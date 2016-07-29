// standard includes
#include <stdexcept>
#include "JetCollection.h"


#include "TaggedJetCollection.h"

namespace fcc {

TaggedJetCollection::TaggedJetCollection() : m_isValid(false), m_collectionID(0), m_entries() , m_rel_jet(new std::vector<fcc::ConstJet>()),m_data(new TaggedJetDataContainer() ) {
    m_refCollections.push_back(new std::vector<podio::ObjectID>());

}

TaggedJetCollection::~TaggedJetCollection() {
  clear();
  if (m_data != nullptr) delete m_data;
    for (auto& pointer : m_refCollections) { if (pointer != nullptr) delete pointer; }
  if (m_rel_jet != nullptr) { delete m_rel_jet; }

}

const TaggedJet TaggedJetCollection::operator[](unsigned int index) const {
  return TaggedJet(m_entries[index]);
}

const TaggedJet TaggedJetCollection::at(unsigned int index) const {
  return TaggedJet(m_entries.at(index));
}

int  TaggedJetCollection::size() const {
  return m_entries.size();
}

TaggedJet TaggedJetCollection::create(){
  auto obj = new TaggedJetObj();
  m_entries.emplace_back(obj);

  obj->id = {int(m_entries.size()-1),m_collectionID};
  return TaggedJet(obj);
}

void TaggedJetCollection::clear(){
  m_data->clear();
  for (auto& pointer : m_refCollections) { pointer->clear(); }
  for (auto& item : (*m_rel_jet)) { item.unlink(); }
  m_rel_jet->clear();

  for (auto& obj : m_entries) { delete obj; }
  m_entries.clear();
}

void TaggedJetCollection::prepareForWrite(){
  auto size = m_entries.size();
  m_data->reserve(size);
  for (auto& obj : m_entries) {m_data->push_back(obj->data); }
  for (auto& pointer : m_refCollections) {pointer->clear(); } 

  for(int i=0, size = m_data->size(); i != size; ++i){

  }
  for (auto& obj : m_entries) {
    if (obj->m_jet != nullptr) {
      m_refCollections[0]->emplace_back(obj->m_jet->getObjectID());
    } else {
      m_refCollections[0]->push_back({-2,-2});
    }
  }

}

void TaggedJetCollection::prepareAfterRead(){
  int index = 0;
  for (auto& data : *m_data){
    auto obj = new TaggedJetObj({index,m_collectionID}, data);
    
    m_entries.emplace_back(obj);
    ++index;
  }
  m_isValid = true;  
}

bool TaggedJetCollection::setReferences(const podio::ICollectionProvider* collectionProvider){

  for(unsigned int i = 0, size = m_entries.size(); i != size; ++i) {
    auto id = (*m_refCollections[0])[i];
    if (id.index != podio::ObjectID::invalid) {
      CollectionBase* coll = nullptr;
      collectionProvider->get(id.collectionID,coll);
      fcc::JetCollection* tmp_coll = static_cast<fcc::JetCollection*>(coll);
      m_entries[i]->m_jet = new ConstJet((*tmp_coll)[id.index]);
    } else {
      m_entries[i]->m_jet = nullptr;
    }
  }

  return true; //TODO: check success
}

void TaggedJetCollection::push_back(ConstTaggedJet object){
  int size = m_entries.size();
  auto obj = object.m_obj;
  if (obj->id.index == podio::ObjectID::untracked) {
      obj->id = {size,m_collectionID};
      m_entries.push_back(obj);
      
  } else {
    throw std::invalid_argument( "Object already in a collection. Cannot add it to a second collection " );
  }
}

void TaggedJetCollection::setBuffer(void* address){
  if (m_data != nullptr) delete m_data;
  m_data = static_cast<TaggedJetDataContainer*>(address);
}


const TaggedJet TaggedJetCollectionIterator::operator* () const {
  m_object.m_obj = (*m_collection)[m_index];
  return m_object;
}

const TaggedJet* TaggedJetCollectionIterator::operator-> () const {
  m_object.m_obj = (*m_collection)[m_index];
  return &m_object;
}

const TaggedJetCollectionIterator& TaggedJetCollectionIterator::operator++() const {
  ++m_index;
  return *this;
}

} // namespace fcc
