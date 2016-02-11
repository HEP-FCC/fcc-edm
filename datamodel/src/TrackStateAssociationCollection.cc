// standard includes
#include <stdexcept>
#include "TrackCollection.h" 
#include "TrackStateCollection.h" 


#include "TrackStateAssociationCollection.h"

namespace fcc {

TrackStateAssociationCollection::TrackStateAssociationCollection() : m_collectionID(0), m_entries() ,m_rel_Track(new std::vector<::fcc::ConstTrack>()),m_rel_State(new std::vector<::fcc::ConstTrackState>()),m_refCollections(nullptr), m_data(new TrackStateAssociationDataContainer() ) {
    m_refCollections = new podio::CollRefCollection();
  m_refCollections->push_back(new std::vector<podio::ObjectID>());
  m_refCollections->push_back(new std::vector<podio::ObjectID>());

}

const TrackStateAssociation TrackStateAssociationCollection::operator[](unsigned int index) const {
  return TrackStateAssociation(m_entries[index]);
}

const TrackStateAssociation TrackStateAssociationCollection::at(unsigned int index) const {
  return TrackStateAssociation(m_entries.at(index));
}

int  TrackStateAssociationCollection::size() const {
  return m_entries.size();
}

TrackStateAssociation TrackStateAssociationCollection::create(){
  auto obj = new TrackStateAssociationObj();
  m_entries.emplace_back(obj);

  obj->id = {int(m_entries.size()-1),m_collectionID};
  return TrackStateAssociation(obj);
}

void TrackStateAssociationCollection::clear(){
  m_data->clear();
  for (auto& pointer : (*m_refCollections)) {pointer->clear(); }
  for (auto& item : (*m_rel_Track)) {item.unlink(); }
  m_rel_Track->clear();
  for (auto& item : (*m_rel_State)) {item.unlink(); }
  m_rel_State->clear();

  for (auto& obj : m_entries) { delete obj; }
  m_entries.clear();
}

void TrackStateAssociationCollection::prepareForWrite(){
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
if (obj->m_State != nullptr){
(*m_refCollections)[1]->emplace_back(obj->m_State->getObjectID());} else {(*m_refCollections)[1]->push_back({-2,-2}); } }

}

void TrackStateAssociationCollection::prepareAfterRead(){
  int index = 0;
  for (auto& data : *m_data){
    auto obj = new TrackStateAssociationObj({index,m_collectionID}, data);
    
    m_entries.emplace_back(obj);
    ++index;
  }
}

bool TrackStateAssociationCollection::setReferences(const podio::ICollectionProvider* collectionProvider){

  for(unsigned int i=0, size=m_entries.size();i!=size;++i ) {
    auto id = (*(*m_refCollections)[0])[i];
    if (id.index != podio::ObjectID::invalid) {
      CollectionBase* coll = nullptr;
      collectionProvider->get(id.collectionID,coll);
      fcc::TrackCollection* tmp_coll = static_cast<fcc::TrackCollection*>(coll);
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
      fcc::TrackStateCollection* tmp_coll = static_cast<fcc::TrackStateCollection*>(coll);
      m_entries[i]->m_State = new ConstTrackState((*tmp_coll)[id.index]);
    } else {
      m_entries[i]->m_State = nullptr;
    }
  }

  return true; //TODO: check success
}

void TrackStateAssociationCollection::push_back(ConstTrackStateAssociation object){
    int size = m_entries.size();
    auto obj = object.m_obj;
    if (obj->id.index == podio::ObjectID::untracked) {
        obj->id = {size,m_collectionID};
        m_entries.push_back(obj);
        
    } else {
      throw std::invalid_argument( "Object already in a collection. Cannot add it to a second collection " );

    }
}

void TrackStateAssociationCollection::setBuffer(void* address){
  m_data = static_cast<TrackStateAssociationDataContainer*>(address);
}


const TrackStateAssociation TrackStateAssociationCollectionIterator::operator* () const {
  m_object.m_obj = (*m_collection)[m_index];
  return m_object;
}

const TrackStateAssociation* TrackStateAssociationCollectionIterator::operator-> () const {
    m_object.m_obj = (*m_collection)[m_index];
    return &m_object;
}

const TrackStateAssociationCollectionIterator& TrackStateAssociationCollectionIterator::operator++() const {
  ++m_index;
 return *this;
}

} // namespace fcc
