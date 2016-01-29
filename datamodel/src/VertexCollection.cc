// standard includes
#include <stdexcept>


#include "VertexCollection.h"

namespace fcc {

VertexCollection::VertexCollection() : m_collectionID(0), m_entries() ,m_refCollections(nullptr), m_data(new VertexDataContainer() ) {
  
}

const Vertex VertexCollection::operator[](unsigned int index) const {
  return Vertex(m_entries[index]);
}

const Vertex VertexCollection::at(unsigned int index) const {
  return Vertex(m_entries.at(index));
}

int  VertexCollection::size() const {
  return m_entries.size();
}

Vertex VertexCollection::create(){
  auto obj = new VertexObj();
  m_entries.emplace_back(obj);

  obj->id = {int(m_entries.size()-1),m_collectionID};
  return Vertex(obj);
}

void VertexCollection::clear(){
  m_data->clear();

  for (auto& obj : m_entries) { delete obj; }
  m_entries.clear();
}

void VertexCollection::prepareForWrite(){
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

void VertexCollection::prepareAfterRead(){
  int index = 0;
  for (auto& data : *m_data){
    auto obj = new VertexObj({index,m_collectionID}, data);
    
    m_entries.emplace_back(obj);
    ++index;
  }
}

bool VertexCollection::setReferences(const podio::ICollectionProvider* collectionProvider){


  return true; //TODO: check success
}

void VertexCollection::push_back(ConstVertex object){
    int size = m_entries.size();
    auto obj = object.m_obj;
    if (obj->id.index == podio::ObjectID::untracked) {
        obj->id = {size,m_collectionID};
        m_entries.push_back(obj);
        
    } else {
      throw std::invalid_argument( "Object already in a collection. Cannot add it to a second collection " );

    }
}

void VertexCollection::setBuffer(void* address){
  m_data = static_cast<VertexDataContainer*>(address);
}


const Vertex VertexCollectionIterator::operator* () const {
  m_object.m_obj = (*m_collection)[m_index];
  return m_object;
}

const Vertex* VertexCollectionIterator::operator-> () const {
    m_object.m_obj = (*m_collection)[m_index];
    return &m_object;
}

const VertexCollectionIterator& VertexCollectionIterator::operator++() const {
  ++m_index;
 return *this;
}

} // namespace fcc
