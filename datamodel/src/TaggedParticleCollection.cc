// standard includes
#include <stdexcept>
#include "ParticleCollection.h"


#include "TaggedParticleCollection.h"

namespace fcc {

TaggedParticleCollection::TaggedParticleCollection() : m_isValid(false), m_collectionID(0), m_entries() , m_rel_particle(new std::vector<fcc::ConstParticle>()),m_data(new TaggedParticleDataContainer() ) {
    m_refCollections.push_back(new std::vector<podio::ObjectID>());

}

TaggedParticleCollection::~TaggedParticleCollection() {
  clear();
  if (m_data != nullptr) delete m_data;
    for (auto& pointer : m_refCollections) { if (pointer != nullptr) delete pointer; }
  if (m_rel_particle != nullptr) { delete m_rel_particle; }

}

const TaggedParticle TaggedParticleCollection::operator[](unsigned int index) const {
  return TaggedParticle(m_entries[index]);
}

const TaggedParticle TaggedParticleCollection::at(unsigned int index) const {
  return TaggedParticle(m_entries.at(index));
}

int  TaggedParticleCollection::size() const {
  return m_entries.size();
}

TaggedParticle TaggedParticleCollection::create(){
  auto obj = new TaggedParticleObj();
  m_entries.emplace_back(obj);

  obj->id = {int(m_entries.size()-1),m_collectionID};
  return TaggedParticle(obj);
}

void TaggedParticleCollection::clear(){
  m_data->clear();
  for (auto& pointer : m_refCollections) { pointer->clear(); }
  for (auto& item : (*m_rel_particle)) { item.unlink(); }
  m_rel_particle->clear();

  for (auto& obj : m_entries) { delete obj; }
  m_entries.clear();
}

void TaggedParticleCollection::prepareForWrite(){
  auto size = m_entries.size();
  m_data->reserve(size);
  for (auto& obj : m_entries) {m_data->push_back(obj->data); }
  for (auto& pointer : m_refCollections) {pointer->clear(); } 

  for(int i=0, size = m_data->size(); i != size; ++i){

  }
  for (auto& obj : m_entries) {
    if (obj->m_particle != nullptr) {
      m_refCollections[0]->emplace_back(obj->m_particle->getObjectID());
    } else {
      m_refCollections[0]->push_back({-2,-2});
    }
  }

}

void TaggedParticleCollection::prepareAfterRead(){
  int index = 0;
  for (auto& data : *m_data){
    auto obj = new TaggedParticleObj({index,m_collectionID}, data);
    
    m_entries.emplace_back(obj);
    ++index;
  }
  m_isValid = true;  
}

bool TaggedParticleCollection::setReferences(const podio::ICollectionProvider* collectionProvider){

  for(unsigned int i = 0, size = m_entries.size(); i != size; ++i) {
    auto id = (*m_refCollections[0])[i];
    if (id.index != podio::ObjectID::invalid) {
      CollectionBase* coll = nullptr;
      collectionProvider->get(id.collectionID,coll);
      fcc::ParticleCollection* tmp_coll = static_cast<fcc::ParticleCollection*>(coll);
      m_entries[i]->m_particle = new ConstParticle((*tmp_coll)[id.index]);
    } else {
      m_entries[i]->m_particle = nullptr;
    }
  }

  return true; //TODO: check success
}

void TaggedParticleCollection::push_back(ConstTaggedParticle object){
  int size = m_entries.size();
  auto obj = object.m_obj;
  if (obj->id.index == podio::ObjectID::untracked) {
      obj->id = {size,m_collectionID};
      m_entries.push_back(obj);
      
  } else {
    throw std::invalid_argument( "Object already in a collection. Cannot add it to a second collection " );
  }
}

void TaggedParticleCollection::setBuffer(void* address){
  if (m_data != nullptr) delete m_data;
  m_data = static_cast<TaggedParticleDataContainer*>(address);
}


const TaggedParticle TaggedParticleCollectionIterator::operator* () const {
  m_object.m_obj = (*m_collection)[m_index];
  return m_object;
}

const TaggedParticle* TaggedParticleCollectionIterator::operator-> () const {
  m_object.m_obj = (*m_collection)[m_index];
  return &m_object;
}

const TaggedParticleCollectionIterator& TaggedParticleCollectionIterator::operator++() const {
  ++m_index;
  return *this;
}

} // namespace fcc
