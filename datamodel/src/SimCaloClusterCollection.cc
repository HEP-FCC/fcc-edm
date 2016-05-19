// standard includes
#include <stdexcept>


#include "SimCaloClusterCollection.h"

namespace fcc {

SimCaloClusterCollection::SimCaloClusterCollection() : m_isValid(false), m_collectionID(0), m_entries() ,m_data(new SimCaloClusterDataContainer() ) {
  
}

SimCaloClusterCollection::~SimCaloClusterCollection() {
  clear();
  if (m_data != nullptr) delete m_data;
  
};

const SimCaloCluster SimCaloClusterCollection::operator[](unsigned int index) const {
  return SimCaloCluster(m_entries[index]);
}

const SimCaloCluster SimCaloClusterCollection::at(unsigned int index) const {
  return SimCaloCluster(m_entries.at(index));
}

int  SimCaloClusterCollection::size() const {
  return m_entries.size();
}

SimCaloCluster SimCaloClusterCollection::create(){
  auto obj = new SimCaloClusterObj();
  m_entries.emplace_back(obj);

  obj->id = {int(m_entries.size()-1),m_collectionID};
  return SimCaloCluster(obj);
}

void SimCaloClusterCollection::clear(){
  m_data->clear();

  for (auto& obj : m_entries) { delete obj; }
  m_entries.clear();
}

void SimCaloClusterCollection::prepareForWrite(){
  auto size = m_entries.size();
  m_data->reserve(size);
  for (auto& obj : m_entries) {m_data->push_back(obj->data); }
  for (auto& pointer : m_refCollections) {pointer->clear(); } 

  for(int i=0, size = m_data->size(); i != size; ++i){

  }

}

void SimCaloClusterCollection::prepareAfterRead(){
  int index = 0;
  for (auto& data : *m_data){
    auto obj = new SimCaloClusterObj({index,m_collectionID}, data);
    
    m_entries.emplace_back(obj);
    ++index;
  }
  m_isValid = true;  
}

bool SimCaloClusterCollection::setReferences(const podio::ICollectionProvider* collectionProvider){


  return true; //TODO: check success
}

void SimCaloClusterCollection::push_back(ConstSimCaloCluster object){
  int size = m_entries.size();
  auto obj = object.m_obj;
  if (obj->id.index == podio::ObjectID::untracked) {
      obj->id = {size,m_collectionID};
      m_entries.push_back(obj);
      
  } else {
    throw std::invalid_argument( "Object already in a collection. Cannot add it to a second collection " );
  }
}

void SimCaloClusterCollection::setBuffer(void* address){
  if (m_data != nullptr) delete m_data;
  m_data = static_cast<SimCaloClusterDataContainer*>(address);
}


const SimCaloCluster SimCaloClusterCollectionIterator::operator* () const {
  m_object.m_obj = (*m_collection)[m_index];
  return m_object;
}

const SimCaloCluster* SimCaloClusterCollectionIterator::operator-> () const {
  m_object.m_obj = (*m_collection)[m_index];
  return &m_object;
}

const SimCaloClusterCollectionIterator& SimCaloClusterCollectionIterator::operator++() const {
  ++m_index;
  return *this;
}

} // namespace fcc
