// standard includes
#include <stdexcept>
#include "SimCaloHitCollection.h"
#include "MCParticleCollection.h"


#include "SimCaloHitMCParticleAssociationCollection.h"

namespace fcc {

SimCaloHitMCParticleAssociationCollection::SimCaloHitMCParticleAssociationCollection() : m_isValid(false), m_collectionID(0), m_entries() , m_rel_Hit(new std::vector<fcc::ConstSimCaloHit>()), m_rel_Particle(new std::vector<fcc::ConstMCParticle>()),m_data(new SimCaloHitMCParticleAssociationDataContainer() ) {
    m_refCollections.push_back(new std::vector<podio::ObjectID>());
  m_refCollections.push_back(new std::vector<podio::ObjectID>());

}

SimCaloHitMCParticleAssociationCollection::~SimCaloHitMCParticleAssociationCollection() {
  clear();
  if (m_data != nullptr) delete m_data;
    for (auto& pointer : m_refCollections) { if (pointer != nullptr) delete pointer; }
  if (m_rel_Hit != nullptr) { delete m_rel_Hit; }
  if (m_rel_Particle != nullptr) { delete m_rel_Particle; }

};

const SimCaloHitMCParticleAssociation SimCaloHitMCParticleAssociationCollection::operator[](unsigned int index) const {
  return SimCaloHitMCParticleAssociation(m_entries[index]);
}

const SimCaloHitMCParticleAssociation SimCaloHitMCParticleAssociationCollection::at(unsigned int index) const {
  return SimCaloHitMCParticleAssociation(m_entries.at(index));
}

int  SimCaloHitMCParticleAssociationCollection::size() const {
  return m_entries.size();
}

SimCaloHitMCParticleAssociation SimCaloHitMCParticleAssociationCollection::create(){
  auto obj = new SimCaloHitMCParticleAssociationObj();
  m_entries.emplace_back(obj);

  obj->id = {int(m_entries.size()-1),m_collectionID};
  return SimCaloHitMCParticleAssociation(obj);
}

void SimCaloHitMCParticleAssociationCollection::clear(){
  m_data->clear();
  for (auto& pointer : m_refCollections) { pointer->clear(); }
  for (auto& item : (*m_rel_Hit)) { item.unlink(); }
  m_rel_Hit->clear();
  for (auto& item : (*m_rel_Particle)) { item.unlink(); }
  m_rel_Particle->clear();

  for (auto& obj : m_entries) { delete obj; }
  m_entries.clear();
}

void SimCaloHitMCParticleAssociationCollection::prepareForWrite(){
  auto size = m_entries.size();
  m_data->reserve(size);
  for (auto& obj : m_entries) {m_data->push_back(obj->data); }
  for (auto& pointer : m_refCollections) {pointer->clear(); } 

  for(int i=0, size = m_data->size(); i != size; ++i){

  }
  for (auto& obj : m_entries) {
    if (obj->m_Hit != nullptr) {
      m_refCollections[0]->emplace_back(obj->m_Hit->getObjectID());
    } else {
      m_refCollections[0]->push_back({-2,-2});
    }
  }
  for (auto& obj : m_entries) {
    if (obj->m_Particle != nullptr) {
      m_refCollections[1]->emplace_back(obj->m_Particle->getObjectID());
    } else {
      m_refCollections[1]->push_back({-2,-2});
    }
  }

}

void SimCaloHitMCParticleAssociationCollection::prepareAfterRead(){
  int index = 0;
  for (auto& data : *m_data){
    auto obj = new SimCaloHitMCParticleAssociationObj({index,m_collectionID}, data);
    
    m_entries.emplace_back(obj);
    ++index;
  }
  m_isValid = true;  
}

bool SimCaloHitMCParticleAssociationCollection::setReferences(const podio::ICollectionProvider* collectionProvider){

  for(unsigned int i = 0, size = m_entries.size(); i != size; ++i) {
    auto id = (*m_refCollections[0])[i];
    if (id.index != podio::ObjectID::invalid) {
      CollectionBase* coll = nullptr;
      collectionProvider->get(id.collectionID,coll);
      fcc::SimCaloHitCollection* tmp_coll = static_cast<fcc::SimCaloHitCollection*>(coll);
      m_entries[i]->m_Hit = new ConstSimCaloHit((*tmp_coll)[id.index]);
    } else {
      m_entries[i]->m_Hit = nullptr;
    }
  }
  for(unsigned int i = 0, size = m_entries.size(); i != size; ++i) {
    auto id = (*m_refCollections[1])[i];
    if (id.index != podio::ObjectID::invalid) {
      CollectionBase* coll = nullptr;
      collectionProvider->get(id.collectionID,coll);
      fcc::MCParticleCollection* tmp_coll = static_cast<fcc::MCParticleCollection*>(coll);
      m_entries[i]->m_Particle = new ConstMCParticle((*tmp_coll)[id.index]);
    } else {
      m_entries[i]->m_Particle = nullptr;
    }
  }

  return true; //TODO: check success
}

void SimCaloHitMCParticleAssociationCollection::push_back(ConstSimCaloHitMCParticleAssociation object){
  int size = m_entries.size();
  auto obj = object.m_obj;
  if (obj->id.index == podio::ObjectID::untracked) {
      obj->id = {size,m_collectionID};
      m_entries.push_back(obj);
      
  } else {
    throw std::invalid_argument( "Object already in a collection. Cannot add it to a second collection " );
  }
}

void SimCaloHitMCParticleAssociationCollection::setBuffer(void* address){
  if (m_data != nullptr) delete m_data;
  m_data = static_cast<SimCaloHitMCParticleAssociationDataContainer*>(address);
}


const SimCaloHitMCParticleAssociation SimCaloHitMCParticleAssociationCollectionIterator::operator* () const {
  m_object.m_obj = (*m_collection)[m_index];
  return m_object;
}

const SimCaloHitMCParticleAssociation* SimCaloHitMCParticleAssociationCollectionIterator::operator-> () const {
  m_object.m_obj = (*m_collection)[m_index];
  return &m_object;
}

const SimCaloHitMCParticleAssociationCollectionIterator& SimCaloHitMCParticleAssociationCollectionIterator::operator++() const {
  ++m_index;
  return *this;
}

} // namespace fcc
