// datamodel specific includes
#include "GenJet.h"
#include "GenJetConst.h"
#include "GenJetObj.h"
#include "GenJetData.h"
#include "GenJetCollection.h"
#include <iostream>


namespace fcc {

ConstGenJet::ConstGenJet() : m_obj(new GenJetObj()) {
 m_obj->acquire();
}

ConstGenJet::ConstGenJet(fcc::BareJet core) : m_obj(new GenJetObj()){
 m_obj->acquire();
   m_obj->data.core = core;
}


ConstGenJet::ConstGenJet(const ConstGenJet& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

ConstGenJet& ConstGenJet::operator=(const ConstGenJet& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

ConstGenJet::ConstGenJet(GenJetObj* obj) : m_obj(obj) {
  if(m_obj != nullptr)
    m_obj->acquire();
}

ConstGenJet ConstGenJet::clone() const {
  return {new GenJetObj(*m_obj)};
}

ConstGenJet::~ConstGenJet(){
  if ( m_obj != nullptr) m_obj->release();
}

  const float& ConstGenJet::area() const { return m_obj->data.core.area; }
  const unsigned& ConstGenJet::bits() const { return m_obj->data.core.bits; }
  const ::fcc::LorentzVector& ConstGenJet::p4() const { return m_obj->data.core.p4; }
  /// Access the  Basic jet information.
  const fcc::BareJet& ConstGenJet::core() const { return m_obj->data.core; }

std::vector<fcc::ConstMCParticle>::const_iterator ConstGenJet::particles_begin() const {
  auto ret_value = m_obj->m_particles->begin();
  std::advance(ret_value, m_obj->data.particles_begin);
  return ret_value;
}

std::vector<fcc::ConstMCParticle>::const_iterator ConstGenJet::particles_end() const {
  auto ret_value = m_obj->m_particles->begin();
  std::advance(ret_value, m_obj->data.particles_end-1);
  return ++ret_value;
}

unsigned int ConstGenJet::particles_size() const {
  return (m_obj->data.particles_end-m_obj->data.particles_begin);
}

fcc::ConstMCParticle ConstGenJet::particles(unsigned int index) const {
  if (particles_size() > index) {
    return m_obj->m_particles->at(m_obj->data.particles_begin+index);
  }
  else throw std::out_of_range ("index out of bounds for existing references");
}


bool  ConstGenJet::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID ConstGenJet::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool ConstGenJet::operator==(const GenJet& other) const {
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
