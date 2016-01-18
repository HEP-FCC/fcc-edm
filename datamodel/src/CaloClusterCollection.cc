// standard includes
#include <stdexcept>


#include "CaloClusterCollection.h"



CaloClusterCollection::CaloClusterCollection() : m_collectionID(0), m_entries() ,m_refCollections(nullptr), m_data(new CaloClusterDataContainer() ) {
  
}

const CaloCluster CaloClusterCollection::operator[](unsigned int index) const {
  return CaloCluster(m_entries[index]);
}

const CaloCluster CaloClusterCollection::at(unsigned int index) const {
  return CaloCluster(m_entries.at(index));
}

int  CaloClusterCollection::size() const {
  return m_entries.size();
}

CaloCluster CaloClusterCollection::create(){
  auto obj = new CaloClusterObj();
  m_entries.emplace_back(obj);

  obj->id = {int(m_entries.size()-1),m_collectionID};
  return CaloCluster(obj);
}

void CaloClusterCollection::clear(){
  m_data->clear();

  for (auto& obj : m_entries) { delete obj; }
  m_entries.clear();
}

void CaloClusterCollection::prepareForWrite(){
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

void CaloClusterCollection::prepareAfterRead(){
  int index = 0;
  for (auto& data : *m_data){
    auto obj = new CaloClusterObj({index,m_collectionID}, data);
    
    m_entries.emplace_back(obj);
    ++index;
  }
}

bool CaloClusterCollection::setReferences(const podio::ICollectionProvider* collectionProvider){


  return true; //TODO: check success
}

void CaloClusterCollection::push_back(ConstCaloCluster object){
    int size = m_entries.size();
    auto obj = object.m_obj;
    if (obj->id.index == podio::ObjectID::untracked) {
        obj->id = {size,m_collectionID};
        m_entries.push_back(obj);
        
    } else {
      throw std::invalid_argument( "Object already in a collection. Cannot add it to a second collection " );

    }
}

void CaloClusterCollection::setBuffer(void* address){
  m_data = static_cast<CaloClusterDataContainer*>(address);
}


const CaloCluster CaloClusterCollectionIterator::operator* () const {
  m_object.m_obj = (*m_collection)[m_index];
  return m_object;
}

const CaloCluster* CaloClusterCollectionIterator::operator-> () const {
    m_object.m_obj = (*m_collection)[m_index];
    return &m_object;
}

const CaloClusterCollectionIterator& CaloClusterCollectionIterator::operator++() const {
  ++m_index;
 return *this;
}


