// standard includes
#include <stdexcept>


#include "TrackStateCollection.h"

namespace fcc {

TrackStateCollection::TrackStateCollection() : m_isValid(false), m_collectionID(0), m_entries() ,m_data(new TrackStateDataContainer() ) {
  
}

TrackStateCollection::~TrackStateCollection() {
  clear();
  if (m_data != nullptr) delete m_data;
  
};

const TrackState TrackStateCollection::operator[](unsigned int index) const {
  return TrackState(m_entries[index]);
}

const TrackState TrackStateCollection::at(unsigned int index) const {
  return TrackState(m_entries.at(index));
}

int  TrackStateCollection::size() const {
  return m_entries.size();
}

TrackState TrackStateCollection::create(){
  auto obj = new TrackStateObj();
  m_entries.emplace_back(obj);

  obj->id = {int(m_entries.size()-1),m_collectionID};
  return TrackState(obj);
}

void TrackStateCollection::clear(){
  m_data->clear();

  for (auto& obj : m_entries) { delete obj; }
  m_entries.clear();
}

void TrackStateCollection::prepareForWrite(){
  auto size = m_entries.size();
  m_data->reserve(size);
  for (auto& obj : m_entries) {m_data->push_back(obj->data); }
  for (auto& pointer : m_refCollections) {pointer->clear(); } 

  for(int i=0, size = m_data->size(); i != size; ++i){

  }

}

void TrackStateCollection::prepareAfterRead(){
  int index = 0;
  for (auto& data : *m_data){
    auto obj = new TrackStateObj({index,m_collectionID}, data);
    
    m_entries.emplace_back(obj);
    ++index;
  }
  m_isValid = true;  
}

bool TrackStateCollection::setReferences(const podio::ICollectionProvider* collectionProvider){


  return true; //TODO: check success
}

void TrackStateCollection::push_back(ConstTrackState object){
  int size = m_entries.size();
  auto obj = object.m_obj;
  if (obj->id.index == podio::ObjectID::untracked) {
      obj->id = {size,m_collectionID};
      m_entries.push_back(obj);
      
  } else {
    throw std::invalid_argument( "Object already in a collection. Cannot add it to a second collection " );
  }
}

void TrackStateCollection::setBuffer(void* address){
  if (m_data != nullptr) delete m_data;
  m_data = static_cast<TrackStateDataContainer*>(address);
}


const TrackState TrackStateCollectionIterator::operator* () const {
  m_object.m_obj = (*m_collection)[m_index];
  return m_object;
}

const TrackState* TrackStateCollectionIterator::operator-> () const {
  m_object.m_obj = (*m_collection)[m_index];
  return &m_object;
}

const TrackStateCollectionIterator& TrackStateCollectionIterator::operator++() const {
  ++m_index;
  return *this;
}

} // namespace fcc
