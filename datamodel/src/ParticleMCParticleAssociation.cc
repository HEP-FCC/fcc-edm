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

  const fcc::ConstParticle ParticleMCParticleAssociation::rec() const {
    if (m_obj->m_rec == nullptr) {
      return fcc::ConstParticle(nullptr);
    }
    return fcc::ConstParticle(*(m_obj->m_rec));
  } const fcc::ConstMCParticle ParticleMCParticleAssociation::sim() const {
    if (m_obj->m_sim == nullptr) {
      return fcc::ConstMCParticle(nullptr);
    }
    return fcc::ConstMCParticle(*(m_obj->m_sim));
  }
void ParticleMCParticleAssociation::rec(fcc::ConstParticle value) {
  if (m_obj->m_rec != nullptr) delete m_obj->m_rec;
  m_obj->m_rec = new ConstParticle(value);
}
void ParticleMCParticleAssociation::sim(fcc::ConstMCParticle value) {
  if (m_obj->m_sim != nullptr) delete m_obj->m_sim;
  m_obj->m_sim = new ConstMCParticle(value);
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
