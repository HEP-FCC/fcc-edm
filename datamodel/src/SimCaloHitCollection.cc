// standard includes
#include <stdexcept>


#include "SimCaloHitCollection.h"

namespace fcc {

SimCaloHitCollection::SimCaloHitCollection() : m_isValid(false), m_collectionID(0), m_entries() ,m_data(new SimCaloHitDataContainer() ) {
  
}

SimCaloHitCollection::~SimCaloHitCollection() {
  clear();
  if (m_data != nullptr) delete m_data;
  
};

const SimCaloHit SimCaloHitCollection::operator[](unsigned int index) const {
  return SimCaloHit(m_entries[index]);
}

const SimCaloHit SimCaloHitCollection::at(unsigned int index) const {
  return SimCaloHit(m_entries.at(index));
}

int  SimCaloHitCollection::size() const {
  return m_entries.size();
}

SimCaloHit SimCaloHitCollection::create(){
  auto obj = new SimCaloHitObj();
  m_entries.emplace_back(obj);

  obj->id = {int(m_entries.size()-1),m_collectionID};
  return SimCaloHit(obj);
}

void SimCaloHitCollection::clear(){
  m_data->clear();

  for (auto& obj : m_entries) { delete obj; }
  m_entries.clear();
}

void SimCaloHitCollection::prepareForWrite(){
  auto size = m_entries.size();
  m_data->reserve(size);
  for (auto& obj : m_entries) {m_data->push_back(obj->data); }
  for (auto& pointer : m_refCollections) {pointer->clear(); } 

  for(int i=0, size = m_data->size(); i != size; ++i){

  }

}

void SimCaloHitCollection::prepareAfterRead(){
  int index = 0;
  for (auto& data : *m_data){
    auto obj = new SimCaloHitObj({index,m_collectionID}, data);
    
    m_entries.emplace_back(obj);
    ++index;
  }
  m_isValid = true;  
}

bool SimCaloHitCollection::setReferences(const podio::ICollectionProvider* collectionProvider){


  return true; //TODO: check success
}

void SimCaloHitCollection::push_back(ConstSimCaloHit object){
  int size = m_entries.size();
  auto obj = object.m_obj;
  if (obj->id.index == podio::ObjectID::untracked) {
      obj->id = {size,m_collectionID};
      m_entries.push_back(obj);
      
  } else {
    throw std::invalid_argument( "Object already in a collection. Cannot add it to a second collection " );
  }
}

void SimCaloHitCollection::setBuffer(void* address){
  if (m_data != nullptr) delete m_data;
  m_data = static_cast<SimCaloHitDataContainer*>(address);
}


const SimCaloHit SimCaloHitCollectionIterator::operator* () const {
  m_object.m_obj = (*m_collection)[m_index];
  return m_object;
}

const SimCaloHit* SimCaloHitCollectionIterator::operator-> () const {
  m_object.m_obj = (*m_collection)[m_index];
  return &m_object;
}

const SimCaloHitCollectionIterator& SimCaloHitCollectionIterator::operator++() const {
  ++m_index;
  return *this;
}

} // namespace fcc
