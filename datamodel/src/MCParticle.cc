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

MCParticle::MCParticle(fcc::BareParticle core) : m_obj(new MCParticleObj()) {
  m_obj->acquire();
    m_obj->data.core = core;
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

  const fcc::BareParticle& MCParticle::core() const { return m_obj->data.core; }
const unsigned& MCParticle::bits() const { return m_obj->data.core.bits; }
const int& MCParticle::charge() const { return m_obj->data.core.charge; }
const ::fcc::LorentzVector& MCParticle::p4() const { return m_obj->data.core.p4; }
const unsigned& MCParticle::status() const { return m_obj->data.core.status; }
const int& MCParticle::type() const { return m_obj->data.core.type; }
const ::fcc::Point& MCParticle::vertex() const { return m_obj->data.core.vertex; }
  const fcc::ConstGenVertex MCParticle::startVertex() const {
    if (m_obj->m_startVertex == nullptr) {
      return fcc::ConstGenVertex(nullptr);
    }
    return fcc::ConstGenVertex(*(m_obj->m_startVertex));
  } const fcc::ConstGenVertex MCParticle::endVertex() const {
    if (m_obj->m_endVertex == nullptr) {
      return fcc::ConstGenVertex(nullptr);
    }
    return fcc::ConstGenVertex(*(m_obj->m_endVertex));
  }
  fcc::BareParticle& MCParticle::core() { return m_obj->data.core; }
void MCParticle::core(class fcc::BareParticle value) { m_obj->data.core = value; }
void MCParticle::bits(unsigned value){ m_obj->data.core.bits = value; }
void MCParticle::charge(int value){ m_obj->data.core.charge = value; }
::fcc::LorentzVector& MCParticle::p4() { return m_obj->data.core.p4; }
void MCParticle::p4(class ::fcc::LorentzVector value) { m_obj->data.core.p4 = value; }
void MCParticle::status(unsigned value){ m_obj->data.core.status = value; }
void MCParticle::type(int value){ m_obj->data.core.type = value; }
::fcc::Point& MCParticle::vertex() { return m_obj->data.core.vertex; }
void MCParticle::vertex(class ::fcc::Point value) { m_obj->data.core.vertex = value; }
void MCParticle::startVertex(fcc::ConstGenVertex value) {
  if (m_obj->m_startVertex != nullptr) delete m_obj->m_startVertex;
  m_obj->m_startVertex = new ConstGenVertex(value);
}
void MCParticle::endVertex(fcc::ConstGenVertex value) {
  if (m_obj->m_endVertex != nullptr) delete m_obj->m_endVertex;
  m_obj->m_endVertex = new ConstGenVertex(value);
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
