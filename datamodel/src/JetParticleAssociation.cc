// datamodel specific includes
#include "JetParticleAssociation.h"
#include "JetParticleAssociationConst.h"
#include "JetParticleAssociationObj.h"
#include "JetParticleAssociationData.h"
#include "JetParticleAssociationCollection.h"
#include <iostream>
#include "Jet.h"
#include "Particle.h"


namespace fcc {

JetParticleAssociation::JetParticleAssociation() : m_obj(new JetParticleAssociationObj()){
 m_obj->acquire();
}



JetParticleAssociation::JetParticleAssociation(const JetParticleAssociation& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

JetParticleAssociation& JetParticleAssociation::operator=(const JetParticleAssociation& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

JetParticleAssociation::JetParticleAssociation(JetParticleAssociationObj* obj) : m_obj(obj){
  if(m_obj != nullptr)
    m_obj->acquire();
}

JetParticleAssociation JetParticleAssociation::clone() const {
  return {new JetParticleAssociationObj(*m_obj)};
}

JetParticleAssociation::~JetParticleAssociation(){
  if ( m_obj != nullptr) m_obj->release();
}

JetParticleAssociation::operator ConstJetParticleAssociation() const {return ConstJetParticleAssociation(m_obj);}

  const fcc::ConstJet JetParticleAssociation::Jet() const {
    if (m_obj->m_Jet == nullptr) {
      return fcc::ConstJet(nullptr);
    }
    return fcc::ConstJet(*(m_obj->m_Jet));
  } const fcc::ConstParticle JetParticleAssociation::Particle() const {
    if (m_obj->m_Particle == nullptr) {
      return fcc::ConstParticle(nullptr);
    }
    return fcc::ConstParticle(*(m_obj->m_Particle));
  }
void JetParticleAssociation::Jet(fcc::ConstJet value) {
  if (m_obj->m_Jet != nullptr) delete m_obj->m_Jet;
  m_obj->m_Jet = new ConstJet(value);
}
void JetParticleAssociation::Particle(fcc::ConstParticle value) {
  if (m_obj->m_Particle != nullptr) delete m_obj->m_Particle;
  m_obj->m_Particle = new ConstParticle(value);
}



bool  JetParticleAssociation::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID JetParticleAssociation::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool JetParticleAssociation::operator==(const ConstJetParticleAssociation& other) const {
  return (m_obj==other.m_obj);
}


//bool operator< (const JetParticleAssociation& p1, const JetParticleAssociation& p2 ) {
//  if( p1.m_containerID == p2.m_containerID ) {
//    return p1.m_index < p2.m_index;
//  } else {
//    return p1.m_containerID < p2.m_containerID;
//  }
//}

} // namespace fcc
