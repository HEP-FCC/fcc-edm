// standard includes
#include <stdexcept>


#include "TrackCollection.h"

namespace fcc {

TrackCollection::TrackCollection() : m_isValid(false), m_collectionID(0), m_entries() ,m_data(new TrackDataContainer() ) {
  
}

TrackCollection::~TrackCollection() {
  clear();
  if (m_data != nullptr) delete m_data;
  
};

const Track TrackCollection::operator[](unsigned int index) const {
  return Track(m_entries[index]);
}

const Track TrackCollection::at(unsigned int index) const {
  return Track(m_entries.at(index));
}

int  TrackCollection::size() const {
  return m_entries.size();
}

Track TrackCollection::create(){
  auto obj = new TrackObj();
  m_entries.emplace_back(obj);

  obj->id = {int(m_entries.size()-1),m_collectionID};
  return Track(obj);
}

void TrackCollection::clear(){
  m_data->clear();

  for (auto& obj : m_entries) { delete obj; }
  m_entries.clear();
}

void TrackCollection::prepareForWrite(){
  auto size = m_entries.size();
  m_data->reserve(size);
  for (auto& obj : m_entries) {m_data->push_back(obj->data); }
  for (auto& pointer : m_refCollections) {pointer->clear(); } 

  for(int i=0, size = m_data->size(); i != size; ++i){

  }

}

void TrackCollection::prepareAfterRead(){
  int index = 0;
  for (auto& data : *m_data){
    auto obj = new TrackObj({index,m_collectionID}, data);
    
    m_entries.emplace_back(obj);
    ++index;
  }
  m_isValid = true;  
}

bool TrackCollection::setReferences(const podio::ICollectionProvider* collectionProvider){


  return true; //TODO: check success
}

void TrackCollection::push_back(ConstTrack object){
  int size = m_entries.size();
  auto obj = object.m_obj;
  if (obj->id.index == podio::ObjectID::untracked) {
      obj->id = {size,m_collectionID};
      m_entries.push_back(obj);
      
  } else {
    throw std::invalid_argument( "Object already in a collection. Cannot add it to a second collection " );
  }
}

void TrackCollection::setBuffer(void* address){
  if (m_data != nullptr) delete m_data;
  m_data = static_cast<TrackDataContainer*>(address);
}


const Track TrackCollectionIterator::operator* () const {
  m_object.m_obj = (*m_collection)[m_index];
  return m_object;
}

const Track* TrackCollectionIterator::operator-> () const {
  m_object.m_obj = (*m_collection)[m_index];
  return &m_object;
}

const TrackCollectionIterator& TrackCollectionIterator::operator++() const {
  ++m_index;
  return *this;
}

} // namespace fcc
