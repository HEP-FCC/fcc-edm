// standard includes
#include <stdexcept>
#include "TrackCollection.h" 
#include "TrackClusterCollection.h" 


#include "TrackClusterAssociationCollection.h"



TrackClusterAssociationCollection::TrackClusterAssociationCollection() : m_collectionID(0), m_entries() ,m_rel_Track(new std::vector<ConstTrack>()),m_rel_Cluster(new std::vector<ConstTrackCluster>()),m_refCollections(nullptr), m_data(new TrackClusterAssociationDataContainer() ) {
    m_refCollections = new podio::CollRefCollection();
  m_refCollections->push_back(new std::vector<podio::ObjectID>());
  m_refCollections->push_back(new std::vector<podio::ObjectID>());

}

const TrackClusterAssociation TrackClusterAssociationCollection::operator[](unsigned int index) const {
  return TrackClusterAssociation(m_entries[index]);
}

const TrackClusterAssociation TrackClusterAssociationCollection::at(unsigned int index) const {
  return TrackClusterAssociation(m_entries.at(index));
}

int  TrackClusterAssociationCollection::size() const {
  return m_entries.size();
}

TrackClusterAssociation TrackClusterAssociationCollection::create(){
  auto obj = new TrackClusterAssociationObj();
  m_entries.emplace_back(obj);

  obj->id = {int(m_entries.size()-1),m_collectionID};
  return TrackClusterAssociation(obj);
}

void TrackClusterAssociationCollection::clear(){
  m_data->clear();
  for (auto& pointer : (*m_refCollections)) {pointer->clear(); }
  for (auto& item : (*m_rel_Track)) {item.unlink(); }
  m_rel_Track->clear();
  for (auto& item : (*m_rel_Cluster)) {item.unlink(); }
  m_rel_Cluster->clear();

  for (auto& obj : m_entries) { delete obj; }
  m_entries.clear();
}

void TrackClusterAssociationCollection::prepareForWrite(){
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
if (obj->m_Track != nullptr){
(*m_refCollections)[0]->emplace_back(obj->m_Track->getObjectID());} else {(*m_refCollections)[0]->push_back({-2,-2}); } }
  for (auto& obj : m_entries) {
if (obj->m_Cluster != nullptr){
(*m_refCollections)[1]->emplace_back(obj->m_Cluster->getObjectID());} else {(*m_refCollections)[1]->push_back({-2,-2}); } }

}

void TrackClusterAssociationCollection::prepareAfterRead(){
  int index = 0;
  for (auto& data : *m_data){
    auto obj = new TrackClusterAssociationObj({index,m_collectionID}, data);
    
    m_entries.emplace_back(obj);
    ++index;
  }
}

bool TrackClusterAssociationCollection::setReferences(const podio::ICollectionProvider* collectionProvider){

  for(unsigned int i=0, size=m_entries.size();i!=size;++i ) {
    auto id = (*(*m_refCollections)[0])[i];
    if (id.index != podio::ObjectID::invalid) {
      CollectionBase* coll = nullptr;
      collectionProvider->get(id.collectionID,coll);
      TrackCollection* tmp_coll = static_cast<TrackCollection*>(coll);
      m_entries[i]->m_Track = new ConstTrack((*tmp_coll)[id.index]);
    } else {
      m_entries[i]->m_Track = nullptr;
    }
  }
  for(unsigned int i=0, size=m_entries.size();i!=size;++i ) {
    auto id = (*(*m_refCollections)[1])[i];
    if (id.index != podio::ObjectID::invalid) {
      CollectionBase* coll = nullptr;
      collectionProvider->get(id.collectionID,coll);
      TrackClusterCollection* tmp_coll = static_cast<TrackClusterCollection*>(coll);
      m_entries[i]->m_Cluster = new ConstTrackCluster((*tmp_coll)[id.index]);
    } else {
      m_entries[i]->m_Cluster = nullptr;
    }
  }

  return true; //TODO: check success
}

void TrackClusterAssociationCollection::push_back(ConstTrackClusterAssociation object){
    int size = m_entries.size();
    auto obj = object.m_obj;
    if (obj->id.index == podio::ObjectID::untracked) {
        obj->id = {size,m_collectionID};
        m_entries.push_back(obj);
        
    } else {
      throw std::invalid_argument( "Object already in a collection. Cannot add it to a second collection " );

    }
}

void TrackClusterAssociationCollection::setBuffer(void* address){
  m_data = static_cast<TrackClusterAssociationDataContainer*>(address);
}


const TrackClusterAssociation TrackClusterAssociationCollectionIterator::operator* () const {
  m_object.m_obj = (*m_collection)[m_index];
  return m_object;
}

const TrackClusterAssociation* TrackClusterAssociationCollectionIterator::operator-> () const {
    m_object.m_obj = (*m_collection)[m_index];
    return &m_object;
}

const TrackClusterAssociationCollectionIterator& TrackClusterAssociationCollectionIterator::operator++() const {
  ++m_index;
 return *this;
}


