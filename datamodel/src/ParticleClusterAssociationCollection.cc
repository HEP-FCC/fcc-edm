// standard includes
#include <stdexcept>
#include "ParticleCollection.h" 
#include "CaloClusterCollection.h" 


#include "ParticleClusterAssociationCollection.h"



ParticleClusterAssociationCollection::ParticleClusterAssociationCollection() : m_collectionID(0), m_entries() ,m_rel_Particle(new std::vector<ConstParticle>()),m_rel_Cluster(new std::vector<ConstCaloCluster>()),m_refCollections(nullptr), m_data(new ParticleClusterAssociationDataContainer() ) {
    m_refCollections = new podio::CollRefCollection();
  m_refCollections->push_back(new std::vector<podio::ObjectID>());
  m_refCollections->push_back(new std::vector<podio::ObjectID>());

}

const ParticleClusterAssociation ParticleClusterAssociationCollection::operator[](unsigned int index) const {
  return ParticleClusterAssociation(m_entries[index]);
}

const ParticleClusterAssociation ParticleClusterAssociationCollection::at(unsigned int index) const {
  return ParticleClusterAssociation(m_entries.at(index));
}

int  ParticleClusterAssociationCollection::size() const {
  return m_entries.size();
}

ParticleClusterAssociation ParticleClusterAssociationCollection::create(){
  auto obj = new ParticleClusterAssociationObj();
  m_entries.emplace_back(obj);

  obj->id = {int(m_entries.size()-1),m_collectionID};
  return ParticleClusterAssociation(obj);
}

void ParticleClusterAssociationCollection::clear(){
  m_data->clear();
  for (auto& pointer : (*m_refCollections)) {pointer->clear(); }
  for (auto& item : (*m_rel_Particle)) {item.unlink(); }
  m_rel_Particle->clear();
  for (auto& item : (*m_rel_Cluster)) {item.unlink(); }
  m_rel_Cluster->clear();

  for (auto& obj : m_entries) { delete obj; }
  m_entries.clear();
}

void ParticleClusterAssociationCollection::prepareForWrite(){
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
if (obj->m_Particle != nullptr){
(*m_refCollections)[0]->emplace_back(obj->m_Particle->getObjectID());} else {(*m_refCollections)[0]->push_back({-2,-2}); } }
  for (auto& obj : m_entries) {
if (obj->m_Cluster != nullptr){
(*m_refCollections)[1]->emplace_back(obj->m_Cluster->getObjectID());} else {(*m_refCollections)[1]->push_back({-2,-2}); } }

}

void ParticleClusterAssociationCollection::prepareAfterRead(){
  int index = 0;
  for (auto& data : *m_data){
    auto obj = new ParticleClusterAssociationObj({index,m_collectionID}, data);
    
    m_entries.emplace_back(obj);
    ++index;
  }
}

bool ParticleClusterAssociationCollection::setReferences(const podio::ICollectionProvider* collectionProvider){

  for(unsigned int i=0, size=m_entries.size();i!=size;++i ) {
    auto id = (*(*m_refCollections)[0])[i];
    if (id.index != podio::ObjectID::invalid) {
      CollectionBase* coll = nullptr;
      collectionProvider->get(id.collectionID,coll);
      ParticleCollection* tmp_coll = static_cast<ParticleCollection*>(coll);
      m_entries[i]->m_Particle = new ConstParticle((*tmp_coll)[id.index]);
    } else {
      m_entries[i]->m_Particle = nullptr;
    }
  }
  for(unsigned int i=0, size=m_entries.size();i!=size;++i ) {
    auto id = (*(*m_refCollections)[1])[i];
    if (id.index != podio::ObjectID::invalid) {
      CollectionBase* coll = nullptr;
      collectionProvider->get(id.collectionID,coll);
      CaloClusterCollection* tmp_coll = static_cast<CaloClusterCollection*>(coll);
      m_entries[i]->m_Cluster = new ConstCaloCluster((*tmp_coll)[id.index]);
    } else {
      m_entries[i]->m_Cluster = nullptr;
    }
  }

  return true; //TODO: check success
}

void ParticleClusterAssociationCollection::push_back(ConstParticleClusterAssociation object){
    int size = m_entries.size();
    auto obj = object.m_obj;
    if (obj->id.index == podio::ObjectID::untracked) {
        obj->id = {size,m_collectionID};
        m_entries.push_back(obj);
        
    } else {
      throw std::invalid_argument( "Object already in a collection. Cannot add it to a second collection " );

    }
}

void ParticleClusterAssociationCollection::setBuffer(void* address){
  m_data = static_cast<ParticleClusterAssociationDataContainer*>(address);
}


const ParticleClusterAssociation ParticleClusterAssociationCollectionIterator::operator* () const {
  m_object.m_obj = (*m_collection)[m_index];
  return m_object;
}

const ParticleClusterAssociation* ParticleClusterAssociationCollectionIterator::operator-> () const {
    m_object.m_obj = (*m_collection)[m_index];
    return &m_object;
}

const ParticleClusterAssociationCollectionIterator& ParticleClusterAssociationCollectionIterator::operator++() const {
  ++m_index;
 return *this;
}


