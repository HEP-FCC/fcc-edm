// standard includes
#include <stdexcept>


#include "PositionedCaloHitCollection.h"

namespace fcc {

PositionedCaloHitCollection::PositionedCaloHitCollection() : m_isValid(false), m_collectionID(0), m_entries() ,m_data(new PositionedCaloHitDataContainer() ) {
  
}

PositionedCaloHitCollection::~PositionedCaloHitCollection() {
  clear();
  if (m_data != nullptr) delete m_data;
  
}

const PositionedCaloHit PositionedCaloHitCollection::operator[](unsigned int index) const {
  return PositionedCaloHit(m_entries[index]);
}

const PositionedCaloHit PositionedCaloHitCollection::at(unsigned int index) const {
  return PositionedCaloHit(m_entries.at(index));
}

int  PositionedCaloHitCollection::size() const {
  return m_entries.size();
}

PositionedCaloHit PositionedCaloHitCollection::create(){
  auto obj = new PositionedCaloHitObj();
  m_entries.emplace_back(obj);

  obj->id = {int(m_entries.size()-1),m_collectionID};
  return PositionedCaloHit(obj);
}

void PositionedCaloHitCollection::clear(){
  m_data->clear();

  for (auto& obj : m_entries) { delete obj; }
  m_entries.clear();
}

void PositionedCaloHitCollection::prepareForWrite(){
  auto size = m_entries.size();
  m_data->reserve(size);
  for (auto& obj : m_entries) {m_data->push_back(obj->data); }
  for (auto& pointer : m_refCollections) {pointer->clear(); } 

  for(int i=0, size = m_data->size(); i != size; ++i){

  }

}

void PositionedCaloHitCollection::prepareAfterRead(){
  int index = 0;
  for (auto& data : *m_data){
    auto obj = new PositionedCaloHitObj({index,m_collectionID}, data);
    
    m_entries.emplace_back(obj);
    ++index;
  }
  m_isValid = true;  
}

bool PositionedCaloHitCollection::setReferences(const podio::ICollectionProvider* collectionProvider){


  return true; //TODO: check success
}

void PositionedCaloHitCollection::push_back(ConstPositionedCaloHit object){
  int size = m_entries.size();
  auto obj = object.m_obj;
  if (obj->id.index == podio::ObjectID::untracked) {
      obj->id = {size,m_collectionID};
      m_entries.push_back(obj);
      
  } else {
    throw std::invalid_argument( "Object already in a collection. Cannot add it to a second collection " );
  }
}

void PositionedCaloHitCollection::setBuffer(void* address){
  if (m_data != nullptr) delete m_data;
  m_data = static_cast<PositionedCaloHitDataContainer*>(address);
}


const PositionedCaloHit PositionedCaloHitCollectionIterator::operator* () const {
  m_object.m_obj = (*m_collection)[m_index];
  return m_object;
}

const PositionedCaloHit* PositionedCaloHitCollectionIterator::operator-> () const {
  m_object.m_obj = (*m_collection)[m_index];
  return &m_object;
}

const PositionedCaloHitCollectionIterator& PositionedCaloHitCollectionIterator::operator++() const {
  ++m_index;
  return *this;
}

} // namespace fcc
