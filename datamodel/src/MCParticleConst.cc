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

ConstMCParticle::ConstMCParticle() : m_obj(new MCParticleObj()) {
 m_obj->acquire();
}

ConstMCParticle::ConstMCParticle(fcc::BareParticle Core) : m_obj(new MCParticleObj()){
 m_obj->acquire();
   m_obj->data.Core = Core;
}


ConstMCParticle::ConstMCParticle(const ConstMCParticle& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

ConstMCParticle& ConstMCParticle::operator=(const ConstMCParticle& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

ConstMCParticle::ConstMCParticle(MCParticleObj* obj) : m_obj(obj) {
  if(m_obj != nullptr)
    m_obj->acquire();
}

ConstMCParticle ConstMCParticle::clone() const {
  return {new MCParticleObj(*m_obj)};
}

ConstMCParticle::~ConstMCParticle(){
  if ( m_obj != nullptr) m_obj->release();
}

  const fcc::BareParticle& ConstMCParticle::Core() const { return m_obj->data.Core; }
  const fcc::ConstGenVertex ConstMCParticle::StartVertex() const {
    if (m_obj->m_StartVertex == nullptr) {
      return fcc::ConstGenVertex(nullptr);
    }
    return fcc::ConstGenVertex(*(m_obj->m_StartVertex));} const fcc::ConstGenVertex ConstMCParticle::EndVertex() const {
    if (m_obj->m_EndVertex == nullptr) {
      return fcc::ConstGenVertex(nullptr);
    }
    return fcc::ConstGenVertex(*(m_obj->m_EndVertex));}


bool  ConstMCParticle::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID ConstMCParticle::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool ConstMCParticle::operator==(const MCParticle& other) const {
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
