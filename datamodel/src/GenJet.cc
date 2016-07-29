// datamodel specific includes
#include "GenJet.h"
#include "GenJetConst.h"
#include "GenJetObj.h"
#include "GenJetData.h"
#include "GenJetCollection.h"
#include <iostream>


namespace fcc {

GenJet::GenJet() : m_obj(new GenJetObj()){
 m_obj->acquire();
}

GenJet::GenJet(fcc::BareJet core) : m_obj(new GenJetObj()) {
  m_obj->acquire();
    m_obj->data.core = core;
}


GenJet::GenJet(const GenJet& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

GenJet& GenJet::operator=(const GenJet& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

GenJet::GenJet(GenJetObj* obj) : m_obj(obj){
  if(m_obj != nullptr)
    m_obj->acquire();
}

GenJet GenJet::clone() const {
  return {new GenJetObj(*m_obj)};
}

GenJet::~GenJet(){
  if ( m_obj != nullptr) m_obj->release();
}

GenJet::operator ConstGenJet() const {return ConstGenJet(m_obj);}

  const fcc::BareJet& GenJet::core() const { return m_obj->data.core; }
const float& GenJet::area() const { return m_obj->data.core.area; }
const unsigned& GenJet::bits() const { return m_obj->data.core.bits; }
const ::fcc::LorentzVector& GenJet::p4() const { return m_obj->data.core.p4; }

  fcc::BareJet& GenJet::core() { return m_obj->data.core; }
void GenJet::core(class fcc::BareJet value) { m_obj->data.core = value; }
void GenJet::area(float value){ m_obj->data.core.area = value; }
void GenJet::bits(unsigned value){ m_obj->data.core.bits = value; }
::fcc::LorentzVector& GenJet::p4() { return m_obj->data.core.p4; }
void GenJet::p4(class ::fcc::LorentzVector value) { m_obj->data.core.p4 = value; }

std::vector<fcc::ConstMCParticle>::const_iterator GenJet::particles_begin() const {
  auto ret_value = m_obj->m_particles->begin();
  std::advance(ret_value, m_obj->data.particles_begin);
  return ret_value;
}

std::vector<fcc::ConstMCParticle>::const_iterator GenJet::particles_end() const {
  auto ret_value = m_obj->m_particles->begin();
//fg: this code fails if m_obj->data.particles==0
//  std::advance(ret_value, m_obj->data.particles_end-1);
//  return ++ret_value;
  std::advance(ret_value, m_obj->data.particles_end);
  return ret_value;
}

void GenJet::addparticles(fcc::ConstMCParticle component) {
  m_obj->m_particles->push_back(component);
  m_obj->data.particles_end++;
}

unsigned int GenJet::particles_size() const {
  return (m_obj->data.particles_end-m_obj->data.particles_begin);
}

fcc::ConstMCParticle GenJet::particles(unsigned int index) const {
  if (particles_size() > index) {
    return m_obj->m_particles->at(m_obj->data.particles_begin+index);
  }
  else throw std::out_of_range ("index out of bounds for existing references");
}


bool  GenJet::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID GenJet::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool GenJet::operator==(const ConstGenJet& other) const {
  return (m_obj==other.m_obj);
}


//bool operator< (const GenJet& p1, const GenJet& p2 ) {
//  if( p1.m_containerID == p2.m_containerID ) {
//    return p1.m_index < p2.m_index;
//  } else {
//    return p1.m_containerID < p2.m_containerID;
//  }
//}

} // namespace fcc
