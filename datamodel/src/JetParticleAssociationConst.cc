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

ConstJetParticleAssociation::ConstJetParticleAssociation() : m_obj(new JetParticleAssociationObj()){
 m_obj->acquire();
}



ConstJetParticleAssociation::ConstJetParticleAssociation(const ConstJetParticleAssociation& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

ConstJetParticleAssociation& ConstJetParticleAssociation::operator=(const ConstJetParticleAssociation& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

ConstJetParticleAssociation::ConstJetParticleAssociation(JetParticleAssociationObj* obj) : m_obj(obj){
  if(m_obj != nullptr)
    m_obj->acquire();
}

ConstJetParticleAssociation ConstJetParticleAssociation::clone() const {
  return {new JetParticleAssociationObj(*m_obj)};
}

ConstJetParticleAssociation::~ConstJetParticleAssociation(){
  if ( m_obj != nullptr) m_obj->release();
}

  const fcc::ConstJet ConstJetParticleAssociation::Jet() const { if (m_obj->m_Jet == nullptr) {
 return fcc::ConstJet(nullptr);}
 return fcc::ConstJet(*(m_obj->m_Jet));}
  const fcc::ConstParticle ConstJetParticleAssociation::Particle() const { if (m_obj->m_Particle == nullptr) {
 return fcc::ConstParticle(nullptr);}
 return fcc::ConstParticle(*(m_obj->m_Particle));}


bool  ConstJetParticleAssociation::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID ConstJetParticleAssociation::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool ConstJetParticleAssociation::operator==(const JetParticleAssociation& other) const {
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
