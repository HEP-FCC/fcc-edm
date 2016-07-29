// datamodel specific includes
#include "Jet.h"
#include "JetConst.h"
#include "JetObj.h"
#include "JetData.h"
#include "JetCollection.h"
#include <iostream>


namespace fcc {

ConstJet::ConstJet() : m_obj(new JetObj()) {
 m_obj->acquire();
}

ConstJet::ConstJet(fcc::BareJet core) : m_obj(new JetObj()){
 m_obj->acquire();
   m_obj->data.core = core;
}


ConstJet::ConstJet(const ConstJet& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

ConstJet& ConstJet::operator=(const ConstJet& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

ConstJet::ConstJet(JetObj* obj) : m_obj(obj) {
  if(m_obj != nullptr)
    m_obj->acquire();
}

ConstJet ConstJet::clone() const {
  return {new JetObj(*m_obj)};
}

ConstJet::~ConstJet(){
  if ( m_obj != nullptr) m_obj->release();
}

  const float& ConstJet::area() const { return m_obj->data.core.area; }
  const unsigned& ConstJet::bits() const { return m_obj->data.core.bits; }
  const ::fcc::LorentzVector& ConstJet::p4() const { return m_obj->data.core.p4; }
  /// Access the  Basic jet information.
  const fcc::BareJet& ConstJet::core() const { return m_obj->data.core; }

std::vector<fcc::ConstParticle>::const_iterator ConstJet::particles_begin() const {
  auto ret_value = m_obj->m_particles->begin();
  std::advance(ret_value, m_obj->data.particles_begin);
  return ret_value;
}

std::vector<fcc::ConstParticle>::const_iterator ConstJet::particles_end() const {
  auto ret_value = m_obj->m_particles->begin();
  std::advance(ret_value, m_obj->data.particles_end-1);
  return ++ret_value;
}

unsigned int ConstJet::particles_size() const {
  return (m_obj->data.particles_end-m_obj->data.particles_begin);
}

fcc::ConstParticle ConstJet::particles(unsigned int index) const {
  if (particles_size() > index) {
    return m_obj->m_particles->at(m_obj->data.particles_begin+index);
  }
  else throw std::out_of_range ("index out of bounds for existing references");
}


bool  ConstJet::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID ConstJet::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool ConstJet::operator==(const Jet& other) const {
     return (m_obj==other.m_obj);
}

//bool operator< (const Jet& p1, const Jet& p2 ) {
//  if( p1.m_containerID == p2.m_containerID ) {
//    return p1.m_index < p2.m_index;
//  } else {
//    return p1.m_containerID < p2.m_containerID;
//  }
//}

} // namespace fcc
