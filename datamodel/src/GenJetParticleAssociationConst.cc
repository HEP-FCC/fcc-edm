// datamodel specific includes
#include "GenJetParticleAssociation.h"
#include "GenJetParticleAssociationConst.h"
#include "GenJetParticleAssociationObj.h"
#include "GenJetParticleAssociationData.h"
#include "GenJetParticleAssociationCollection.h"
#include <iostream>
#include "GenJet.h"
#include "MCParticle.h"




ConstGenJetParticleAssociation::ConstGenJetParticleAssociation() : m_obj(new GenJetParticleAssociationObj()){
 m_obj->acquire();
}



ConstGenJetParticleAssociation::ConstGenJetParticleAssociation(const ConstGenJetParticleAssociation& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

ConstGenJetParticleAssociation& ConstGenJetParticleAssociation::operator=(const ConstGenJetParticleAssociation& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

ConstGenJetParticleAssociation::ConstGenJetParticleAssociation(GenJetParticleAssociationObj* obj) : m_obj(obj){
  if(m_obj != nullptr)
    m_obj->acquire();
}

ConstGenJetParticleAssociation ConstGenJetParticleAssociation::clone() const {
  return {new GenJetParticleAssociationObj(*m_obj)};
}

ConstGenJetParticleAssociation::~ConstGenJetParticleAssociation(){
  if ( m_obj != nullptr) m_obj->release();
}

  const ConstGenJet ConstGenJetParticleAssociation::Jet() const { if (m_obj->m_Jet == nullptr) {
 return ConstGenJet(nullptr);}
 return ConstGenJet(*(m_obj->m_Jet));}
  const ConstMCParticle ConstGenJetParticleAssociation::Particle() const { if (m_obj->m_Particle == nullptr) {
 return ConstMCParticle(nullptr);}
 return ConstMCParticle(*(m_obj->m_Particle));}


bool  ConstGenJetParticleAssociation::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID ConstGenJetParticleAssociation::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool ConstGenJetParticleAssociation::operator==(const GenJetParticleAssociation& other) const {
     return (m_obj==other.m_obj);
}

//bool operator< (const GenJetParticleAssociation& p1, const GenJetParticleAssociation& p2 ) {
//  if( p1.m_containerID == p2.m_containerID ) {
//    return p1.m_index < p2.m_index;
//  } else {
//    return p1.m_containerID < p2.m_containerID;
//  }
//}


