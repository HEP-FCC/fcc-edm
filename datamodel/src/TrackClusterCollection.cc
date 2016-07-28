// standard includes
#include <stdexcept>
#include "TrackHitCollection.h" 


#include "TrackClusterCollection.h"

namespace fcc {

TrackClusterCollection::TrackClusterCollection() : m_isValid(false), m_collectionID(0), m_entries() , m_rel_hits(new std::vector<fcc::ConstTrackHit>()),m_data(new TrackClusterDataContainer() ) {
    m_refCollections.push_back(new std::vector<podio::ObjectID>());

}

TrackClusterCollection::~TrackClusterCollection() {
  clear();
  if (m_data != nullptr) delete m_data;
    for (auto& pointer : m_refCollections) { if (pointer != nullptr) delete pointer; }
  if (m_rel_hits != nullptr) { delete m_rel_hits; }

}

const TrackCluster TrackClusterCollection::operator[](unsigned int index) const {
  return TrackCluster(m_entries[index]);
}

const TrackCluster TrackClusterCollection::at(unsigned int index) const {
  return TrackCluster(m_entries.at(index));
}

int  TrackClusterCollection::size() const {
  return m_entries.size();
}

TrackCluster TrackClusterCollection::create(){
  auto obj = new TrackClusterObj();
  m_entries.emplace_back(obj);
  m_rel_hits_tmp.push_back(obj->m_hits);

  obj->id = {int(m_entries.size()-1),m_collectionID};
  return TrackCluster(obj);
}

void TrackClusterCollection::clear(){
  m_data->clear();
  for (auto& pointer : m_refCollections) { pointer->clear(); }
  // clear relations to hits. Make sure to unlink() the reference data s they may be gone already.
  for (auto& pointer : m_rel_hits_tmp) {
    for(auto& item : (*pointer)) {
      item.unlink();
    };
    delete pointer;
  }
  m_rel_hits_tmp.clear();
  for (auto& item : (*m_rel_hits)) { item.unlink(); }
  m_rel_hits->clear();

  for (auto& obj : m_entries) { delete obj; }
  m_entries.clear();
}

void TrackClusterCollection::prepareForWrite(){
  auto size = m_entries.size();
  m_data->reserve(size);
  for (auto& obj : m_entries) {m_data->push_back(obj->data); }
  for (auto& pointer : m_refCollections) {pointer->clear(); } 
  int hits_index =0;

  for(int i=0, size = m_data->size(); i != size; ++i){
   (*m_data)[i].hits_begin=hits_index;
   (*m_data)[i].hits_end+=hits_index;
   hits_index = (*m_data)[i].hits_end;
   for(auto it : (*m_rel_hits_tmp[i])) {
     if (it.getObjectID().index == podio::ObjectID::untracked)
       throw std::runtime_error("Trying to persistify untracked object");
     m_refCollections[0]->emplace_back(it.getObjectID());
     m_rel_hits->push_back(it);
   }

  }

}

void TrackClusterCollection::prepareAfterRead(){
  int index = 0;
  for (auto& data : *m_data){
    auto obj = new TrackClusterObj({index,m_collectionID}, data);
        obj->m_hits = m_rel_hits;
    m_entries.emplace_back(obj);
    ++index;
  }
  m_isValid = true;  
}

bool TrackClusterCollection::setReferences(const podio::ICollectionProvider* collectionProvider){
  for(unsigned int i=0, size=m_refCollections[0]->size();i!=size;++i) {
    auto id = (*m_refCollections[0])[i];
    CollectionBase* coll = nullptr;
    collectionProvider->get(id.collectionID,coll);
    fcc::TrackHitCollection* tmp_coll = static_cast<fcc::TrackHitCollection*>(coll);
    auto tmp = (*tmp_coll)[id.index];
    m_rel_hits->emplace_back(tmp);
  }


  return true; //TODO: check success
}

void TrackClusterCollection::push_back(ConstTrackCluster object){
  int size = m_entries.size();
  auto obj = object.m_obj;
  if (obj->id.index == podio::ObjectID::untracked) {
      obj->id = {size,m_collectionID};
      m_entries.push_back(obj);
        m_rel_hits_tmp.push_back(obj->m_hits);

  } else {
    throw std::invalid_argument( "Object already in a collection. Cannot add it to a second collection " );
  }
}

void TrackClusterCollection::setBuffer(void* address){
  if (m_data != nullptr) delete m_data;
  m_data = static_cast<TrackClusterDataContainer*>(address);
}


const TrackCluster TrackClusterCollectionIterator::operator* () const {
  m_object.m_obj = (*m_collection)[m_index];
  return m_object;
}

const TrackCluster* TrackClusterCollectionIterator::operator-> () const {
  m_object.m_obj = (*m_collection)[m_index];
  return &m_object;
}

const TrackClusterCollectionIterator& TrackClusterCollectionIterator::operator++() const {
  ++m_index;
  return *this;
}

} // namespace fcc
