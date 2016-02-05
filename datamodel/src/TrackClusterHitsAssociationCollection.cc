// standard includes
#include <stdexcept>
#include "TrackClusterCollection.h" 
#include "TrackHitCollection.h" 


#include "TrackClusterHitsAssociationCollection.h"

namespace fcc {

TrackClusterHitsAssociationCollection::TrackClusterHitsAssociationCollection() : m_collectionID(0), m_entries() ,m_rel_Cluster(new std::vector<::fcc::ConstTrackCluster>()),m_rel_Hit(new std::vector<::fcc::ConstTrackHit>()),m_refCollections(nullptr), m_data(new TrackClusterHitsAssociationDataContainer() ) {
    m_refCollections = new podio::CollRefCollection();
  m_refCollections->push_back(new std::vector<podio::ObjectID>());
  m_refCollections->push_back(new std::vector<podio::ObjectID>());

}

const TrackClusterHitsAssociation TrackClusterHitsAssociationCollection::operator[](unsigned int index) const {
  return TrackClusterHitsAssociation(m_entries[index]);
}

const TrackClusterHitsAssociation TrackClusterHitsAssociationCollection::at(unsigned int index) const {
  return TrackClusterHitsAssociation(m_entries.at(index));
}

int  TrackClusterHitsAssociationCollection::size() const {
  return m_entries.size();
}

TrackClusterHitsAssociation TrackClusterHitsAssociationCollection::create(){
  auto obj = new TrackClusterHitsAssociationObj();
  m_entries.emplace_back(obj);

  obj->id = {int(m_entries.size()-1),m_collectionID};
  return TrackClusterHitsAssociation(obj);
}

void TrackClusterHitsAssociationCollection::clear(){
  m_data->clear();
  for (auto& pointer : (*m_refCollections)) {pointer->clear(); }
  for (auto& item : (*m_rel_Cluster)) {item.unlink(); }
  m_rel_Cluster->clear();
  for (auto& item : (*m_rel_Hit)) {item.unlink(); }
  m_rel_Hit->clear();

  for (auto& obj : m_entries) { delete obj; }
  m_entries.clear();
}

void TrackClusterHitsAssociationCollection::prepareForWrite(){
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

void TrackClusterHitsAssociationCollection::prepareAfterRead(){
  int index = 0;
  for (auto& data : *m_data){
    auto obj = new TrackClusterHitsAssociationObj({index,m_collectionID}, data);
    
    m_entries.emplace_back(obj);
    ++index;
  }
}

bool TrackClusterHitsAssociationCollection::setReferences(const podio::ICollectionProvider* collectionProvider){

  for(unsigned int i=0, size=m_entries.size();i!=size;++i ) {
    auto id = (*(*m_refCollections)[0])[i];
    if (id.index != podio::ObjectID::invalid) {
      CollectionBase* coll = nullptr;
      collectionProvider->get(id.collectionID,coll);
      fcc::TrackClusterCollection* tmp_coll = static_cast<fcc::TrackClusterCollection*>(coll);
      m_entries[i]->m_Cluster = new ConstTrackCluster((*tmp_coll)[id.index]);
    } else {
      m_entries[i]->m_Cluster = nullptr;
    }
  }
  for(unsigned int i=0, size=m_entries.size();i!=size;++i ) {
    auto id = (*(*m_refCollections)[1])[i];
    if (id.index != podio::ObjectID::invalid) {
      CollectionBase* coll = nullptr;
      collectionProvider->get(id.collectionID,coll);
      fcc::TrackHitCollection* tmp_coll = static_cast<fcc::TrackHitCollection*>(coll);
      m_entries[i]->m_Hit = new ConstTrackHit((*tmp_coll)[id.index]);
    } else {
      m_entries[i]->m_Hit = nullptr;
    }
  }

  return true; //TODO: check success
}

void TrackClusterHitsAssociationCollection::push_back(ConstTrackClusterHitsAssociation object){
    int size = m_entries.size();
    auto obj = object.m_obj;
    if (obj->id.index == podio::ObjectID::untracked) {
        obj->id = {size,m_collectionID};
        m_entries.push_back(obj);
        
    } else {
      throw std::invalid_argument( "Object already in a collection. Cannot add it to a second collection " );

    }
}

void TrackClusterHitsAssociationCollection::setBuffer(void* address){
  m_data = static_cast<TrackClusterHitsAssociationDataContainer*>(address);
}


const TrackClusterHitsAssociation TrackClusterHitsAssociationCollectionIterator::operator* () const {
  m_object.m_obj = (*m_collection)[m_index];
  return m_object;
}

const TrackClusterHitsAssociation* TrackClusterHitsAssociationCollectionIterator::operator-> () const {
    m_object.m_obj = (*m_collection)[m_index];
    return &m_object;
}

const TrackClusterHitsAssociationCollectionIterator& TrackClusterHitsAssociationCollectionIterator::operator++() const {
  ++m_index;
 return *this;
}

} // namespace fcc
