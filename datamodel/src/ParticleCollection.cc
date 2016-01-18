// standard includes
#include <stdexcept>


#include "ParticleCollection.h"



ParticleCollection::ParticleCollection() : m_collectionID(0), m_entries() ,m_refCollections(nullptr), m_data(new ParticleDataContainer() ) {
  
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

  obj->id = {int(m_entries.size()-1),m_collectionID};
  return Particle(obj);
}

void ParticleCollection::clear(){
  m_data->clear();

  for (auto& obj : m_entries) { delete obj; }
  m_entries.clear();
}

void ParticleCollection::prepareForWrite(){
  int index = 0;
  auto size = m_entries.size();
  m_data->reserve(size);
  for (auto& obj : m_entries) {m_data->push_back(obj->data); }
  if (m_refCollections != nullptr) {
    for (auto& pointer : (*m_refCollections)) {pointer->clear(); }
  }
  
  for(int i=0, size = m_data->size(); i != size; ++i){
  
  }
  
}

void ParticleCollection::prepareAfterRead(){
  int index = 0;
  for (auto& data : *m_data){
    auto obj = new ParticleObj({index,m_collectionID}, data);
    
    m_entries.emplace_back(obj);
    ++index;
  }
}

bool ParticleCollection::setReferences(const podio::ICollectionProvider* collectionProvider){


  return true; //TODO: check success
}

void ParticleCollection::push_back(ConstParticle object){
    int size = m_entries.size();
    auto obj = object.m_obj;
    if (obj->id.index == podio::ObjectID::untracked) {
        obj->id = {size,m_collectionID};
        m_entries.push_back(obj);
        
    } else {
      throw std::invalid_argument( "Object already in a collection. Cannot add it to a second collection " );

    }
}

void ParticleCollection::setBuffer(void* address){
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


