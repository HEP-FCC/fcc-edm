// datamodel specific includes
#include "ParticleMCParticleAssociation.h"
#include "ParticleMCParticleAssociationConst.h"
#include "ParticleMCParticleAssociationObj.h"
#include "ParticleMCParticleAssociationData.h"
#include "ParticleMCParticleAssociationCollection.h"
#include <iostream>
#include "Particle.h"
#include "MCParticle.h"


namespace fcc {

ParticleMCParticleAssociation::ParticleMCParticleAssociation() : m_obj(new ParticleMCParticleAssociationObj()){
 m_obj->acquire();
}



ParticleMCParticleAssociation::ParticleMCParticleAssociation(const ParticleMCParticleAssociation& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

ParticleMCParticleAssociation& ParticleMCParticleAssociation::operator=(const ParticleMCParticleAssociation& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

ParticleMCParticleAssociation::ParticleMCParticleAssociation(ParticleMCParticleAssociationObj* obj) : m_obj(obj){
  if(m_obj != nullptr)
    m_obj->acquire();
}

ParticleMCParticleAssociation ParticleMCParticleAssociation::clone() const {
  return {new ParticleMCParticleAssociationObj(*m_obj)};
}

ParticleMCParticleAssociation::~ParticleMCParticleAssociation(){
  if ( m_obj != nullptr) m_obj->release();
}

ParticleMCParticleAssociation::operator ConstParticleMCParticleAssociation() const {return ConstParticleMCParticleAssociation(m_obj);}

  const fcc::ConstParticle ParticleMCParticleAssociation::Rec() const {
    if (m_obj->m_Rec == nullptr) {
      return fcc::ConstParticle(nullptr);
    }
    return fcc::ConstParticle(*(m_obj->m_Rec));
  } const fcc::ConstMCParticle ParticleMCParticleAssociation::Sim() const {
    if (m_obj->m_Sim == nullptr) {
      return fcc::ConstMCParticle(nullptr);
    }
    return fcc::ConstMCParticle(*(m_obj->m_Sim));
  }
void ParticleMCParticleAssociation::Rec(fcc::ConstParticle value) {
  if (m_obj->m_Rec != nullptr) delete m_obj->m_Rec;
  m_obj->m_Rec = new ConstParticle(value);
}
void ParticleMCParticleAssociation::Sim(fcc::ConstMCParticle value) {
  if (m_obj->m_Sim != nullptr) delete m_obj->m_Sim;
  m_obj->m_Sim = new ConstMCParticle(value);
}



bool  ParticleMCParticleAssociation::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID ParticleMCParticleAssociation::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool ParticleMCParticleAssociation::operator==(const ConstParticleMCParticleAssociation& other) const {
  return (m_obj==other.m_obj);
}


//bool operator< (const ParticleMCParticleAssociation& p1, const ParticleMCParticleAssociation& p2 ) {
//  if( p1.m_containerID == p2.m_containerID ) {
//    return p1.m_index < p2.m_index;
//  } else {
//    return p1.m_containerID < p2.m_containerID;
//  }
//}

} // namespace fcc
