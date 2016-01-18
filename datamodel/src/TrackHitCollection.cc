// standard includes
#include <stdexcept>


#include "TrackHitCollection.h"



TrackHitCollection::TrackHitCollection() : m_collectionID(0), m_entries() ,m_refCollections(nullptr), m_data(new TrackHitDataContainer() ) {
  
}

const TrackHit TrackHitCollection::operator[](unsigned int index) const {
  return TrackHit(m_entries[index]);
}

const TrackHit TrackHitCollection::at(unsigned int index) const {
  return TrackHit(m_entries.at(index));
}

int  TrackHitCollection::size() const {
  return m_entries.size();
}

TrackHit TrackHitCollection::create(){
  auto obj = new TrackHitObj();
  m_entries.emplace_back(obj);

  obj->id = {int(m_entries.size()-1),m_collectionID};
  return TrackHit(obj);
}

void TrackHitCollection::clear(){
  m_data->clear();

  for (auto& obj : m_entries) { delete obj; }
  m_entries.clear();
}

void TrackHitCollection::prepareForWrite(){
  int index = 0;
  auto size = m_entries.size();
  m_data->reserve(size);
  for (auto& obj : m_entries) {m_data->push_back(obj->data); }
  if (m_refCollections != nullptr) {
    for (auto& pointer : (*m_refCollections)) {pointer->clear(); }
  }
  
  for(int i=0, size = m_data->size(); i != size; ++i){
  
  }
  
}

void TrackHitCollection::prepareAfterRead(){
  int index = 0;
  for (auto& data : *m_data){
    auto obj = new TrackHitObj({index,m_collectionID}, data);
    
    m_entries.emplace_back(obj);
    ++index;
  }
}

bool TrackHitCollection::setReferences(const podio::ICollectionProvider* collectionProvider){


  return true; //TODO: check success
}

void TrackHitCollection::push_back(ConstTrackHit object){
    int size = m_entries.size();
    auto obj = object.m_obj;
    if (obj->id.index == podio::ObjectID::untracked) {
        obj->id = {size,m_collectionID};
        m_entries.push_back(obj);
        
    } else {
      throw std::invalid_argument( "Object already in a collection. Cannot add it to a second collection " );

    }
}

void TrackHitCollection::setBuffer(void* address){
  m_data = static_cast<TrackHitDataContainer*>(address);
}


const TrackHit TrackHitCollectionIterator::operator* () const {
  m_object.m_obj = (*m_collection)[m_index];
  return m_object;
}

const TrackHit* TrackHitCollectionIterator::operator-> () const {
    m_object.m_obj = (*m_collection)[m_index];
    return &m_object;
}

const TrackHitCollectionIterator& TrackHitCollectionIterator::operator++() const {
  ++m_index;
 return *this;
}


