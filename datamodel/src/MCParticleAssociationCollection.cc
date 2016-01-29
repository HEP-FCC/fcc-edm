// standard includes
#include <stdexcept>
#include "MCParticleCollection.h" 
#include "MCParticleCollection.h" 


#include "MCParticleAssociationCollection.h"

namespace fcc {

MCParticleAssociationCollection::MCParticleAssociationCollection() : m_collectionID(0), m_entries() ,m_rel_Mother(new std::vector<::fcc::ConstMCParticle>()),m_rel_Daughter(new std::vector<::fcc::ConstMCParticle>()),m_refCollections(nullptr), m_data(new MCParticleAssociationDataContainer() ) {
    m_refCollections = new podio::CollRefCollection();
  m_refCollections->push_back(new std::vector<podio::ObjectID>());
  m_refCollections->push_back(new std::vector<podio::ObjectID>());

}

const MCParticleAssociation MCParticleAssociationCollection::operator[](unsigned int index) const {
  return MCParticleAssociation(m_entries[index]);
}

const MCParticleAssociation MCParticleAssociationCollection::at(unsigned int index) const {
  return MCParticleAssociation(m_entries.at(index));
}

int  MCParticleAssociationCollection::size() const {
  return m_entries.size();
}

MCParticleAssociation MCParticleAssociationCollection::create(){
  auto obj = new MCParticleAssociationObj();
  m_entries.emplace_back(obj);

  obj->id = {int(m_entries.size()-1),m_collectionID};
  return MCParticleAssociation(obj);
}

void MCParticleAssociationCollection::clear(){
  m_data->clear();
  for (auto& pointer : (*m_refCollections)) {pointer->clear(); }
  for (auto& item : (*m_rel_Mother)) {item.unlink(); }
  m_rel_Mother->clear();
  for (auto& item : (*m_rel_Daughter)) {item.unlink(); }
  m_rel_Daughter->clear();

  for (auto& obj : m_entries) { delete obj; }
  m_entries.clear();
}

void MCParticleAssociationCollection::prepareForWrite(){
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
if (obj->m_Mother != nullptr){
(*m_refCollections)[0]->emplace_back(obj->m_Mother->getObjectID());} else {(*m_refCollections)[0]->push_back({-2,-2}); } }
  for (auto& obj : m_entries) {
if (obj->m_Daughter != nullptr){
(*m_refCollections)[1]->emplace_back(obj->m_Daughter->getObjectID());} else {(*m_refCollections)[1]->push_back({-2,-2}); } }

}

void MCParticleAssociationCollection::prepareAfterRead(){
  int index = 0;
  for (auto& data : *m_data){
    auto obj = new MCParticleAssociationObj({index,m_collectionID}, data);
    
    m_entries.emplace_back(obj);
    ++index;
  }
}

bool MCParticleAssociationCollection::setReferences(const podio::ICollectionProvider* collectionProvider){

  for(unsigned int i=0, size=m_entries.size();i!=size;++i ) {
    auto id = (*(*m_refCollections)[0])[i];
    if (id.index != podio::ObjectID::invalid) {
      CollectionBase* coll = nullptr;
      collectionProvider->get(id.collectionID,coll);
      fcc::MCParticleCollection* tmp_coll = static_cast<fcc::MCParticleCollection*>(coll);
      m_entries[i]->m_Mother = new ConstMCParticle((*tmp_coll)[id.index]);
    } else {
      m_entries[i]->m_Mother = nullptr;
    }
  }
  for(unsigned int i=0, size=m_entries.size();i!=size;++i ) {
    auto id = (*(*m_refCollections)[1])[i];
    if (id.index != podio::ObjectID::invalid) {
      CollectionBase* coll = nullptr;
      collectionProvider->get(id.collectionID,coll);
      fcc::MCParticleCollection* tmp_coll = static_cast<fcc::MCParticleCollection*>(coll);
      m_entries[i]->m_Daughter = new ConstMCParticle((*tmp_coll)[id.index]);
    } else {
      m_entries[i]->m_Daughter = nullptr;
    }
  }

  return true; //TODO: check success
}

void MCParticleAssociationCollection::push_back(ConstMCParticleAssociation object){
    int size = m_entries.size();
    auto obj = object.m_obj;
    if (obj->id.index == podio::ObjectID::untracked) {
        obj->id = {size,m_collectionID};
        m_entries.push_back(obj);
        
    } else {
      throw std::invalid_argument( "Object already in a collection. Cannot add it to a second collection " );

    }
}

void MCParticleAssociationCollection::setBuffer(void* address){
  m_data = static_cast<MCParticleAssociationDataContainer*>(address);
}


const MCParticleAssociation MCParticleAssociationCollectionIterator::operator* () const {
  m_object.m_obj = (*m_collection)[m_index];
  return m_object;
}

const MCParticleAssociation* MCParticleAssociationCollectionIterator::operator-> () const {
    m_object.m_obj = (*m_collection)[m_index];
    return &m_object;
}

const MCParticleAssociationCollectionIterator& MCParticleAssociationCollectionIterator::operator++() const {
  ++m_index;
 return *this;
}

} // namespace fcc
