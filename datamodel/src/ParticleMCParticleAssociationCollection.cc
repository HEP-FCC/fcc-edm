// standard includes
#include <stdexcept>
#include "ParticleCollection.h"
#include "MCParticleCollection.h"


#include "ParticleMCParticleAssociationCollection.h"

namespace fcc {

ParticleMCParticleAssociationCollection::ParticleMCParticleAssociationCollection() : m_isValid(false), m_collectionID(0), m_entries() , m_rel_rec(new std::vector<fcc::ConstParticle>()), m_rel_sim(new std::vector<fcc::ConstMCParticle>()),m_data(new ParticleMCParticleAssociationDataContainer() ) {
    m_refCollections.push_back(new std::vector<podio::ObjectID>());
  m_refCollections.push_back(new std::vector<podio::ObjectID>());

}

ParticleMCParticleAssociationCollection::~ParticleMCParticleAssociationCollection() {
  clear();
  if (m_data != nullptr) delete m_data;
    for (auto& pointer : m_refCollections) { if (pointer != nullptr) delete pointer; }
  if (m_rel_rec != nullptr) { delete m_rel_rec; }
  if (m_rel_sim != nullptr) { delete m_rel_sim; }

}

const ParticleMCParticleAssociation ParticleMCParticleAssociationCollection::operator[](unsigned int index) const {
  return ParticleMCParticleAssociation(m_entries[index]);
}

const ParticleMCParticleAssociation ParticleMCParticleAssociationCollection::at(unsigned int index) const {
  return ParticleMCParticleAssociation(m_entries.at(index));
}

int  ParticleMCParticleAssociationCollection::size() const {
  return m_entries.size();
}

ParticleMCParticleAssociation ParticleMCParticleAssociationCollection::create(){
  auto obj = new ParticleMCParticleAssociationObj();
  m_entries.emplace_back(obj);

  obj->id = {int(m_entries.size()-1),m_collectionID};
  return ParticleMCParticleAssociation(obj);
}

void ParticleMCParticleAssociationCollection::clear(){
  m_data->clear();
  for (auto& pointer : m_refCollections) { pointer->clear(); }
  for (auto& item : (*m_rel_rec)) { item.unlink(); }
  m_rel_rec->clear();
  for (auto& item : (*m_rel_sim)) { item.unlink(); }
  m_rel_sim->clear();

  for (auto& obj : m_entries) { delete obj; }
  m_entries.clear();
}

void ParticleMCParticleAssociationCollection::prepareForWrite(){
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

void ParticleMCParticleAssociationCollection::prepareAfterRead(){
  int index = 0;
  for (auto& data : *m_data){
    auto obj = new ParticleMCParticleAssociationObj({index,m_collectionID}, data);
    
    m_entries.emplace_back(obj);
    ++index;
  }
  m_isValid = true;  
}

bool ParticleMCParticleAssociationCollection::setReferences(const podio::ICollectionProvider* collectionProvider){

  for(unsigned int i = 0, size = m_entries.size(); i != size; ++i) {
    auto id = (*m_refCollections[0])[i];
    if (id.index != podio::ObjectID::invalid) {
      CollectionBase* coll = nullptr;
      collectionProvider->get(id.collectionID,coll);
      fcc::ParticleCollection* tmp_coll = static_cast<fcc::ParticleCollection*>(coll);
      m_entries[i]->m_rec = new ConstParticle((*tmp_coll)[id.index]);
    } else {
      m_entries[i]->m_rec = nullptr;
    }
  }
  for(unsigned int i = 0, size = m_entries.size(); i != size; ++i) {
    auto id = (*m_refCollections[1])[i];
    if (id.index != podio::ObjectID::invalid) {
      CollectionBase* coll = nullptr;
      collectionProvider->get(id.collectionID,coll);
      fcc::MCParticleCollection* tmp_coll = static_cast<fcc::MCParticleCollection*>(coll);
      m_entries[i]->m_sim = new ConstMCParticle((*tmp_coll)[id.index]);
    } else {
      m_entries[i]->m_sim = nullptr;
    }
  }

  return true; //TODO: check success
}

void ParticleMCParticleAssociationCollection::push_back(ConstParticleMCParticleAssociation object){
  int size = m_entries.size();
  auto obj = object.m_obj;
  if (obj->id.index == podio::ObjectID::untracked) {
      obj->id = {size,m_collectionID};
      m_entries.push_back(obj);
      
  } else {
    throw std::invalid_argument( "Object already in a collection. Cannot add it to a second collection " );
  }
}

void ParticleMCParticleAssociationCollection::setBuffer(void* address){
  if (m_data != nullptr) delete m_data;
  m_data = static_cast<ParticleMCParticleAssociationDataContainer*>(address);
}


const ParticleMCParticleAssociation ParticleMCParticleAssociationCollectionIterator::operator* () const {
  m_object.m_obj = (*m_collection)[m_index];
  return m_object;
}

const ParticleMCParticleAssociation* ParticleMCParticleAssociationCollectionIterator::operator-> () const {
  m_object.m_obj = (*m_collection)[m_index];
  return &m_object;
}

const ParticleMCParticleAssociationCollectionIterator& ParticleMCParticleAssociationCollectionIterator::operator++() const {
  ++m_index;
  return *this;
}

} // namespace fcc
