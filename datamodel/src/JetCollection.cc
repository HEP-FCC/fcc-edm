// standard includes
#include <stdexcept>


#include "JetCollection.h"

namespace fcc {

JetCollection::JetCollection() : m_isValid(false), m_collectionID(0), m_entries() ,m_data(new JetDataContainer() ) {
  
}

JetCollection::~JetCollection() {
  clear();
  if (m_data != nullptr) delete m_data;
  
};

const Jet JetCollection::operator[](unsigned int index) const {
  return Jet(m_entries[index]);
}

const Jet JetCollection::at(unsigned int index) const {
  return Jet(m_entries.at(index));
}

int  JetCollection::size() const {
  return m_entries.size();
}

Jet JetCollection::create(){
  auto obj = new JetObj();
  m_entries.emplace_back(obj);

  obj->id = {int(m_entries.size()-1),m_collectionID};
  return Jet(obj);
}

void JetCollection::clear(){
  m_data->clear();

  for (auto& obj : m_entries) { delete obj; }
  m_entries.clear();
}

void JetCollection::prepareForWrite(){
  auto size = m_entries.size();
  m_data->reserve(size);
  for (auto& obj : m_entries) {m_data->push_back(obj->data); }
  for (auto& pointer : m_refCollections) {pointer->clear(); } 

  for(int i=0, size = m_data->size(); i != size; ++i){

  }

}

void JetCollection::prepareAfterRead(){
  int index = 0;
  for (auto& data : *m_data){
    auto obj = new JetObj({index,m_collectionID}, data);
    
    m_entries.emplace_back(obj);
    ++index;
  }
  m_isValid = true;  
}

bool JetCollection::setReferences(const podio::ICollectionProvider* collectionProvider){


  return true; //TODO: check success
}

void JetCollection::push_back(ConstJet object){
  int size = m_entries.size();
  auto obj = object.m_obj;
  if (obj->id.index == podio::ObjectID::untracked) {
      obj->id = {size,m_collectionID};
      m_entries.push_back(obj);
      
  } else {
    throw std::invalid_argument( "Object already in a collection. Cannot add it to a second collection " );
  }
}

void JetCollection::setBuffer(void* address){
  if (m_data != nullptr) delete m_data;
  m_data = static_cast<JetDataContainer*>(address);
}


const Jet JetCollectionIterator::operator* () const {
  m_object.m_obj = (*m_collection)[m_index];
  return m_object;
}

const Jet* JetCollectionIterator::operator-> () const {
  m_object.m_obj = (*m_collection)[m_index];
  return &m_object;
}

const JetCollectionIterator& JetCollectionIterator::operator++() const {
  ++m_index;
  return *this;
}

} // namespace fcc
