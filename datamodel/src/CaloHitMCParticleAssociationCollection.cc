// standard includes
#include <stdexcept>
#include "CaloHitCollection.h"
#include "MCParticleCollection.h"


#include "CaloHitMCParticleAssociationCollection.h"

namespace fcc {

CaloHitMCParticleAssociationCollection::CaloHitMCParticleAssociationCollection() : m_isValid(false), m_collectionID(0), m_entries() , m_rel_hit(new std::vector<fcc::ConstCaloHit>()), m_rel_particle(new std::vector<fcc::ConstMCParticle>()),m_data(new CaloHitMCParticleAssociationDataContainer() ) {
    m_refCollections.push_back(new std::vector<podio::ObjectID>());
  m_refCollections.push_back(new std::vector<podio::ObjectID>());

}

CaloHitMCParticleAssociationCollection::~CaloHitMCParticleAssociationCollection() {
  clear();
  if (m_data != nullptr) delete m_data;
    for (auto& pointer : m_refCollections) { if (pointer != nullptr) delete pointer; }
  if (m_rel_hit != nullptr) { delete m_rel_hit; }
  if (m_rel_particle != nullptr) { delete m_rel_particle; }

}

const CaloHitMCParticleAssociation CaloHitMCParticleAssociationCollection::operator[](unsigned int index) const {
  return CaloHitMCParticleAssociation(m_entries[index]);
}

const CaloHitMCParticleAssociation CaloHitMCParticleAssociationCollection::at(unsigned int index) const {
  return CaloHitMCParticleAssociation(m_entries.at(index));
}

int  CaloHitMCParticleAssociationCollection::size() const {
  return m_entries.size();
}

CaloHitMCParticleAssociation CaloHitMCParticleAssociationCollection::create(){
  auto obj = new CaloHitMCParticleAssociationObj();
  m_entries.emplace_back(obj);

  obj->id = {int(m_entries.size()-1),m_collectionID};
  return CaloHitMCParticleAssociation(obj);
}

void CaloHitMCParticleAssociationCollection::clear(){
  m_data->clear();
  for (auto& pointer : m_refCollections) { pointer->clear(); }
  for (auto& item : (*m_rel_hit)) { item.unlink(); }
  m_rel_hit->clear();
  for (auto& item : (*m_rel_particle)) { item.unlink(); }
  m_rel_particle->clear();

  for (auto& obj : m_entries) { delete obj; }
  m_entries.clear();
}

void CaloHitMCParticleAssociationCollection::prepareForWrite(){
  auto size = m_entries.size();
  m_data->reserve(size);
  for (auto& obj : m_entries) {m_data->push_back(obj->data); }
  for (auto& pointer : m_refCollections) {pointer->clear(); } 

  for(int i=0, size = m_data->size(); i != size; ++i){

  }
  for (auto& obj : m_entries) {
    if (obj->m_hit != nullptr) {
      m_refCollections[0]->emplace_back(obj->m_hit->getObjectID());
    } else {
      m_refCollections[0]->push_back({-2,-2});
    }
  }
  for (auto& obj : m_entries) {
    if (obj->m_particle != nullptr) {
      m_refCollections[1]->emplace_back(obj->m_particle->getObjectID());
    } else {
      m_refCollections[1]->push_back({-2,-2});
    }
  }

}

void CaloHitMCParticleAssociationCollection::prepareAfterRead(){
  int index = 0;
  for (auto& data : *m_data){
    auto obj = new CaloHitMCParticleAssociationObj({index,m_collectionID}, data);
    
    m_entries.emplace_back(obj);
    ++index;
  }
  m_isValid = true;  
}

bool CaloHitMCParticleAssociationCollection::setReferences(const podio::ICollectionProvider* collectionProvider){

  for(unsigned int i = 0, size = m_entries.size(); i != size; ++i) {
    auto id = (*m_refCollections[0])[i];
    if (id.index != podio::ObjectID::invalid) {
      CollectionBase* coll = nullptr;
      collectionProvider->get(id.collectionID,coll);
      fcc::CaloHitCollection* tmp_coll = static_cast<fcc::CaloHitCollection*>(coll);
      m_entries[i]->m_hit = new ConstCaloHit((*tmp_coll)[id.index]);
    } else {
      m_entries[i]->m_hit = nullptr;
    }
  }
  for(unsigned int i = 0, size = m_entries.size(); i != size; ++i) {
    auto id = (*m_refCollections[1])[i];
    if (id.index != podio::ObjectID::invalid) {
      CollectionBase* coll = nullptr;
      collectionProvider->get(id.collectionID,coll);
      fcc::MCParticleCollection* tmp_coll = static_cast<fcc::MCParticleCollection*>(coll);
      m_entries[i]->m_particle = new ConstMCParticle((*tmp_coll)[id.index]);
    } else {
      m_entries[i]->m_particle = nullptr;
    }
  }

  return true; //TODO: check success
}

void CaloHitMCParticleAssociationCollection::push_back(ConstCaloHitMCParticleAssociation object){
  int size = m_entries.size();
  auto obj = object.m_obj;
  if (obj->id.index == podio::ObjectID::untracked) {
      obj->id = {size,m_collectionID};
      m_entries.push_back(obj);
      
  } else {
    throw std::invalid_argument( "Object already in a collection. Cannot add it to a second collection " );
  }
}

void CaloHitMCParticleAssociationCollection::setBuffer(void* address){
  if (m_data != nullptr) delete m_data;
  m_data = static_cast<CaloHitMCParticleAssociationDataContainer*>(address);
}


const CaloHitMCParticleAssociation CaloHitMCParticleAssociationCollectionIterator::operator* () const {
  m_object.m_obj = (*m_collection)[m_index];
  return m_object;
}

const CaloHitMCParticleAssociation* CaloHitMCParticleAssociationCollectionIterator::operator-> () const {
  m_object.m_obj = (*m_collection)[m_index];
  return &m_object;
}

const CaloHitMCParticleAssociationCollectionIterator& CaloHitMCParticleAssociationCollectionIterator::operator++() const {
  ++m_index;
  return *this;
}

} // namespace fcc
