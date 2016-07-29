// standard includes
#include <stdexcept>


#include "CaloHitCollection.h"

namespace fcc {

CaloHitCollection::CaloHitCollection() : m_isValid(false), m_collectionID(0), m_entries() ,m_data(new CaloHitDataContainer() ) {
  
}

CaloHitCollection::~CaloHitCollection() {
  clear();
  if (m_data != nullptr) delete m_data;
  
}

const CaloHit CaloHitCollection::operator[](unsigned int index) const {
  return CaloHit(m_entries[index]);
}

const CaloHit CaloHitCollection::at(unsigned int index) const {
  return CaloHit(m_entries.at(index));
}

int  CaloHitCollection::size() const {
  return m_entries.size();
}

CaloHit CaloHitCollection::create(){
  auto obj = new CaloHitObj();
  m_entries.emplace_back(obj);

  obj->id = {int(m_entries.size()-1),m_collectionID};
  return CaloHit(obj);
}

void CaloHitCollection::clear(){
  m_data->clear();

  for (auto& obj : m_entries) { delete obj; }
  m_entries.clear();
}

void CaloHitCollection::prepareForWrite(){
  auto size = m_entries.size();
  m_data->reserve(size);
  for (auto& obj : m_entries) {m_data->push_back(obj->data); }
  for (auto& pointer : m_refCollections) {pointer->clear(); } 

  for(int i=0, size = m_data->size(); i != size; ++i){

  }

}

void CaloHitCollection::prepareAfterRead(){
  int index = 0;
  for (auto& data : *m_data){
    auto obj = new CaloHitObj({index,m_collectionID}, data);
    
    m_entries.emplace_back(obj);
    ++index;
  }
  m_isValid = true;  
}

bool CaloHitCollection::setReferences(const podio::ICollectionProvider* collectionProvider){


  return true; //TODO: check success
}

void CaloHitCollection::push_back(ConstCaloHit object){
  int size = m_entries.size();
  auto obj = object.m_obj;
  if (obj->id.index == podio::ObjectID::untracked) {
      obj->id = {size,m_collectionID};
      m_entries.push_back(obj);
      
  } else {
    throw std::invalid_argument( "Object already in a collection. Cannot add it to a second collection " );
  }
}

void CaloHitCollection::setBuffer(void* address){
  if (m_data != nullptr) delete m_data;
  m_data = static_cast<CaloHitDataContainer*>(address);
}


const CaloHit CaloHitCollectionIterator::operator* () const {
  m_object.m_obj = (*m_collection)[m_index];
  return m_object;
}

const CaloHit* CaloHitCollectionIterator::operator-> () const {
  m_object.m_obj = (*m_collection)[m_index];
  return &m_object;
}

const CaloHitCollectionIterator& CaloHitCollectionIterator::operator++() const {
  ++m_index;
  return *this;
}

} // namespace fcc
