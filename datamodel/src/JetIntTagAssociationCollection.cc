// standard includes
#include <stdexcept>
#include "JetCollection.h" 
#include "IntTagCollection.h" 


#include "JetIntTagAssociationCollection.h"

namespace fcc {

JetIntTagAssociationCollection::JetIntTagAssociationCollection() : m_collectionID(0), m_entries() ,m_rel_Jet(new std::vector<::fcc::ConstJet>()),m_rel_Tag(new std::vector<::fcc::ConstIntTag>()),m_refCollections(nullptr), m_data(new JetIntTagAssociationDataContainer() ) {
    m_refCollections = new podio::CollRefCollection();
  m_refCollections->push_back(new std::vector<podio::ObjectID>());
  m_refCollections->push_back(new std::vector<podio::ObjectID>());

}

const JetIntTagAssociation JetIntTagAssociationCollection::operator[](unsigned int index) const {
  return JetIntTagAssociation(m_entries[index]);
}

const JetIntTagAssociation JetIntTagAssociationCollection::at(unsigned int index) const {
  return JetIntTagAssociation(m_entries.at(index));
}

int  JetIntTagAssociationCollection::size() const {
  return m_entries.size();
}

JetIntTagAssociation JetIntTagAssociationCollection::create(){
  auto obj = new JetIntTagAssociationObj();
  m_entries.emplace_back(obj);

  obj->id = {int(m_entries.size()-1),m_collectionID};
  return JetIntTagAssociation(obj);
}

void JetIntTagAssociationCollection::clear(){
  m_data->clear();
  for (auto& pointer : (*m_refCollections)) {pointer->clear(); }
  for (auto& item : (*m_rel_Jet)) {item.unlink(); }
  m_rel_Jet->clear();
  for (auto& item : (*m_rel_Tag)) {item.unlink(); }
  m_rel_Tag->clear();

  for (auto& obj : m_entries) { delete obj; }
  m_entries.clear();
}

void JetIntTagAssociationCollection::prepareForWrite(){
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
if (obj->m_Tag != nullptr){
(*m_refCollections)[1]->emplace_back(obj->m_Tag->getObjectID());} else {(*m_refCollections)[1]->push_back({-2,-2}); } }

}

void JetIntTagAssociationCollection::prepareAfterRead(){
  int index = 0;
  for (auto& data : *m_data){
    auto obj = new JetIntTagAssociationObj({index,m_collectionID}, data);
    
    m_entries.emplace_back(obj);
    ++index;
  }
}

bool JetIntTagAssociationCollection::setReferences(const podio::ICollectionProvider* collectionProvider){

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
      fcc::IntTagCollection* tmp_coll = static_cast<fcc::IntTagCollection*>(coll);
      m_entries[i]->m_Tag = new ConstIntTag((*tmp_coll)[id.index]);
    } else {
      m_entries[i]->m_Tag = nullptr;
    }
  }

  return true; //TODO: check success
}

void JetIntTagAssociationCollection::push_back(ConstJetIntTagAssociation object){
    int size = m_entries.size();
    auto obj = object.m_obj;
    if (obj->id.index == podio::ObjectID::untracked) {
        obj->id = {size,m_collectionID};
        m_entries.push_back(obj);
        
    } else {
      throw std::invalid_argument( "Object already in a collection. Cannot add it to a second collection " );

    }
}

void JetIntTagAssociationCollection::setBuffer(void* address){
  m_data = static_cast<JetIntTagAssociationDataContainer*>(address);
}


const JetIntTagAssociation JetIntTagAssociationCollectionIterator::operator* () const {
  m_object.m_obj = (*m_collection)[m_index];
  return m_object;
}

const JetIntTagAssociation* JetIntTagAssociationCollectionIterator::operator-> () const {
    m_object.m_obj = (*m_collection)[m_index];
    return &m_object;
}

const JetIntTagAssociationCollectionIterator& JetIntTagAssociationCollectionIterator::operator++() const {
  ++m_index;
 return *this;
}

} // namespace fcc
