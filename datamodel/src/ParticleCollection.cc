// standard includes
#include <stdexcept>
#include "TrackCollection.h" 
#include "CaloClusterCollection.h" 


#include "ParticleCollection.h"

namespace fcc {

ParticleCollection::ParticleCollection() : m_isValid(false), m_collectionID(0), m_entries() , m_rel_tracks(new std::vector<fcc::ConstTrack>()), m_rel_clusters(new std::vector<fcc::ConstCaloCluster>()),m_data(new ParticleDataContainer() ) {
    m_refCollections.push_back(new std::vector<podio::ObjectID>());
  m_refCollections.push_back(new std::vector<podio::ObjectID>());

}

ParticleCollection::~ParticleCollection() {
  clear();
  if (m_data != nullptr) delete m_data;
    for (auto& pointer : m_refCollections) { if (pointer != nullptr) delete pointer; }
  if (m_rel_tracks != nullptr) { delete m_rel_tracks; }
  if (m_rel_clusters != nullptr) { delete m_rel_clusters; }

}

const Particle ParticleCollection::operator[](unsigned int index) const {
  return Particle(m_entries[index]);
}

const Particle ParticleCollection::at(unsigned int index) const {
  return Particle(m_entries.at(index));
}

int  ParticleCollection::size() const {
  return m_entries.size();
}

Particle ParticleCollection::create(){
  auto obj = new ParticleObj();
  m_entries.emplace_back(obj);
  m_rel_tracks_tmp.push_back(obj->m_tracks);
  m_rel_clusters_tmp.push_back(obj->m_clusters);

  obj->id = {int(m_entries.size()-1),m_collectionID};
  return Particle(obj);
}

void ParticleCollection::clear(){
  m_data->clear();
  for (auto& pointer : m_refCollections) { pointer->clear(); }
  // clear relations to tracks. Make sure to unlink() the reference data s they may be gone already.
  for (auto& pointer : m_rel_tracks_tmp) {
    for(auto& item : (*pointer)) {
      item.unlink();
    };
    delete pointer;
  }
  m_rel_tracks_tmp.clear();
  for (auto& item : (*m_rel_tracks)) { item.unlink(); }
  m_rel_tracks->clear();
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

  for (auto& obj : m_entries) { delete obj; }
  m_entries.clear();
}

void ParticleCollection::prepareForWrite(){
  auto size = m_entries.size();
  m_data->reserve(size);
  for (auto& obj : m_entries) {m_data->push_back(obj->data); }
  for (auto& pointer : m_refCollections) {pointer->clear(); } 
  int tracks_index =0;
  int clusters_index =0;

  for(int i=0, size = m_data->size(); i != size; ++i){
   (*m_data)[i].tracks_begin=tracks_index;
   (*m_data)[i].tracks_end+=tracks_index;
   tracks_index = (*m_data)[i].tracks_end;
   for(auto it : (*m_rel_tracks_tmp[i])) {
     if (it.getObjectID().index == podio::ObjectID::untracked)
       throw std::runtime_error("Trying to persistify untracked object");
     m_refCollections[0]->emplace_back(it.getObjectID());
     m_rel_tracks->push_back(it);
   }
   (*m_data)[i].clusters_begin=clusters_index;
   (*m_data)[i].clusters_end+=clusters_index;
   clusters_index = (*m_data)[i].clusters_end;
   for(auto it : (*m_rel_clusters_tmp[i])) {
     if (it.getObjectID().index == podio::ObjectID::untracked)
       throw std::runtime_error("Trying to persistify untracked object");
     m_refCollections[1]->emplace_back(it.getObjectID());
     m_rel_clusters->push_back(it);
   }

  }

}

void ParticleCollection::prepareAfterRead(){
  int index = 0;
  for (auto& data : *m_data){
    auto obj = new ParticleObj({index,m_collectionID}, data);
        obj->m_tracks = m_rel_tracks;   obj->m_clusters = m_rel_clusters;
    m_entries.emplace_back(obj);
    ++index;
  }
  m_isValid = true;  
}

bool ParticleCollection::setReferences(const podio::ICollectionProvider* collectionProvider){
  for(unsigned int i=0, size=m_refCollections[0]->size();i!=size;++i) {
    auto id = (*m_refCollections[0])[i];
    CollectionBase* coll = nullptr;
    collectionProvider->get(id.collectionID,coll);
    fcc::TrackCollection* tmp_coll = static_cast<fcc::TrackCollection*>(coll);
    auto tmp = (*tmp_coll)[id.index];
    m_rel_tracks->emplace_back(tmp);
  }
  for(unsigned int i=0, size=m_refCollections[1]->size();i!=size;++i) {
    auto id = (*m_refCollections[1])[i];
    CollectionBase* coll = nullptr;
    collectionProvider->get(id.collectionID,coll);
    fcc::CaloClusterCollection* tmp_coll = static_cast<fcc::CaloClusterCollection*>(coll);
    auto tmp = (*tmp_coll)[id.index];
    m_rel_clusters->emplace_back(tmp);
  }


  return true; //TODO: check success
}

void ParticleCollection::push_back(ConstParticle object){
  int size = m_entries.size();
  auto obj = object.m_obj;
  if (obj->id.index == podio::ObjectID::untracked) {
      obj->id = {size,m_collectionID};
      m_entries.push_back(obj);
        m_rel_tracks_tmp.push_back(obj->m_tracks);
  m_rel_clusters_tmp.push_back(obj->m_clusters);

  } else {
    throw std::invalid_argument( "Object already in a collection. Cannot add it to a second collection " );
  }
}

void ParticleCollection::setBuffer(void* address){
  if (m_data != nullptr) delete m_data;
  m_data = static_cast<ParticleDataContainer*>(address);
}


const Particle ParticleCollectionIterator::operator* () const {
  m_object.m_obj = (*m_collection)[m_index];
  return m_object;
}

const Particle* ParticleCollectionIterator::operator-> () const {
  m_object.m_obj = (*m_collection)[m_index];
  return &m_object;
}

const ParticleCollectionIterator& ParticleCollectionIterator::operator++() const {
  ++m_index;
  return *this;
}

} // namespace fcc
