// standard includes
#include <stdexcept>
#include "ParticleCollection.h" 
#include "TrackCollection.h" 


#include "ParticleTrackAssociationCollection.h"

namespace fcc {

ParticleTrackAssociationCollection::ParticleTrackAssociationCollection() : m_collectionID(0), m_entries() ,m_rel_Particle(new std::vector<::fcc::ConstParticle>()),m_rel_Track(new std::vector<::fcc::ConstTrack>()),m_refCollections(nullptr), m_data(new ParticleTrackAssociationDataContainer() ) {
    m_refCollections = new podio::CollRefCollection();
  m_refCollections->push_back(new std::vector<podio::ObjectID>());
  m_refCollections->push_back(new std::vector<podio::ObjectID>());

}

const ParticleTrackAssociation ParticleTrackAssociationCollection::operator[](unsigned int index) const {
  return ParticleTrackAssociation(m_entries[index]);
}

const ParticleTrackAssociation ParticleTrackAssociationCollection::at(unsigned int index) const {
  return ParticleTrackAssociation(m_entries.at(index));
}

int  ParticleTrackAssociationCollection::size() const {
  return m_entries.size();
}

ParticleTrackAssociation ParticleTrackAssociationCollection::create(){
  auto obj = new ParticleTrackAssociationObj();
  m_entries.emplace_back(obj);

  obj->id = {int(m_entries.size()-1),m_collectionID};
  return ParticleTrackAssociation(obj);
}

void ParticleTrackAssociationCollection::clear(){
  m_data->clear();
  for (auto& pointer : (*m_refCollections)) {pointer->clear(); }
  for (auto& item : (*m_rel_Particle)) {item.unlink(); }
  m_rel_Particle->clear();
  for (auto& item : (*m_rel_Track)) {item.unlink(); }
  m_rel_Track->clear();

  for (auto& obj : m_entries) { delete obj; }
  m_entries.clear();
}

void ParticleTrackAssociationCollection::prepareForWrite(){
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
if (obj->m_Particle != nullptr){
(*m_refCollections)[0]->emplace_back(obj->m_Particle->getObjectID());} else {(*m_refCollections)[0]->push_back({-2,-2}); } }
  for (auto& obj : m_entries) {
if (obj->m_Track != nullptr){
(*m_refCollections)[1]->emplace_back(obj->m_Track->getObjectID());} else {(*m_refCollections)[1]->push_back({-2,-2}); } }

}

void ParticleTrackAssociationCollection::prepareAfterRead(){
  int index = 0;
  for (auto& data : *m_data){
    auto obj = new ParticleTrackAssociationObj({index,m_collectionID}, data);
    
    m_entries.emplace_back(obj);
    ++index;
  }
}

bool ParticleTrackAssociationCollection::setReferences(const podio::ICollectionProvider* collectionProvider){

  for(unsigned int i=0, size=m_entries.size();i!=size;++i ) {
    auto id = (*(*m_refCollections)[0])[i];
    if (id.index != podio::ObjectID::invalid) {
      CollectionBase* coll = nullptr;
      collectionProvider->get(id.collectionID,coll);
      fcc::ParticleCollection* tmp_coll = static_cast<fcc::ParticleCollection*>(coll);
      m_entries[i]->m_Particle = new ConstParticle((*tmp_coll)[id.index]);
    } else {
      m_entries[i]->m_Particle = nullptr;
    }
  }
  for(unsigned int i=0, size=m_entries.size();i!=size;++i ) {
    auto id = (*(*m_refCollections)[1])[i];
    if (id.index != podio::ObjectID::invalid) {
      CollectionBase* coll = nullptr;
      collectionProvider->get(id.collectionID,coll);
      fcc::TrackCollection* tmp_coll = static_cast<fcc::TrackCollection*>(coll);
      m_entries[i]->m_Track = new ConstTrack((*tmp_coll)[id.index]);
    } else {
      m_entries[i]->m_Track = nullptr;
    }
  }

  return true; //TODO: check success
}

void ParticleTrackAssociationCollection::push_back(ConstParticleTrackAssociation object){
    int size = m_entries.size();
    auto obj = object.m_obj;
    if (obj->id.index == podio::ObjectID::untracked) {
        obj->id = {size,m_collectionID};
        m_entries.push_back(obj);
        
    } else {
      throw std::invalid_argument( "Object already in a collection. Cannot add it to a second collection " );

    }
}

void ParticleTrackAssociationCollection::setBuffer(void* address){
  m_data = static_cast<ParticleTrackAssociationDataContainer*>(address);
}


const ParticleTrackAssociation ParticleTrackAssociationCollectionIterator::operator* () const {
  m_object.m_obj = (*m_collection)[m_index];
  return m_object;
}

const ParticleTrackAssociation* ParticleTrackAssociationCollectionIterator::operator-> () const {
    m_object.m_obj = (*m_collection)[m_index];
    return &m_object;
}

const ParticleTrackAssociationCollectionIterator& ParticleTrackAssociationCollectionIterator::operator++() const {
  ++m_index;
 return *this;
}

} // namespace fcc
