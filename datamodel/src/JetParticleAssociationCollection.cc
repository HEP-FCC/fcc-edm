// standard includes
#include <stdexcept>
#include "JetCollection.h" 
#include "ParticleCollection.h" 


#include "JetParticleAssociationCollection.h"

namespace fcc {

JetParticleAssociationCollection::JetParticleAssociationCollection() : m_collectionID(0), m_entries() ,m_rel_Jet(new std::vector<::fcc::ConstJet>()),m_rel_Particle(new std::vector<::fcc::ConstParticle>()),m_refCollections(nullptr), m_data(new JetParticleAssociationDataContainer() ) {
    m_refCollections = new podio::CollRefCollection();
  m_refCollections->push_back(new std::vector<podio::ObjectID>());
  m_refCollections->push_back(new std::vector<podio::ObjectID>());

}

const JetParticleAssociation JetParticleAssociationCollection::operator[](unsigned int index) const {
  return JetParticleAssociation(m_entries[index]);
}

const JetParticleAssociation JetParticleAssociationCollection::at(unsigned int index) const {
  return JetParticleAssociation(m_entries.at(index));
}

int  JetParticleAssociationCollection::size() const {
  return m_entries.size();
}

JetParticleAssociation JetParticleAssociationCollection::create(){
  auto obj = new JetParticleAssociationObj();
  m_entries.emplace_back(obj);

  obj->id = {int(m_entries.size()-1),m_collectionID};
  return JetParticleAssociation(obj);
}

void JetParticleAssociationCollection::clear(){
  m_data->clear();
  for (auto& pointer : (*m_refCollections)) {pointer->clear(); }
  for (auto& item : (*m_rel_Jet)) {item.unlink(); }
  m_rel_Jet->clear();
  for (auto& item : (*m_rel_Particle)) {item.unlink(); }
  m_rel_Particle->clear();

  for (auto& obj : m_entries) { delete obj; }
  m_entries.clear();
}

void JetParticleAssociationCollection::prepareForWrite(){
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

void JetParticleAssociationCollection::prepareAfterRead(){
  int index = 0;
  for (auto& data : *m_data){
    auto obj = new JetParticleAssociationObj({index,m_collectionID}, data);
    
    m_entries.emplace_back(obj);
    ++index;
  }
}

bool JetParticleAssociationCollection::setReferences(const podio::ICollectionProvider* collectionProvider){

  for(unsigned int i=0, size=m_entries.size();i!=size;++i ) {
    auto id = (*(*m_refCollections)[0])[i];
    if (id.index != podio::ObjectID::invalid) {
      CollectionBase* coll = nullptr;
      collectionProvider->get(id.collectionID,coll);
      fcc::JetCollection* tmp_coll = static_cast<fcc::JetCollection*>(coll);
      m_entries[i]->m_Jet = new ConstJet((*tmp_coll)[id.index]);
    } else {
      m_entries[i]->m_Jet = nullptr;
    }
  }
  for(unsigned int i=0, size=m_entries.size();i!=size;++i ) {
    auto id = (*(*m_refCollections)[1])[i];
    if (id.index != podio::ObjectID::invalid) {
      CollectionBase* coll = nullptr;
      collectionProvider->get(id.collectionID,coll);
      fcc::ParticleCollection* tmp_coll = static_cast<fcc::ParticleCollection*>(coll);
      m_entries[i]->m_Particle = new ConstParticle((*tmp_coll)[id.index]);
    } else {
      m_entries[i]->m_Particle = nullptr;
    }
  }

  return true; //TODO: check success
}

void JetParticleAssociationCollection::push_back(ConstJetParticleAssociation object){
    int size = m_entries.size();
    auto obj = object.m_obj;
    if (obj->id.index == podio::ObjectID::untracked) {
        obj->id = {size,m_collectionID};
        m_entries.push_back(obj);
        
    } else {
      throw std::invalid_argument( "Object already in a collection. Cannot add it to a second collection " );

    }
}

void JetParticleAssociationCollection::setBuffer(void* address){
  m_data = static_cast<JetParticleAssociationDataContainer*>(address);
}


const JetParticleAssociation JetParticleAssociationCollectionIterator::operator* () const {
  m_object.m_obj = (*m_collection)[m_index];
  return m_object;
}

const JetParticleAssociation* JetParticleAssociationCollectionIterator::operator-> () const {
    m_object.m_obj = (*m_collection)[m_index];
    return &m_object;
}

const JetParticleAssociationCollectionIterator& JetParticleAssociationCollectionIterator::operator++() const {
  ++m_index;
 return *this;
}

} // namespace fcc
