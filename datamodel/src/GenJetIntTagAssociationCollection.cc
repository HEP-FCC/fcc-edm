// standard includes
#include <stdexcept>
#include "GenJetCollection.h"
#include "IntTagCollection.h"


#include "GenJetIntTagAssociationCollection.h"

namespace fcc {

GenJetIntTagAssociationCollection::GenJetIntTagAssociationCollection() : m_isValid(false), m_collectionID(0), m_entries() , m_rel_Jet(new std::vector<fcc::ConstGenJet>()), m_rel_Tag(new std::vector<fcc::ConstIntTag>()),m_data(new GenJetIntTagAssociationDataContainer() ) {
    m_refCollections.push_back(new std::vector<podio::ObjectID>());
  m_refCollections.push_back(new std::vector<podio::ObjectID>());

}

GenJetIntTagAssociationCollection::~GenJetIntTagAssociationCollection() {
  clear();
  if (m_data != nullptr) delete m_data;
    for (auto& pointer : m_refCollections) { if (pointer != nullptr) delete pointer; }
  if (m_rel_Jet != nullptr) { delete m_rel_Jet; }
  if (m_rel_Tag != nullptr) { delete m_rel_Tag; }

};

const GenJetIntTagAssociation GenJetIntTagAssociationCollection::operator[](unsigned int index) const {
  return GenJetIntTagAssociation(m_entries[index]);
}

const GenJetIntTagAssociation GenJetIntTagAssociationCollection::at(unsigned int index) const {
  return GenJetIntTagAssociation(m_entries.at(index));
}

int  GenJetIntTagAssociationCollection::size() const {
  return m_entries.size();
}

GenJetIntTagAssociation GenJetIntTagAssociationCollection::create(){
  auto obj = new GenJetIntTagAssociationObj();
  m_entries.emplace_back(obj);

  obj->id = {int(m_entries.size()-1),m_collectionID};
  return GenJetIntTagAssociation(obj);
}

void GenJetIntTagAssociationCollection::clear(){
  m_data->clear();
  for (auto& pointer : m_refCollections) { pointer->clear(); }
  for (auto& item : (*m_rel_Jet)) { item.unlink(); }
  m_rel_Jet->clear();
  for (auto& item : (*m_rel_Tag)) { item.unlink(); }
  m_rel_Tag->clear();

  for (auto& obj : m_entries) { delete obj; }
  m_entries.clear();
}

void GenJetIntTagAssociationCollection::prepareForWrite(){
  auto size = m_entries.size();
  m_data->reserve(size);
  for (auto& obj : m_entries) {m_data->push_back(obj->data); }
  for (auto& pointer : m_refCollections) {pointer->clear(); } 

  for(int i=0, size = m_data->size(); i != size; ++i){

  }
  for (auto& obj : m_entries) {
    if (obj->m_Jet != nullptr) {
      m_refCollections[0]->emplace_back(obj->m_Jet->getObjectID());
    } else {
      m_refCollections[0]->push_back({-2,-2});
    }
  }
  for (auto& obj : m_entries) {
    if (obj->m_Tag != nullptr) {
      m_refCollections[1]->emplace_back(obj->m_Tag->getObjectID());
    } else {
      m_refCollections[1]->push_back({-2,-2});
    }
  }

}

void GenJetIntTagAssociationCollection::prepareAfterRead(){
  int index = 0;
  for (auto& data : *m_data){
    auto obj = new GenJetIntTagAssociationObj({index,m_collectionID}, data);
    
    m_entries.emplace_back(obj);
    ++index;
  }
  m_isValid = true;  
}

bool GenJetIntTagAssociationCollection::setReferences(const podio::ICollectionProvider* collectionProvider){

  for(unsigned int i = 0, size = m_entries.size(); i != size; ++i) {
    auto id = (*m_refCollections[0])[i];
    if (id.index != podio::ObjectID::invalid) {
      CollectionBase* coll = nullptr;
      collectionProvider->get(id.collectionID,coll);
      fcc::GenJetCollection* tmp_coll = static_cast<fcc::GenJetCollection*>(coll);
      m_entries[i]->m_Jet = new ConstGenJet((*tmp_coll)[id.index]);
    } else {
      m_entries[i]->m_Jet = nullptr;
    }
  }
  for(unsigned int i = 0, size = m_entries.size(); i != size; ++i) {
    auto id = (*m_refCollections[1])[i];
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

void GenJetIntTagAssociationCollection::push_back(ConstGenJetIntTagAssociation object){
  int size = m_entries.size();
  auto obj = object.m_obj;
  if (obj->id.index == podio::ObjectID::untracked) {
      obj->id = {size,m_collectionID};
      m_entries.push_back(obj);
      
  } else {
    throw std::invalid_argument( "Object already in a collection. Cannot add it to a second collection " );
  }
}

void GenJetIntTagAssociationCollection::setBuffer(void* address){
  if (m_data != nullptr) delete m_data;
  m_data = static_cast<GenJetIntTagAssociationDataContainer*>(address);
}


const GenJetIntTagAssociation GenJetIntTagAssociationCollectionIterator::operator* () const {
  m_object.m_obj = (*m_collection)[m_index];
  return m_object;
}

const GenJetIntTagAssociation* GenJetIntTagAssociationCollectionIterator::operator-> () const {
  m_object.m_obj = (*m_collection)[m_index];
  return &m_object;
}

const GenJetIntTagAssociationCollectionIterator& GenJetIntTagAssociationCollectionIterator::operator++() const {
  ++m_index;
  return *this;
}

} // namespace fcc
