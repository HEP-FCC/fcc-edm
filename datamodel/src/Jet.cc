// datamodel specific includes
#include "Jet.h"
#include "JetConst.h"
#include "JetObj.h"
#include "JetData.h"
#include "JetCollection.h"
#include <iostream>


namespace fcc {

Jet::Jet() : m_obj(new JetObj()){
 m_obj->acquire();
}

Jet::Jet(fcc::BareJet core) : m_obj(new JetObj()) {
  m_obj->acquire();
    m_obj->data.core = core;
}


Jet::Jet(const Jet& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

Jet& Jet::operator=(const Jet& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

Jet::Jet(JetObj* obj) : m_obj(obj){
  if(m_obj != nullptr)
    m_obj->acquire();
}

Jet Jet::clone() const {
  return {new JetObj(*m_obj)};
}

Jet::~Jet(){
  if ( m_obj != nullptr) m_obj->release();
}

Jet::operator ConstJet() const {return ConstJet(m_obj);}

  const fcc::BareJet& Jet::core() const { return m_obj->data.core; }
const float& Jet::area() const { return m_obj->data.core.area; }
const unsigned& Jet::bits() const { return m_obj->data.core.bits; }
const ::fcc::LorentzVector& Jet::p4() const { return m_obj->data.core.p4; }

  fcc::BareJet& Jet::core() { return m_obj->data.core; }
void Jet::core(class fcc::BareJet value) { m_obj->data.core = value; }
void Jet::area(float value){ m_obj->data.core.area = value; }
void Jet::bits(unsigned value){ m_obj->data.core.bits = value; }
::fcc::LorentzVector& Jet::p4() { return m_obj->data.core.p4; }
void Jet::p4(class ::fcc::LorentzVector value) { m_obj->data.core.p4 = value; }

std::vector<fcc::ConstParticle>::const_iterator Jet::particles_begin() const {
  auto ret_value = m_obj->m_particles->begin();
  std::advance(ret_value, m_obj->data.particles_begin);
  return ret_value;
}

std::vector<fcc::ConstParticle>::const_iterator Jet::particles_end() const {
  auto ret_value = m_obj->m_particles->begin();
//fg: this code fails if m_obj->data.particles==0
//  std::advance(ret_value, m_obj->data.particles_end-1);
//  return ++ret_value;
  std::advance(ret_value, m_obj->data.particles_end);
  return ret_value;
}

void Jet::addparticles(fcc::ConstParticle component) {
  m_obj->m_particles->push_back(component);
  m_obj->data.particles_end++;
}

unsigned int Jet::particles_size() const {
  return (m_obj->data.particles_end-m_obj->data.particles_begin);
}

fcc::ConstParticle Jet::particles(unsigned int index) const {
  if (particles_size() > index) {
    return m_obj->m_particles->at(m_obj->data.particles_begin+index);
  }
  else throw std::out_of_range ("index out of bounds for existing references");
}


bool  Jet::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID Jet::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool Jet::operator==(const ConstJet& other) const {
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
