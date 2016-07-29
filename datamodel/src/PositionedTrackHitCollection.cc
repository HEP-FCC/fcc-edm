// standard includes
#include <stdexcept>


#include "PositionedTrackHitCollection.h"

namespace fcc {

PositionedTrackHitCollection::PositionedTrackHitCollection() : m_isValid(false), m_collectionID(0), m_entries() ,m_data(new PositionedTrackHitDataContainer() ) {
  
}

PositionedTrackHitCollection::~PositionedTrackHitCollection() {
  clear();
  if (m_data != nullptr) delete m_data;
  
}

const PositionedTrackHit PositionedTrackHitCollection::operator[](unsigned int index) const {
  return PositionedTrackHit(m_entries[index]);
}

const PositionedTrackHit PositionedTrackHitCollection::at(unsigned int index) const {
  return PositionedTrackHit(m_entries.at(index));
}

int  PositionedTrackHitCollection::size() const {
  return m_entries.size();
}

PositionedTrackHit PositionedTrackHitCollection::create(){
  auto obj = new PositionedTrackHitObj();
  m_entries.emplace_back(obj);

  obj->id = {int(m_entries.size()-1),m_collectionID};
  return PositionedTrackHit(obj);
}

void PositionedTrackHitCollection::clear(){
  m_data->clear();

  for (auto& obj : m_entries) { delete obj; }
  m_entries.clear();
}

void PositionedTrackHitCollection::prepareForWrite(){
  auto size = m_entries.size();
  m_data->reserve(size);
  for (auto& obj : m_entries) {m_data->push_back(obj->data); }
  for (auto& pointer : m_refCollections) {pointer->clear(); } 

  for(int i=0, size = m_data->size(); i != size; ++i){

  }

}

void PositionedTrackHitCollection::prepareAfterRead(){
  int index = 0;
  for (auto& data : *m_data){
    auto obj = new PositionedTrackHitObj({index,m_collectionID}, data);
    
    m_entries.emplace_back(obj);
    ++index;
  }
  m_isValid = true;  
}

bool PositionedTrackHitCollection::setReferences(const podio::ICollectionProvider* collectionProvider){


  return true; //TODO: check success
}

void PositionedTrackHitCollection::push_back(ConstPositionedTrackHit object){
  int size = m_entries.size();
  auto obj = object.m_obj;
  if (obj->id.index == podio::ObjectID::untracked) {
      obj->id = {size,m_collectionID};
      m_entries.push_back(obj);
      
  } else {
    throw std::invalid_argument( "Object already in a collection. Cannot add it to a second collection " );
  }
}

void PositionedTrackHitCollection::setBuffer(void* address){
  if (m_data != nullptr) delete m_data;
  m_data = static_cast<PositionedTrackHitDataContainer*>(address);
}


const PositionedTrackHit PositionedTrackHitCollectionIterator::operator* () const {
  m_object.m_obj = (*m_collection)[m_index];
  return m_object;
}

const PositionedTrackHit* PositionedTrackHitCollectionIterator::operator-> () const {
  m_object.m_obj = (*m_collection)[m_index];
  return &m_object;
}

const PositionedTrackHitCollectionIterator& PositionedTrackHitCollectionIterator::operator++() const {
  ++m_index;
  return *this;
}

} // namespace fcc
