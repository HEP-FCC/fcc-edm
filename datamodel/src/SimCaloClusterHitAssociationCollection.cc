// standard includes
#include <stdexcept>
#include "SimCaloClusterCollection.h" 
#include "SimCaloHitCollection.h" 


#include "SimCaloClusterHitAssociationCollection.h"

namespace fcc {

SimCaloClusterHitAssociationCollection::SimCaloClusterHitAssociationCollection() : m_collectionID(0), m_entries() ,m_rel_Cluster(new std::vector<::fcc::ConstSimCaloCluster>()),m_rel_Hit(new std::vector<::fcc::ConstSimCaloHit>()),m_refCollections(nullptr), m_data(new SimCaloClusterHitAssociationDataContainer() ) {
    m_refCollections = new podio::CollRefCollection();
  m_refCollections->push_back(new std::vector<podio::ObjectID>());
  m_refCollections->push_back(new std::vector<podio::ObjectID>());

}

const SimCaloClusterHitAssociation SimCaloClusterHitAssociationCollection::operator[](unsigned int index) const {
  return SimCaloClusterHitAssociation(m_entries[index]);
}

const SimCaloClusterHitAssociation SimCaloClusterHitAssociationCollection::at(unsigned int index) const {
  return SimCaloClusterHitAssociation(m_entries.at(index));
}

int  SimCaloClusterHitAssociationCollection::size() const {
  return m_entries.size();
}

SimCaloClusterHitAssociation SimCaloClusterHitAssociationCollection::create(){
  auto obj = new SimCaloClusterHitAssociationObj();
  m_entries.emplace_back(obj);

  obj->id = {int(m_entries.size()-1),m_collectionID};
  return SimCaloClusterHitAssociation(obj);
}

void SimCaloClusterHitAssociationCollection::clear(){
  m_data->clear();
  for (auto& pointer : (*m_refCollections)) {pointer->clear(); }
  for (auto& item : (*m_rel_Cluster)) {item.unlink(); }
  m_rel_Cluster->clear();
  for (auto& item : (*m_rel_Hit)) {item.unlink(); }
  m_rel_Hit->clear();

  for (auto& obj : m_entries) { delete obj; }
  m_entries.clear();
}

void SimCaloClusterHitAssociationCollection::prepareForWrite(){
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
if (obj->m_Cluster != nullptr){
(*m_refCollections)[0]->emplace_back(obj->m_Cluster->getObjectID());} else {(*m_refCollections)[0]->push_back({-2,-2}); } }
  for (auto& obj : m_entries) {
if (obj->m_Hit != nullptr){
(*m_refCollections)[1]->emplace_back(obj->m_Hit->getObjectID());} else {(*m_refCollections)[1]->push_back({-2,-2}); } }

}

void SimCaloClusterHitAssociationCollection::prepareAfterRead(){
  int index = 0;
  for (auto& data : *m_data){
    auto obj = new SimCaloClusterHitAssociationObj({index,m_collectionID}, data);
    
    m_entries.emplace_back(obj);
    ++index;
  }
}

bool SimCaloClusterHitAssociationCollection::setReferences(const podio::ICollectionProvider* collectionProvider){

  for(unsigned int i=0, size=m_entries.size();i!=size;++i ) {
    auto id = (*(*m_refCollections)[0])[i];
    if (id.index != podio::ObjectID::invalid) {
      CollectionBase* coll = nullptr;
      collectionProvider->get(id.collectionID,coll);
      fcc::SimCaloClusterCollection* tmp_coll = static_cast<fcc::SimCaloClusterCollection*>(coll);
      m_entries[i]->m_Cluster = new ConstSimCaloCluster((*tmp_coll)[id.index]);
    } else {
      m_entries[i]->m_Cluster = nullptr;
    }
  }
  for(unsigned int i=0, size=m_entries.size();i!=size;++i ) {
    auto id = (*(*m_refCollections)[1])[i];
    if (id.index != podio::ObjectID::invalid) {
      CollectionBase* coll = nullptr;
      collectionProvider->get(id.collectionID,coll);
      fcc::SimCaloHitCollection* tmp_coll = static_cast<fcc::SimCaloHitCollection*>(coll);
      m_entries[i]->m_Hit = new ConstSimCaloHit((*tmp_coll)[id.index]);
    } else {
      m_entries[i]->m_Hit = nullptr;
    }
  }

  return true; //TODO: check success
}

void SimCaloClusterHitAssociationCollection::push_back(ConstSimCaloClusterHitAssociation object){
    int size = m_entries.size();
    auto obj = object.m_obj;
    if (obj->id.index == podio::ObjectID::untracked) {
        obj->id = {size,m_collectionID};
        m_entries.push_back(obj);
        
    } else {
      throw std::invalid_argument( "Object already in a collection. Cannot add it to a second collection " );

    }
}

void SimCaloClusterHitAssociationCollection::setBuffer(void* address){
  m_data = static_cast<SimCaloClusterHitAssociationDataContainer*>(address);
}


const SimCaloClusterHitAssociation SimCaloClusterHitAssociationCollectionIterator::operator* () const {
  m_object.m_obj = (*m_collection)[m_index];
  return m_object;
}

const SimCaloClusterHitAssociation* SimCaloClusterHitAssociationCollectionIterator::operator-> () const {
    m_object.m_obj = (*m_collection)[m_index];
    return &m_object;
}

const SimCaloClusterHitAssociationCollectionIterator& SimCaloClusterHitAssociationCollectionIterator::operator++() const {
  ++m_index;
 return *this;
}

} // namespace fcc
