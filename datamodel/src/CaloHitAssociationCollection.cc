// standard includes
#include <stdexcept>
#include "CaloHitCollection.h" 
#include "SimCaloHitCollection.h" 


#include "CaloHitAssociationCollection.h"



CaloHitAssociationCollection::CaloHitAssociationCollection() : m_collectionID(0), m_entries() ,m_rel_Rec(new std::vector<ConstCaloHit>()),m_rel_Sim(new std::vector<ConstSimCaloHit>()),m_refCollections(nullptr), m_data(new CaloHitAssociationDataContainer() ) {
    m_refCollections = new podio::CollRefCollection();
  m_refCollections->push_back(new std::vector<podio::ObjectID>());
  m_refCollections->push_back(new std::vector<podio::ObjectID>());

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
  for (auto& pointer : (*m_refCollections)) {pointer->clear(); }
  for (auto& item : (*m_rel_Rec)) {item.unlink(); }
  m_rel_Rec->clear();
  for (auto& item : (*m_rel_Sim)) {item.unlink(); }
  m_rel_Sim->clear();

  for (auto& obj : m_entries) { delete obj; }
  m_entries.clear();
}

void CaloHitAssociationCollection::prepareForWrite(){
  int index = 0;
  auto size = m_entries.size();
  m_data->reserve(size);
  for (auto& obj : m_entries) {m_data->push_back(obj->data); }
  if (m_refCollections != nullptr) {
    for (auto& pointer : (*m_refCollections)) {pointer->clear(); }
  }
  
  for(int i=0, size = m_data->size(); i != size; ++i){
  
  }
    for (auto& obj : m_entries) {
if (obj->m_Rec != nullptr){
(*m_refCollections)[0]->emplace_back(obj->m_Rec->getObjectID());} else {(*m_refCollections)[0]->push_back({-2,-2}); } }
  for (auto& obj : m_entries) {
if (obj->m_Sim != nullptr){
(*m_refCollections)[1]->emplace_back(obj->m_Sim->getObjectID());} else {(*m_refCollections)[1]->push_back({-2,-2}); } }

}

void CaloHitAssociationCollection::prepareAfterRead(){
  int index = 0;
  for (auto& data : *m_data){
    auto obj = new CaloHitAssociationObj({index,m_collectionID}, data);
    
    m_entries.emplace_back(obj);
    ++index;
  }
}

bool CaloHitAssociationCollection::setReferences(const podio::ICollectionProvider* collectionProvider){

  for(unsigned int i=0, size=m_entries.size();i!=size;++i ) {
    auto id = (*(*m_refCollections)[0])[i];
    if (id.index != podio::ObjectID::invalid) {
      CollectionBase* coll = nullptr;
      collectionProvider->get(id.collectionID,coll);
      CaloHitCollection* tmp_coll = static_cast<CaloHitCollection*>(coll);
      m_entries[i]->m_Rec = new ConstCaloHit((*tmp_coll)[id.index]);
    } else {
      m_entries[i]->m_Rec = nullptr;
    }
  }
  for(unsigned int i=0, size=m_entries.size();i!=size;++i ) {
    auto id = (*(*m_refCollections)[1])[i];
    if (id.index != podio::ObjectID::invalid) {
      CollectionBase* coll = nullptr;
      collectionProvider->get(id.collectionID,coll);
      SimCaloHitCollection* tmp_coll = static_cast<SimCaloHitCollection*>(coll);
      m_entries[i]->m_Sim = new ConstSimCaloHit((*tmp_coll)[id.index]);
    } else {
      m_entries[i]->m_Sim = nullptr;
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


