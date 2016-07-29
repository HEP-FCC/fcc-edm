// standard includes
#include <stdexcept>
#include "WeightedTrackCollection.h" 


#include "VertexCollection.h"

namespace fcc {

VertexCollection::VertexCollection() : m_isValid(false), m_collectionID(0), m_entries() , m_rel_tracks(new std::vector<fcc::ConstWeightedTrack>()),m_data(new VertexDataContainer() ) {
    m_refCollections.push_back(new std::vector<podio::ObjectID>());

}

VertexCollection::~VertexCollection() {
  clear();
  if (m_data != nullptr) delete m_data;
    for (auto& pointer : m_refCollections) { if (pointer != nullptr) delete pointer; }
  if (m_rel_tracks != nullptr) { delete m_rel_tracks; }

}

const Vertex VertexCollection::operator[](unsigned int index) const {
  return Vertex(m_entries[index]);
}

const Vertex VertexCollection::at(unsigned int index) const {
  return Vertex(m_entries.at(index));
}

int  VertexCollection::size() const {
  return m_entries.size();
}

Vertex VertexCollection::create(){
  auto obj = new VertexObj();
  m_entries.emplace_back(obj);
  m_rel_tracks_tmp.push_back(obj->m_tracks);

  obj->id = {int(m_entries.size()-1),m_collectionID};
  return Vertex(obj);
}

void VertexCollection::clear(){
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

  for (auto& obj : m_entries) { delete obj; }
  m_entries.clear();
}

void VertexCollection::prepareForWrite(){
  auto size = m_entries.size();
  m_data->reserve(size);
  for (auto& obj : m_entries) {m_data->push_back(obj->data); }
  for (auto& pointer : m_refCollections) {pointer->clear(); } 
  int tracks_index =0;

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

  }

}

void VertexCollection::prepareAfterRead(){
  int index = 0;
  for (auto& data : *m_data){
    auto obj = new VertexObj({index,m_collectionID}, data);
        obj->m_tracks = m_rel_tracks;
    m_entries.emplace_back(obj);
    ++index;
  }
  m_isValid = true;  
}

bool VertexCollection::setReferences(const podio::ICollectionProvider* collectionProvider){
  for(unsigned int i=0, size=m_refCollections[0]->size();i!=size;++i) {
    auto id = (*m_refCollections[0])[i];
    CollectionBase* coll = nullptr;
    collectionProvider->get(id.collectionID,coll);
    fcc::WeightedTrackCollection* tmp_coll = static_cast<fcc::WeightedTrackCollection*>(coll);
    auto tmp = (*tmp_coll)[id.index];
    m_rel_tracks->emplace_back(tmp);
  }


  return true; //TODO: check success
}

void VertexCollection::push_back(ConstVertex object){
  int size = m_entries.size();
  auto obj = object.m_obj;
  if (obj->id.index == podio::ObjectID::untracked) {
      obj->id = {size,m_collectionID};
      m_entries.push_back(obj);
        m_rel_tracks_tmp.push_back(obj->m_tracks);

  } else {
    throw std::invalid_argument( "Object already in a collection. Cannot add it to a second collection " );
  }
}

void VertexCollection::setBuffer(void* address){
  if (m_data != nullptr) delete m_data;
  m_data = static_cast<VertexDataContainer*>(address);
}


const Vertex VertexCollectionIterator::operator* () const {
  m_object.m_obj = (*m_collection)[m_index];
  return m_object;
}

const Vertex* VertexCollectionIterator::operator-> () const {
  m_object.m_obj = (*m_collection)[m_index];
  return &m_object;
}

const VertexCollectionIterator& VertexCollectionIterator::operator++() const {
  ++m_index;
  return *this;
}

} // namespace fcc
