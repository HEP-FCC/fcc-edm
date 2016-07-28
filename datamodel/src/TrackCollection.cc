// standard includes
#include <stdexcept>
#include "TrackClusterCollection.h" 
#include "TrackStateCollection.h" 


#include "TrackCollection.h"

namespace fcc {

TrackCollection::TrackCollection() : m_isValid(false), m_collectionID(0), m_entries() , m_rel_clusters(new std::vector<fcc::ConstTrackCluster>()), m_rel_states(new std::vector<fcc::ConstTrackState>()),m_data(new TrackDataContainer() ) {
    m_refCollections.push_back(new std::vector<podio::ObjectID>());
  m_refCollections.push_back(new std::vector<podio::ObjectID>());

}

TrackCollection::~TrackCollection() {
  clear();
  if (m_data != nullptr) delete m_data;
    for (auto& pointer : m_refCollections) { if (pointer != nullptr) delete pointer; }
  if (m_rel_clusters != nullptr) { delete m_rel_clusters; }
  if (m_rel_states != nullptr) { delete m_rel_states; }

}

const Track TrackCollection::operator[](unsigned int index) const {
  return Track(m_entries[index]);
}

const Track TrackCollection::at(unsigned int index) const {
  return Track(m_entries.at(index));
}

int  TrackCollection::size() const {
  return m_entries.size();
}

Track TrackCollection::create(){
  auto obj = new TrackObj();
  m_entries.emplace_back(obj);
  m_rel_clusters_tmp.push_back(obj->m_clusters);
  m_rel_states_tmp.push_back(obj->m_states);

  obj->id = {int(m_entries.size()-1),m_collectionID};
  return Track(obj);
}

void TrackCollection::clear(){
  m_data->clear();
  for (auto& pointer : m_refCollections) { pointer->clear(); }
  // clear relations to clusters. Make sure to unlink() the reference data s they may be gone already.
  for (auto& pointer : m_rel_clusters_tmp) {
    for(auto& item : (*pointer)) {
      item.unlink();
    };
    delete pointer;
  }
  m_rel_clusters_tmp.clear();
  for (auto& item : (*m_rel_clusters)) { item.unlink(); }
  m_rel_clusters->clear();
  // clear relations to states. Make sure to unlink() the reference data s they may be gone already.
  for (auto& pointer : m_rel_states_tmp) {
    for(auto& item : (*pointer)) {
      item.unlink();
    };
    delete pointer;
  }
  m_rel_states_tmp.clear();
  for (auto& item : (*m_rel_states)) { item.unlink(); }
  m_rel_states->clear();

  for (auto& obj : m_entries) { delete obj; }
  m_entries.clear();
}

void TrackCollection::prepareForWrite(){
  auto size = m_entries.size();
  m_data->reserve(size);
  for (auto& obj : m_entries) {m_data->push_back(obj->data); }
  for (auto& pointer : m_refCollections) {pointer->clear(); } 
  int clusters_index =0;
  int states_index =0;

  for(int i=0, size = m_data->size(); i != size; ++i){
   (*m_data)[i].clusters_begin=clusters_index;
   (*m_data)[i].clusters_end+=clusters_index;
   clusters_index = (*m_data)[i].clusters_end;
   for(auto it : (*m_rel_clusters_tmp[i])) {
     if (it.getObjectID().index == podio::ObjectID::untracked)
       throw std::runtime_error("Trying to persistify untracked object");
     m_refCollections[0]->emplace_back(it.getObjectID());
     m_rel_clusters->push_back(it);
   }
   (*m_data)[i].states_begin=states_index;
   (*m_data)[i].states_end+=states_index;
   states_index = (*m_data)[i].states_end;
   for(auto it : (*m_rel_states_tmp[i])) {
     if (it.getObjectID().index == podio::ObjectID::untracked)
       throw std::runtime_error("Trying to persistify untracked object");
     m_refCollections[1]->emplace_back(it.getObjectID());
     m_rel_states->push_back(it);
   }

  }

}

void TrackCollection::prepareAfterRead(){
  int index = 0;
  for (auto& data : *m_data){
    auto obj = new TrackObj({index,m_collectionID}, data);
        obj->m_clusters = m_rel_clusters;   obj->m_states = m_rel_states;
    m_entries.emplace_back(obj);
    ++index;
  }
  m_isValid = true;  
}

bool TrackCollection::setReferences(const podio::ICollectionProvider* collectionProvider){
  for(unsigned int i=0, size=m_refCollections[0]->size();i!=size;++i) {
    auto id = (*m_refCollections[0])[i];
    CollectionBase* coll = nullptr;
    collectionProvider->get(id.collectionID,coll);
    fcc::TrackClusterCollection* tmp_coll = static_cast<fcc::TrackClusterCollection*>(coll);
    auto tmp = (*tmp_coll)[id.index];
    m_rel_clusters->emplace_back(tmp);
  }
  for(unsigned int i=0, size=m_refCollections[1]->size();i!=size;++i) {
    auto id = (*m_refCollections[1])[i];
    CollectionBase* coll = nullptr;
    collectionProvider->get(id.collectionID,coll);
    fcc::TrackStateCollection* tmp_coll = static_cast<fcc::TrackStateCollection*>(coll);
    auto tmp = (*tmp_coll)[id.index];
    m_rel_states->emplace_back(tmp);
  }


  return true; //TODO: check success
}

void TrackCollection::push_back(ConstTrack object){
  int size = m_entries.size();
  auto obj = object.m_obj;
  if (obj->id.index == podio::ObjectID::untracked) {
      obj->id = {size,m_collectionID};
      m_entries.push_back(obj);
        m_rel_clusters_tmp.push_back(obj->m_clusters);
  m_rel_states_tmp.push_back(obj->m_states);

  } else {
    throw std::invalid_argument( "Object already in a collection. Cannot add it to a second collection " );
  }
}

void TrackCollection::setBuffer(void* address){
  if (m_data != nullptr) delete m_data;
  m_data = static_cast<TrackDataContainer*>(address);
}


const Track TrackCollectionIterator::operator* () const {
  m_object.m_obj = (*m_collection)[m_index];
  return m_object;
}

const Track* TrackCollectionIterator::operator-> () const {
  m_object.m_obj = (*m_collection)[m_index];
  return &m_object;
}

const TrackCollectionIterator& TrackCollectionIterator::operator++() const {
  ++m_index;
  return *this;
}

} // namespace fcc
