// standard includes
#include <stdexcept>
#include "TrackCollection.h"


#include "WeightedTrackCollection.h"

namespace fcc {

WeightedTrackCollection::WeightedTrackCollection() : m_isValid(false), m_collectionID(0), m_entries() , m_rel_track(new std::vector<fcc::ConstTrack>()),m_data(new WeightedTrackDataContainer() ) {
    m_refCollections.push_back(new std::vector<podio::ObjectID>());

}

WeightedTrackCollection::~WeightedTrackCollection() {
  clear();
  if (m_data != nullptr) delete m_data;
    for (auto& pointer : m_refCollections) { if (pointer != nullptr) delete pointer; }
  if (m_rel_track != nullptr) { delete m_rel_track; }

}

const WeightedTrack WeightedTrackCollection::operator[](unsigned int index) const {
  return WeightedTrack(m_entries[index]);
}

const WeightedTrack WeightedTrackCollection::at(unsigned int index) const {
  return WeightedTrack(m_entries.at(index));
}

int  WeightedTrackCollection::size() const {
  return m_entries.size();
}

WeightedTrack WeightedTrackCollection::create(){
  auto obj = new WeightedTrackObj();
  m_entries.emplace_back(obj);

  obj->id = {int(m_entries.size()-1),m_collectionID};
  return WeightedTrack(obj);
}

void WeightedTrackCollection::clear(){
  m_data->clear();
  for (auto& pointer : m_refCollections) { pointer->clear(); }
  for (auto& item : (*m_rel_track)) { item.unlink(); }
  m_rel_track->clear();

  for (auto& obj : m_entries) { delete obj; }
  m_entries.clear();
}

void WeightedTrackCollection::prepareForWrite(){
  auto size = m_entries.size();
  m_data->reserve(size);
  for (auto& obj : m_entries) {m_data->push_back(obj->data); }
  for (auto& pointer : m_refCollections) {pointer->clear(); } 

  for(int i=0, size = m_data->size(); i != size; ++i){

  }
  for (auto& obj : m_entries) {
    if (obj->m_track != nullptr) {
      m_refCollections[0]->emplace_back(obj->m_track->getObjectID());
    } else {
      m_refCollections[0]->push_back({-2,-2});
    }
  }

}

void WeightedTrackCollection::prepareAfterRead(){
  int index = 0;
  for (auto& data : *m_data){
    auto obj = new WeightedTrackObj({index,m_collectionID}, data);
    
    m_entries.emplace_back(obj);
    ++index;
  }
  m_isValid = true;  
}

bool WeightedTrackCollection::setReferences(const podio::ICollectionProvider* collectionProvider){

  for(unsigned int i = 0, size = m_entries.size(); i != size; ++i) {
    auto id = (*m_refCollections[0])[i];
    if (id.index != podio::ObjectID::invalid) {
      CollectionBase* coll = nullptr;
      collectionProvider->get(id.collectionID,coll);
      fcc::TrackCollection* tmp_coll = static_cast<fcc::TrackCollection*>(coll);
      m_entries[i]->m_track = new ConstTrack((*tmp_coll)[id.index]);
    } else {
      m_entries[i]->m_track = nullptr;
    }
  }

  return true; //TODO: check success
}

void WeightedTrackCollection::push_back(ConstWeightedTrack object){
  int size = m_entries.size();
  auto obj = object.m_obj;
  if (obj->id.index == podio::ObjectID::untracked) {
      obj->id = {size,m_collectionID};
      m_entries.push_back(obj);
      
  } else {
    throw std::invalid_argument( "Object already in a collection. Cannot add it to a second collection " );
  }
}

void WeightedTrackCollection::setBuffer(void* address){
  if (m_data != nullptr) delete m_data;
  m_data = static_cast<WeightedTrackDataContainer*>(address);
}


const WeightedTrack WeightedTrackCollectionIterator::operator* () const {
  m_object.m_obj = (*m_collection)[m_index];
  return m_object;
}

const WeightedTrack* WeightedTrackCollectionIterator::operator-> () const {
  m_object.m_obj = (*m_collection)[m_index];
  return &m_object;
}

const WeightedTrackCollectionIterator& WeightedTrackCollectionIterator::operator++() const {
  ++m_index;
  return *this;
}

} // namespace fcc
