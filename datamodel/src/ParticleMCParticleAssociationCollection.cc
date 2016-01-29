// standard includes
#include <stdexcept>
#include "ParticleCollection.h" 
#include "MCParticleCollection.h" 


#include "ParticleMCParticleAssociationCollection.h"

namespace fcc {

ParticleMCParticleAssociationCollection::ParticleMCParticleAssociationCollection() : m_collectionID(0), m_entries() ,m_rel_Rec(new std::vector<::fcc::ConstParticle>()),m_rel_Sim(new std::vector<::fcc::ConstMCParticle>()),m_refCollections(nullptr), m_data(new ParticleMCParticleAssociationDataContainer() ) {
    m_refCollections = new podio::CollRefCollection();
  m_refCollections->push_back(new std::vector<podio::ObjectID>());
  m_refCollections->push_back(new std::vector<podio::ObjectID>());

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
  for (auto& pointer : (*m_refCollections)) {pointer->clear(); }
  for (auto& item : (*m_rel_Rec)) {item.unlink(); }
  m_rel_Rec->clear();
  for (auto& item : (*m_rel_Sim)) {item.unlink(); }
  m_rel_Sim->clear();

  for (auto& obj : m_entries) { delete obj; }
  m_entries.clear();
}

void ParticleMCParticleAssociationCollection::prepareForWrite(){
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

void ParticleMCParticleAssociationCollection::prepareAfterRead(){
  int index = 0;
  for (auto& data : *m_data){
    auto obj = new ParticleMCParticleAssociationObj({index,m_collectionID}, data);
    
    m_entries.emplace_back(obj);
    ++index;
  }
}

bool ParticleMCParticleAssociationCollection::setReferences(const podio::ICollectionProvider* collectionProvider){

  for(unsigned int i=0, size=m_entries.size();i!=size;++i ) {
    auto id = (*(*m_refCollections)[0])[i];
    if (id.index != podio::ObjectID::invalid) {
      CollectionBase* coll = nullptr;
      collectionProvider->get(id.collectionID,coll);
      fcc::ParticleCollection* tmp_coll = static_cast<fcc::ParticleCollection*>(coll);
      m_entries[i]->m_Rec = new ConstParticle((*tmp_coll)[id.index]);
    } else {
      m_entries[i]->m_Rec = nullptr;
    }
  }
  for(unsigned int i=0, size=m_entries.size();i!=size;++i ) {
    auto id = (*(*m_refCollections)[1])[i];
    if (id.index != podio::ObjectID::invalid) {
      CollectionBase* coll = nullptr;
      collectionProvider->get(id.collectionID,coll);
      fcc::MCParticleCollection* tmp_coll = static_cast<fcc::MCParticleCollection*>(coll);
      m_entries[i]->m_Sim = new ConstMCParticle((*tmp_coll)[id.index]);
    } else {
      m_entries[i]->m_Sim = nullptr;
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
