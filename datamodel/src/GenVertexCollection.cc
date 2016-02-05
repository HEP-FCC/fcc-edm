// standard includes
#include <stdexcept>


#include "GenVertexCollection.h"

namespace fcc {

GenVertexCollection::GenVertexCollection() : m_collectionID(0), m_entries() ,m_refCollections(nullptr), m_data(new GenVertexDataContainer() ) {
  
}

const GenVertex GenVertexCollection::operator[](unsigned int index) const {
  return GenVertex(m_entries[index]);
}

const GenVertex GenVertexCollection::at(unsigned int index) const {
  return GenVertex(m_entries.at(index));
}

int  GenVertexCollection::size() const {
  return m_entries.size();
}

GenVertex GenVertexCollection::create(){
  auto obj = new GenVertexObj();
  m_entries.emplace_back(obj);

  obj->id = {int(m_entries.size()-1),m_collectionID};
  return GenVertex(obj);
}

void GenVertexCollection::clear(){
  m_data->clear();

  for (auto& obj : m_entries) { delete obj; }
  m_entries.clear();
}

void GenVertexCollection::prepareForWrite(){
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

void GenVertexCollection::prepareAfterRead(){
  int index = 0;
  for (auto& data : *m_data){
    auto obj = new GenVertexObj({index,m_collectionID}, data);
    
    m_entries.emplace_back(obj);
    ++index;
  }
}

bool GenVertexCollection::setReferences(const podio::ICollectionProvider* collectionProvider){


  return true; //TODO: check success
}

void GenVertexCollection::push_back(ConstGenVertex object){
    int size = m_entries.size();
    auto obj = object.m_obj;
    if (obj->id.index == podio::ObjectID::untracked) {
        obj->id = {size,m_collectionID};
        m_entries.push_back(obj);
        
    } else {
      throw std::invalid_argument( "Object already in a collection. Cannot add it to a second collection " );

    }
}

void GenVertexCollection::setBuffer(void* address){
  m_data = static_cast<GenVertexDataContainer*>(address);
}


const GenVertex GenVertexCollectionIterator::operator* () const {
  m_object.m_obj = (*m_collection)[m_index];
  return m_object;
}

const GenVertex* GenVertexCollectionIterator::operator-> () const {
    m_object.m_obj = (*m_collection)[m_index];
    return &m_object;
}

const GenVertexCollectionIterator& GenVertexCollectionIterator::operator++() const {
  ++m_index;
 return *this;
}

} // namespace fcc
