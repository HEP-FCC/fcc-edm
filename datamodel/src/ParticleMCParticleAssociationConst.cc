// datamodel specific includes
#include "ParticleMCParticleAssociation.h"
#include "ParticleMCParticleAssociationConst.h"
#include "ParticleMCParticleAssociationObj.h"
#include "ParticleMCParticleAssociationData.h"
#include "ParticleMCParticleAssociationCollection.h"
#include <iostream>
#include "Particle.h"
#include "MCParticle.h"




ConstParticleMCParticleAssociation::ConstParticleMCParticleAssociation() : m_obj(new ParticleMCParticleAssociationObj()){
 m_obj->acquire();
}



ConstParticleMCParticleAssociation::ConstParticleMCParticleAssociation(const ConstParticleMCParticleAssociation& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

ConstParticleMCParticleAssociation& ConstParticleMCParticleAssociation::operator=(const ConstParticleMCParticleAssociation& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

ConstParticleMCParticleAssociation::ConstParticleMCParticleAssociation(ParticleMCParticleAssociationObj* obj) : m_obj(obj){
  if(m_obj != nullptr)
    m_obj->acquire();
}

ConstParticleMCParticleAssociation ConstParticleMCParticleAssociation::clone() const {
  return {new ParticleMCParticleAssociationObj(*m_obj)};
}

ConstParticleMCParticleAssociation::~ConstParticleMCParticleAssociation(){
  if ( m_obj != nullptr) m_obj->release();
}

  const ConstParticle ConstParticleMCParticleAssociation::Rec() const { if (m_obj->m_Rec == nullptr) {
 return ConstParticle(nullptr);}
 return ConstParticle(*(m_obj->m_Rec));}
  const ConstMCParticle ConstParticleMCParticleAssociation::Sim() const { if (m_obj->m_Sim == nullptr) {
 return ConstMCParticle(nullptr);}
 return ConstMCParticle(*(m_obj->m_Sim));}


bool  ConstParticleMCParticleAssociation::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID ConstParticleMCParticleAssociation::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool ConstParticleMCParticleAssociation::operator==(const ParticleMCParticleAssociation& other) const {
     return (m_obj==other.m_obj);
}

//bool operator< (const ParticleMCParticleAssociation& p1, const ParticleMCParticleAssociation& p2 ) {
//  if( p1.m_containerID == p2.m_containerID ) {
//    return p1.m_index < p2.m_index;
//  } else {
//    return p1.m_containerID < p2.m_containerID;
//  }
//}


