// standard includes
#include <stdexcept>


#include "GenJetCollection.h"

namespace fcc {

GenJetCollection::GenJetCollection() : m_collectionID(0), m_entries() ,m_refCollections(nullptr), m_data(new GenJetDataContainer() ) {
  
}

const GenJet GenJetCollection::operator[](unsigned int index) const {
  return GenJet(m_entries[index]);
}

const GenJet GenJetCollection::at(unsigned int index) const {
  return GenJet(m_entries.at(index));
}

int  GenJetCollection::size() const {
  return m_entries.size();
}

GenJet GenJetCollection::create(){
  auto obj = new GenJetObj();
  m_entries.emplace_back(obj);

  obj->id = {int(m_entries.size()-1),m_collectionID};
  return GenJet(obj);
}

void GenJetCollection::clear(){
  m_data->clear();

  for (auto& obj : m_entries) { delete obj; }
  m_entries.clear();
}

void GenJetCollection::prepareForWrite(){
  int index = 0;
  auto size = m_entries.size();
  m_data->reserve(size);
  for (auto& obj : m_entries) {m_data->push_back(obj->data); }
  if (m_refCollections != nullptr) {
    for (auto& pointer : (*m_refCollections)) {pointer->clear(); }
  }
  
  for(int i=0, size = m_data->size(); i != size; ++i){
  
  }
  
}

void GenJetCollection::prepareAfterRead(){
  int index = 0;
  for (auto& data : *m_data){
    auto obj = new GenJetObj({index,m_collectionID}, data);
    
    m_entries.emplace_back(obj);
    ++index;
  }
}

bool GenJetCollection::setReferences(const podio::ICollectionProvider* collectionProvider){


  return true; //TODO: check success
}

void GenJetCollection::push_back(ConstGenJet object){
    int size = m_entries.size();
    auto obj = object.m_obj;
    if (obj->id.index == podio::ObjectID::untracked) {
        obj->id = {size,m_collectionID};
        m_entries.push_back(obj);
        
    } else {
      throw std::invalid_argument( "Object already in a collection. Cannot add it to a second collection " );

    }
}

void GenJetCollection::setBuffer(void* address){
  m_data = static_cast<GenJetDataContainer*>(address);
}


const GenJet GenJetCollectionIterator::operator* () const {
  m_object.m_obj = (*m_collection)[m_index];
  return m_object;
}

const GenJet* GenJetCollectionIterator::operator-> () const {
    m_object.m_obj = (*m_collection)[m_index];
    return &m_object;
}

const GenJetCollectionIterator& GenJetCollectionIterator::operator++() const {
  ++m_index;
 return *this;
}

} // namespace fcc
