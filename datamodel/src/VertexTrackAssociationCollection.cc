// standard includes
#include <stdexcept>
#include "TrackCollection.h" 
#include "VertexCollection.h" 


#include "VertexTrackAssociationCollection.h"



VertexTrackAssociationCollection::VertexTrackAssociationCollection() : m_collectionID(0), m_entries() ,m_rel_Track(new std::vector<ConstTrack>()),m_rel_Vertex(new std::vector<ConstVertex>()),m_refCollections(nullptr), m_data(new VertexTrackAssociationDataContainer() ) {
    m_refCollections = new podio::CollRefCollection();
  m_refCollections->push_back(new std::vector<podio::ObjectID>());
  m_refCollections->push_back(new std::vector<podio::ObjectID>());

}

const VertexTrackAssociation VertexTrackAssociationCollection::operator[](unsigned int index) const {
  return VertexTrackAssociation(m_entries[index]);
}

const VertexTrackAssociation VertexTrackAssociationCollection::at(unsigned int index) const {
  return VertexTrackAssociation(m_entries.at(index));
}

int  VertexTrackAssociationCollection::size() const {
  return m_entries.size();
}

VertexTrackAssociation VertexTrackAssociationCollection::create(){
  auto obj = new VertexTrackAssociationObj();
  m_entries.emplace_back(obj);

  obj->id = {int(m_entries.size()-1),m_collectionID};
  return VertexTrackAssociation(obj);
}

void VertexTrackAssociationCollection::clear(){
  m_data->clear();
  for (auto& pointer : (*m_refCollections)) {pointer->clear(); }
  for (auto& item : (*m_rel_Track)) {item.unlink(); }
  m_rel_Track->clear();
  for (auto& item : (*m_rel_Vertex)) {item.unlink(); }
  m_rel_Vertex->clear();

  for (auto& obj : m_entries) { delete obj; }
  m_entries.clear();
}

void VertexTrackAssociationCollection::prepareForWrite(){
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
if (obj->m_Vertex != nullptr){
(*m_refCollections)[1]->emplace_back(obj->m_Vertex->getObjectID());} else {(*m_refCollections)[1]->push_back({-2,-2}); } }

}

void VertexTrackAssociationCollection::prepareAfterRead(){
  int index = 0;
  for (auto& data : *m_data){
    auto obj = new VertexTrackAssociationObj({index,m_collectionID}, data);
    
    m_entries.emplace_back(obj);
    ++index;
  }
}

bool VertexTrackAssociationCollection::setReferences(const podio::ICollectionProvider* collectionProvider){

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
      VertexCollection* tmp_coll = static_cast<VertexCollection*>(coll);
      m_entries[i]->m_Vertex = new ConstVertex((*tmp_coll)[id.index]);
    } else {
      m_entries[i]->m_Vertex = nullptr;
    }
  }

  return true; //TODO: check success
}

void VertexTrackAssociationCollection::push_back(ConstVertexTrackAssociation object){
    int size = m_entries.size();
    auto obj = object.m_obj;
    if (obj->id.index == podio::ObjectID::untracked) {
        obj->id = {size,m_collectionID};
        m_entries.push_back(obj);
        
    } else {
      throw std::invalid_argument( "Object already in a collection. Cannot add it to a second collection " );

    }
}

void VertexTrackAssociationCollection::setBuffer(void* address){
  m_data = static_cast<VertexTrackAssociationDataContainer*>(address);
}


const VertexTrackAssociation VertexTrackAssociationCollectionIterator::operator* () const {
  m_object.m_obj = (*m_collection)[m_index];
  return m_object;
}

const VertexTrackAssociation* VertexTrackAssociationCollectionIterator::operator-> () const {
    m_object.m_obj = (*m_collection)[m_index];
    return &m_object;
}

const VertexTrackAssociationCollectionIterator& VertexTrackAssociationCollectionIterator::operator++() const {
  ++m_index;
 return *this;
}


