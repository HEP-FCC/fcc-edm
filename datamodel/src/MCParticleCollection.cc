// standard includes
#include <stdexcept>
#include "GenVertexCollection.h"
#include "GenVertexCollection.h"


#include "MCParticleCollection.h"

namespace fcc {

MCParticleCollection::MCParticleCollection() : m_isValid(false), m_collectionID(0), m_entries() , m_rel_StartVertex(new std::vector<fcc::ConstGenVertex>()), m_rel_EndVertex(new std::vector<fcc::ConstGenVertex>()),m_data(new MCParticleDataContainer() ) {
    m_refCollections.push_back(new std::vector<podio::ObjectID>());
  m_refCollections.push_back(new std::vector<podio::ObjectID>());

}

MCParticleCollection::~MCParticleCollection() {
  clear();
  if (m_data != nullptr) delete m_data;
    for (auto& pointer : m_refCollections) { if (pointer != nullptr) delete pointer; }
  if (m_rel_StartVertex != nullptr) { delete m_rel_StartVertex; }
  if (m_rel_EndVertex != nullptr) { delete m_rel_EndVertex; }

};

const MCParticle MCParticleCollection::operator[](unsigned int index) const {
  return MCParticle(m_entries[index]);
}

const MCParticle MCParticleCollection::at(unsigned int index) const {
  return MCParticle(m_entries.at(index));
}

int  MCParticleCollection::size() const {
  return m_entries.size();
}

MCParticle MCParticleCollection::create(){
  auto obj = new MCParticleObj();
  m_entries.emplace_back(obj);

  obj->id = {int(m_entries.size()-1),m_collectionID};
  return MCParticle(obj);
}

void MCParticleCollection::clear(){
  m_data->clear();
  for (auto& pointer : m_refCollections) { pointer->clear(); }
  for (auto& item : (*m_rel_StartVertex)) { item.unlink(); }
  m_rel_StartVertex->clear();
  for (auto& item : (*m_rel_EndVertex)) { item.unlink(); }
  m_rel_EndVertex->clear();

  for (auto& obj : m_entries) { delete obj; }
  m_entries.clear();
}

void MCParticleCollection::prepareForWrite(){
  auto size = m_entries.size();
  m_data->reserve(size);
  for (auto& obj : m_entries) {m_data->push_back(obj->data); }
  for (auto& pointer : m_refCollections) {pointer->clear(); } 

  for(int i=0, size = m_data->size(); i != size; ++i){

  }
  for (auto& obj : m_entries) {
    if (obj->m_StartVertex != nullptr) {
      m_refCollections[0]->emplace_back(obj->m_StartVertex->getObjectID());
    } else {
      m_refCollections[0]->push_back({-2,-2});
    }
  }
  for (auto& obj : m_entries) {
    if (obj->m_EndVertex != nullptr) {
      m_refCollections[1]->emplace_back(obj->m_EndVertex->getObjectID());
    } else {
      m_refCollections[1]->push_back({-2,-2});
    }
  }

}

void MCParticleCollection::prepareAfterRead(){
  int index = 0;
  for (auto& data : *m_data){
    auto obj = new MCParticleObj({index,m_collectionID}, data);
    
    m_entries.emplace_back(obj);
    ++index;
  }
  m_isValid = true;  
}

bool MCParticleCollection::setReferences(const podio::ICollectionProvider* collectionProvider){

  for(unsigned int i = 0, size = m_entries.size(); i != size; ++i) {
    auto id = (*m_refCollections[0])[i];
    if (id.index != podio::ObjectID::invalid) {
      CollectionBase* coll = nullptr;
      collectionProvider->get(id.collectionID,coll);
      fcc::GenVertexCollection* tmp_coll = static_cast<fcc::GenVertexCollection*>(coll);
      m_entries[i]->m_StartVertex = new ConstGenVertex((*tmp_coll)[id.index]);
    } else {
      m_entries[i]->m_StartVertex = nullptr;
    }
  }
  for(unsigned int i = 0, size = m_entries.size(); i != size; ++i) {
    auto id = (*m_refCollections[1])[i];
    if (id.index != podio::ObjectID::invalid) {
      CollectionBase* coll = nullptr;
      collectionProvider->get(id.collectionID,coll);
      fcc::GenVertexCollection* tmp_coll = static_cast<fcc::GenVertexCollection*>(coll);
      m_entries[i]->m_EndVertex = new ConstGenVertex((*tmp_coll)[id.index]);
    } else {
      m_entries[i]->m_EndVertex = nullptr;
    }
  }

  return true; //TODO: check success
}

void MCParticleCollection::push_back(ConstMCParticle object){
  int size = m_entries.size();
  auto obj = object.m_obj;
  if (obj->id.index == podio::ObjectID::untracked) {
      obj->id = {size,m_collectionID};
      m_entries.push_back(obj);
      
  } else {
    throw std::invalid_argument( "Object already in a collection. Cannot add it to a second collection " );
  }
}

void MCParticleCollection::setBuffer(void* address){
  if (m_data != nullptr) delete m_data;
  m_data = static_cast<MCParticleDataContainer*>(address);
}


const MCParticle MCParticleCollectionIterator::operator* () const {
  m_object.m_obj = (*m_collection)[m_index];
  return m_object;
}

const MCParticle* MCParticleCollectionIterator::operator-> () const {
  m_object.m_obj = (*m_collection)[m_index];
  return &m_object;
}

const MCParticleCollectionIterator& MCParticleCollectionIterator::operator++() const {
  ++m_index;
  return *this;
}

} // namespace fcc
