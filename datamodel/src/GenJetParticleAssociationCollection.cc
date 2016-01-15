// standard includes
#include <stdexcept>
#include "GenJetCollection.h" 
#include "MCParticleCollection.h" 


#include "GenJetParticleAssociationCollection.h"



GenJetParticleAssociationCollection::GenJetParticleAssociationCollection() : m_collectionID(0), m_entries() ,m_rel_Jet(new std::vector<ConstGenJet>()),m_rel_Particle(new std::vector<ConstMCParticle>()),m_refCollections(nullptr), m_data(new GenJetParticleAssociationDataContainer() ) {
    m_refCollections = new podio::CollRefCollection();
  m_refCollections->push_back(new std::vector<podio::ObjectID>());
  m_refCollections->push_back(new std::vector<podio::ObjectID>());

}

const GenJetParticleAssociation GenJetParticleAssociationCollection::operator[](unsigned int index) const {
  return GenJetParticleAssociation(m_entries[index]);
}

const GenJetParticleAssociation GenJetParticleAssociationCollection::at(unsigned int index) const {
  return GenJetParticleAssociation(m_entries.at(index));
}

int  GenJetParticleAssociationCollection::size() const {
  return m_entries.size();
}

GenJetParticleAssociation GenJetParticleAssociationCollection::create(){
  auto obj = new GenJetParticleAssociationObj();
  m_entries.emplace_back(obj);

  obj->id = {int(m_entries.size()-1),m_collectionID};
  return GenJetParticleAssociation(obj);
}

void GenJetParticleAssociationCollection::clear(){
  m_data->clear();
  for (auto& pointer : (*m_refCollections)) {pointer->clear(); }
  for (auto& item : (*m_rel_Jet)) {item.unlink(); }
  m_rel_Jet->clear();
  for (auto& item : (*m_rel_Particle)) {item.unlink(); }
  m_rel_Particle->clear();

  for (auto& obj : m_entries) { delete obj; }
  m_entries.clear();
}

void GenJetParticleAssociationCollection::prepareForWrite(){
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
if (obj->m_Jet != nullptr){
(*m_refCollections)[0]->emplace_back(obj->m_Jet->getObjectID());} else {(*m_refCollections)[0]->push_back({-2,-2}); } }
  for (auto& obj : m_entries) {
if (obj->m_Particle != nullptr){
(*m_refCollections)[1]->emplace_back(obj->m_Particle->getObjectID());} else {(*m_refCollections)[1]->push_back({-2,-2}); } }

}

void GenJetParticleAssociationCollection::prepareAfterRead(){
  int index = 0;
  for (auto& data : *m_data){
    auto obj = new GenJetParticleAssociationObj({index,m_collectionID}, data);
    
    m_entries.emplace_back(obj);
    ++index;
  }
}

bool GenJetParticleAssociationCollection::setReferences(const podio::ICollectionProvider* collectionProvider){

  for(unsigned int i=0, size=m_entries.size();i!=size;++i ) {
    auto id = (*(*m_refCollections)[0])[i];
    if (id.index != podio::ObjectID::invalid) {
      CollectionBase* coll = nullptr;
      collectionProvider->get(id.collectionID,coll);
      GenJetCollection* tmp_coll = static_cast<GenJetCollection*>(coll);
      m_entries[i]->m_Jet = new ConstGenJet((*tmp_coll)[id.index]);
    } else {
      m_entries[i]->m_Jet = nullptr;
    }
  }
  for(unsigned int i=0, size=m_entries.size();i!=size;++i ) {
    auto id = (*(*m_refCollections)[1])[i];
    if (id.index != podio::ObjectID::invalid) {
      CollectionBase* coll = nullptr;
      collectionProvider->get(id.collectionID,coll);
      MCParticleCollection* tmp_coll = static_cast<MCParticleCollection*>(coll);
      m_entries[i]->m_Particle = new ConstMCParticle((*tmp_coll)[id.index]);
    } else {
      m_entries[i]->m_Particle = nullptr;
    }
  }

  return true; //TODO: check success
}

void GenJetParticleAssociationCollection::push_back(ConstGenJetParticleAssociation object){
    int size = m_entries.size();
    auto obj = object.m_obj;
    if (obj->id.index == podio::ObjectID::untracked) {
        obj->id = {size,m_collectionID};
        m_entries.push_back(obj);
        
    } else {
      throw std::invalid_argument( "Object already in a collection. Cannot add it to a second collection " );

    }
}

void GenJetParticleAssociationCollection::setBuffer(void* address){
  m_data = static_cast<GenJetParticleAssociationDataContainer*>(address);
}


const GenJetParticleAssociation GenJetParticleAssociationCollectionIterator::operator* () const {
  m_object.m_obj = (*m_collection)[m_index];
  return m_object;
}

const GenJetParticleAssociation* GenJetParticleAssociationCollectionIterator::operator-> () const {
    m_object.m_obj = (*m_collection)[m_index];
    return &m_object;
}

const GenJetParticleAssociationCollectionIterator& GenJetParticleAssociationCollectionIterator::operator++() const {
  ++m_index;
 return *this;
}


