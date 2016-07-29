// standard includes
#include <stdexcept>
#include "CaloHitCollection.h"
#include "CaloHitCollection.h"


#include "CaloHitAssociationCollection.h"

namespace fcc {

CaloHitAssociationCollection::CaloHitAssociationCollection() : m_isValid(false), m_collectionID(0), m_entries() , m_rel_rec(new std::vector<fcc::ConstCaloHit>()), m_rel_sim(new std::vector<fcc::ConstCaloHit>()),m_data(new CaloHitAssociationDataContainer() ) {
    m_refCollections.push_back(new std::vector<podio::ObjectID>());
  m_refCollections.push_back(new std::vector<podio::ObjectID>());

}

CaloHitAssociationCollection::~CaloHitAssociationCollection() {
  clear();
  if (m_data != nullptr) delete m_data;
    for (auto& pointer : m_refCollections) { if (pointer != nullptr) delete pointer; }
  if (m_rel_rec != nullptr) { delete m_rel_rec; }
  if (m_rel_sim != nullptr) { delete m_rel_sim; }

}

const CaloHitAssociation CaloHitAssociationCollection::operator[](unsigned int index) const {
  return CaloHitAssociation(m_entries[index]);
}

const CaloHitAssociation CaloHitAssociationCollection::at(unsigned int index) const {
  return CaloHitAssociation(m_entries.at(index));
}

int  CaloHitAssociationCollection::size() const {
  return m_entries.size();
}

CaloHitAssociation CaloHitAssociationCollection::create(){
  auto obj = new CaloHitAssociationObj();
  m_entries.emplace_back(obj);

  obj->id = {int(m_entries.size()-1),m_collectionID};
  return CaloHitAssociation(obj);
}

void CaloHitAssociationCollection::clear(){
  m_data->clear();
  for (auto& pointer : m_refCollections) { pointer->clear(); }
  for (auto& item : (*m_rel_rec)) { item.unlink(); }
  m_rel_rec->clear();
  for (auto& item : (*m_rel_sim)) { item.unlink(); }
  m_rel_sim->clear();

  for (auto& obj : m_entries) { delete obj; }
  m_entries.clear();
}

void CaloHitAssociationCollection::prepareForWrite(){
  auto size = m_entries.size();
  m_data->reserve(size);
  for (auto& obj : m_entries) {m_data->push_back(obj->data); }
  for (auto& pointer : m_refCollections) {pointer->clear(); } 

  for(int i=0, size = m_data->size(); i != size; ++i){

  }
  for (auto& obj : m_entries) {
    if (obj->m_rec != nullptr) {
      m_refCollections[0]->emplace_back(obj->m_rec->getObjectID());
    } else {
      m_refCollections[0]->push_back({-2,-2});
    }
  }
  for (auto& obj : m_entries) {
    if (obj->m_sim != nullptr) {
      m_refCollections[1]->emplace_back(obj->m_sim->getObjectID());
    } else {
      m_refCollections[1]->push_back({-2,-2});
    }
  }

}

void CaloHitAssociationCollection::prepareAfterRead(){
  int index = 0;
  for (auto& data : *m_data){
    auto obj = new CaloHitAssociationObj({index,m_collectionID}, data);
    
    m_entries.emplace_back(obj);
    ++index;
  }
  m_isValid = true;  
}

bool CaloHitAssociationCollection::setReferences(const podio::ICollectionProvider* collectionProvider){

  for(unsigned int i = 0, size = m_entries.size(); i != size; ++i) {
    auto id = (*m_refCollections[0])[i];
    if (id.index != podio::ObjectID::invalid) {
      CollectionBase* coll = nullptr;
      collectionProvider->get(id.collectionID,coll);
      fcc::CaloHitCollection* tmp_coll = static_cast<fcc::CaloHitCollection*>(coll);
      m_entries[i]->m_rec = new ConstCaloHit((*tmp_coll)[id.index]);
    } else {
      m_entries[i]->m_rec = nullptr;
    }
  }
  for(unsigned int i = 0, size = m_entries.size(); i != size; ++i) {
    auto id = (*m_refCollections[1])[i];
    if (id.index != podio::ObjectID::invalid) {
      CollectionBase* coll = nullptr;
      collectionProvider->get(id.collectionID,coll);
      fcc::CaloHitCollection* tmp_coll = static_cast<fcc::CaloHitCollection*>(coll);
      m_entries[i]->m_sim = new ConstCaloHit((*tmp_coll)[id.index]);
    } else {
      m_entries[i]->m_sim = nullptr;
    }
  }

  return true; //TODO: check success
}

void CaloHitAssociationCollection::push_back(ConstCaloHitAssociation object){
  int size = m_entries.size();
  auto obj = object.m_obj;
  if (obj->id.index == podio::ObjectID::untracked) {
      obj->id = {size,m_collectionID};
      m_entries.push_back(obj);
      
  } else {
    throw std::invalid_argument( "Object already in a collection. Cannot add it to a second collection " );
  }
}

void CaloHitAssociationCollection::setBuffer(void* address){
  if (m_data != nullptr) delete m_data;
  m_data = static_cast<CaloHitAssociationDataContainer*>(address);
}


const CaloHitAssociation CaloHitAssociationCollectionIterator::operator* () const {
  m_object.m_obj = (*m_collection)[m_index];
  return m_object;
}

const CaloHitAssociation* CaloHitAssociationCollectionIterator::operator-> () const {
  m_object.m_obj = (*m_collection)[m_index];
  return &m_object;
}

const CaloHitAssociationCollectionIterator& CaloHitAssociationCollectionIterator::operator++() const {
  ++m_index;
  return *this;
}

} // namespace fcc
