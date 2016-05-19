// datamodel specific includes
#include "SimCaloHitMCParticleAssociation.h"
#include "SimCaloHitMCParticleAssociationConst.h"
#include "SimCaloHitMCParticleAssociationObj.h"
#include "SimCaloHitMCParticleAssociationData.h"
#include "SimCaloHitMCParticleAssociationCollection.h"
#include <iostream>
#include "SimCaloHit.h"
#include "MCParticle.h"


namespace fcc {

ConstSimCaloHitMCParticleAssociation::ConstSimCaloHitMCParticleAssociation() : m_obj(new SimCaloHitMCParticleAssociationObj()) {
 m_obj->acquire();
}

ConstSimCaloHitMCParticleAssociation::ConstSimCaloHitMCParticleAssociation(float Fraction) : m_obj(new SimCaloHitMCParticleAssociationObj()){
 m_obj->acquire();
   m_obj->data.Fraction = Fraction;
}


ConstSimCaloHitMCParticleAssociation::ConstSimCaloHitMCParticleAssociation(const ConstSimCaloHitMCParticleAssociation& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

ConstSimCaloHitMCParticleAssociation& ConstSimCaloHitMCParticleAssociation::operator=(const ConstSimCaloHitMCParticleAssociation& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

ConstSimCaloHitMCParticleAssociation::ConstSimCaloHitMCParticleAssociation(SimCaloHitMCParticleAssociationObj* obj) : m_obj(obj) {
  if(m_obj != nullptr)
    m_obj->acquire();
}

ConstSimCaloHitMCParticleAssociation ConstSimCaloHitMCParticleAssociation::clone() const {
  return {new SimCaloHitMCParticleAssociationObj(*m_obj)};
}

ConstSimCaloHitMCParticleAssociation::~ConstSimCaloHitMCParticleAssociation(){
  if ( m_obj != nullptr) m_obj->release();
}

  const float& ConstSimCaloHitMCParticleAssociation::Fraction() const { return m_obj->data.Fraction; }
  const fcc::ConstSimCaloHit ConstSimCaloHitMCParticleAssociation::Hit() const {
    if (m_obj->m_Hit == nullptr) {
      return fcc::ConstSimCaloHit(nullptr);
    }
    return fcc::ConstSimCaloHit(*(m_obj->m_Hit));}  const fcc::ConstMCParticle ConstSimCaloHitMCParticleAssociation::Particle() const {
    if (m_obj->m_Particle == nullptr) {
      return fcc::ConstMCParticle(nullptr);
    }
    return fcc::ConstMCParticle(*(m_obj->m_Particle));}


bool  ConstSimCaloHitMCParticleAssociation::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID ConstSimCaloHitMCParticleAssociation::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool ConstSimCaloHitMCParticleAssociation::operator==(const SimCaloHitMCParticleAssociation& other) const {
     return (m_obj==other.m_obj);
}

//bool operator< (const SimCaloHitMCParticleAssociation& p1, const SimCaloHitMCParticleAssociation& p2 ) {
//  if( p1.m_containerID == p2.m_containerID ) {
//    return p1.m_index < p2.m_index;
//  } else {
//    return p1.m_containerID < p2.m_containerID;
//  }
//}

} // namespace fcc
