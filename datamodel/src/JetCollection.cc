// standard includes
#include <stdexcept>
#include "ParticleCollection.h" 


#include "JetCollection.h"

namespace fcc {

JetCollection::JetCollection() : m_isValid(false), m_collectionID(0), m_entries() , m_rel_particles(new std::vector<fcc::ConstParticle>()),m_data(new JetDataContainer() ) {
    m_refCollections.push_back(new std::vector<podio::ObjectID>());

}

JetCollection::~JetCollection() {
  clear();
  if (m_data != nullptr) delete m_data;
    for (auto& pointer : m_refCollections) { if (pointer != nullptr) delete pointer; }
  if (m_rel_particles != nullptr) { delete m_rel_particles; }

}

const Jet JetCollection::operator[](unsigned int index) const {
  return Jet(m_entries[index]);
}

const Jet JetCollection::at(unsigned int index) const {
  return Jet(m_entries.at(index));
}

int  JetCollection::size() const {
  return m_entries.size();
}

Jet JetCollection::create(){
  auto obj = new JetObj();
  m_entries.emplace_back(obj);
  m_rel_particles_tmp.push_back(obj->m_particles);

  obj->id = {int(m_entries.size()-1),m_collectionID};
  return Jet(obj);
}

void JetCollection::clear(){
  m_data->clear();
  for (auto& pointer : m_refCollections) { pointer->clear(); }
  // clear relations to particles. Make sure to unlink() the reference data s they may be gone already.
  for (auto& pointer : m_rel_particles_tmp) {
    for(auto& item : (*pointer)) {
      item.unlink();
    };
    delete pointer;
  }
  m_rel_particles_tmp.clear();
  for (auto& item : (*m_rel_particles)) { item.unlink(); }
  m_rel_particles->clear();

  for (auto& obj : m_entries) { delete obj; }
  m_entries.clear();
}

void JetCollection::prepareForWrite(){
  auto size = m_entries.size();
  m_data->reserve(size);
  for (auto& obj : m_entries) {m_data->push_back(obj->data); }
  for (auto& pointer : m_refCollections) {pointer->clear(); } 
  int particles_index =0;

  for(int i=0, size = m_data->size(); i != size; ++i){
   (*m_data)[i].particles_begin=particles_index;
   (*m_data)[i].particles_end+=particles_index;
   particles_index = (*m_data)[i].particles_end;
   for(auto it : (*m_rel_particles_tmp[i])) {
     if (it.getObjectID().index == podio::ObjectID::untracked)
       throw std::runtime_error("Trying to persistify untracked object");
     m_refCollections[0]->emplace_back(it.getObjectID());
     m_rel_particles->push_back(it);
   }

  }

}

void JetCollection::prepareAfterRead(){
  int index = 0;
  for (auto& data : *m_data){
    auto obj = new JetObj({index,m_collectionID}, data);
        obj->m_particles = m_rel_particles;
    m_entries.emplace_back(obj);
    ++index;
  }
  m_isValid = true;  
}

bool JetCollection::setReferences(const podio::ICollectionProvider* collectionProvider){
  for(unsigned int i=0, size=m_refCollections[0]->size();i!=size;++i) {
    auto id = (*m_refCollections[0])[i];
    CollectionBase* coll = nullptr;
    collectionProvider->get(id.collectionID,coll);
    fcc::ParticleCollection* tmp_coll = static_cast<fcc::ParticleCollection*>(coll);
    auto tmp = (*tmp_coll)[id.index];
    m_rel_particles->emplace_back(tmp);
  }


  return true; //TODO: check success
}

void JetCollection::push_back(ConstJet object){
  int size = m_entries.size();
  auto obj = object.m_obj;
  if (obj->id.index == podio::ObjectID::untracked) {
      obj->id = {size,m_collectionID};
      m_entries.push_back(obj);
        m_rel_particles_tmp.push_back(obj->m_particles);

  } else {
    throw std::invalid_argument( "Object already in a collection. Cannot add it to a second collection " );
  }
}

void JetCollection::setBuffer(void* address){
  if (m_data != nullptr) delete m_data;
  m_data = static_cast<JetDataContainer*>(address);
}


const Jet JetCollectionIterator::operator* () const {
  m_object.m_obj = (*m_collection)[m_index];
  return m_object;
}

const Jet* JetCollectionIterator::operator-> () const {
  m_object.m_obj = (*m_collection)[m_index];
  return &m_object;
}

const JetCollectionIterator& JetCollectionIterator::operator++() const {
  ++m_index;
  return *this;
}

} // namespace fcc
