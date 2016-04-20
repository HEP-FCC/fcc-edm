// datamodel specific includes
#include "MCParticle.h"
#include "MCParticleConst.h"
#include "MCParticleObj.h"
#include "MCParticleData.h"
#include "MCParticleCollection.h"
#include <iostream>
#include "GenVertex.h"
#include "GenVertex.h"


namespace fcc {

MCParticle::MCParticle() : m_obj(new MCParticleObj()){
 m_obj->acquire();
}

MCParticle::MCParticle(fcc::BareParticle Core) : m_obj(new MCParticleObj()) {
  m_obj->acquire();
    m_obj->data.Core = Core;
}


MCParticle::MCParticle(const MCParticle& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

MCParticle& MCParticle::operator=(const MCParticle& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

MCParticle::MCParticle(MCParticleObj* obj) : m_obj(obj){
  if(m_obj != nullptr)
    m_obj->acquire();
}

MCParticle MCParticle::clone() const {
  return {new MCParticleObj(*m_obj)};
}

MCParticle::~MCParticle(){
  if ( m_obj != nullptr) m_obj->release();
}

MCParticle::operator ConstMCParticle() const {return ConstMCParticle(m_obj);}

  const fcc::BareParticle& MCParticle::Core() const { return m_obj->data.Core; }
  const fcc::ConstGenVertex MCParticle::StartVertex() const {
    if (m_obj->m_StartVertex == nullptr) {
      return fcc::ConstGenVertex(nullptr);
    }
    return fcc::ConstGenVertex(*(m_obj->m_StartVertex));
  } const fcc::ConstGenVertex MCParticle::EndVertex() const {
    if (m_obj->m_EndVertex == nullptr) {
      return fcc::ConstGenVertex(nullptr);
    }
    return fcc::ConstGenVertex(*(m_obj->m_EndVertex));
  }
  fcc::BareParticle& MCParticle::Core() { return m_obj->data.Core; }
void MCParticle::Core(class fcc::BareParticle value) { m_obj->data.Core = value; }
void MCParticle::StartVertex(fcc::ConstGenVertex value) {
  if (m_obj->m_StartVertex != nullptr) delete m_obj->m_StartVertex;
  m_obj->m_StartVertex = new ConstGenVertex(value);
}
void MCParticle::EndVertex(fcc::ConstGenVertex value) {
  if (m_obj->m_EndVertex != nullptr) delete m_obj->m_EndVertex;
  m_obj->m_EndVertex = new ConstGenVertex(value);
}



bool  MCParticle::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID MCParticle::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool MCParticle::operator==(const ConstMCParticle& other) const {
  return (m_obj==other.m_obj);
}


//bool operator< (const MCParticle& p1, const MCParticle& p2 ) {
//  if( p1.m_containerID == p2.m_containerID ) {
//    return p1.m_index < p2.m_index;
//  } else {
//    return p1.m_containerID < p2.m_containerID;
//  }
//}

} // namespace fcc
