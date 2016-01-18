// datamodel specific includes
#include "GenJetParticleAssociation.h"
#include "GenJetParticleAssociationConst.h"
#include "GenJetParticleAssociationObj.h"
#include "GenJetParticleAssociationData.h"
#include "GenJetParticleAssociationCollection.h"
#include <iostream>
#include "GenJet.h"
#include "MCParticle.h"




GenJetParticleAssociation::GenJetParticleAssociation() : m_obj(new GenJetParticleAssociationObj()){
 m_obj->acquire();
}



GenJetParticleAssociation::GenJetParticleAssociation(const GenJetParticleAssociation& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

GenJetParticleAssociation& GenJetParticleAssociation::operator=(const GenJetParticleAssociation& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

GenJetParticleAssociation::GenJetParticleAssociation(GenJetParticleAssociationObj* obj) : m_obj(obj){
  if(m_obj != nullptr)
    m_obj->acquire();
}

GenJetParticleAssociation GenJetParticleAssociation::clone() const {
  return {new GenJetParticleAssociationObj(*m_obj)};
}

GenJetParticleAssociation::~GenJetParticleAssociation(){
  if ( m_obj != nullptr) m_obj->release();
}

GenJetParticleAssociation::operator ConstGenJetParticleAssociation() const {return ConstGenJetParticleAssociation(m_obj);}

  const ConstGenJet GenJetParticleAssociation::Jet() const { if (m_obj->m_Jet == nullptr) {
 return ConstGenJet(nullptr);}
 return ConstGenJet(*(m_obj->m_Jet));}
  const ConstMCParticle GenJetParticleAssociation::Particle() const { if (m_obj->m_Particle == nullptr) {
 return ConstMCParticle(nullptr);}
 return ConstMCParticle(*(m_obj->m_Particle));}

void GenJetParticleAssociation::Jet(ConstGenJet value) { if (m_obj->m_Jet != nullptr) delete m_obj->m_Jet; m_obj->m_Jet = new ConstGenJet(value); }
void GenJetParticleAssociation::Particle(ConstMCParticle value) { if (m_obj->m_Particle != nullptr) delete m_obj->m_Particle; m_obj->m_Particle = new ConstMCParticle(value); }


bool  GenJetParticleAssociation::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID GenJetParticleAssociation::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool GenJetParticleAssociation::operator==(const ConstGenJetParticleAssociation& other) const {
     return (m_obj==other.m_obj);
}


//bool operator< (const GenJetParticleAssociation& p1, const GenJetParticleAssociation& p2 ) {
//  if( p1.m_containerID == p2.m_containerID ) {
//    return p1.m_index < p2.m_index;
//  } else {
//    return p1.m_containerID < p2.m_containerID;
//  }
//}


