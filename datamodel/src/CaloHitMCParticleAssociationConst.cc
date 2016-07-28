// datamodel specific includes
#include "CaloHitMCParticleAssociation.h"
#include "CaloHitMCParticleAssociationConst.h"
#include "CaloHitMCParticleAssociationObj.h"
#include "CaloHitMCParticleAssociationData.h"
#include "CaloHitMCParticleAssociationCollection.h"
#include <iostream>
#include "CaloHit.h"
#include "MCParticle.h"


namespace fcc {

ConstCaloHitMCParticleAssociation::ConstCaloHitMCParticleAssociation() : m_obj(new CaloHitMCParticleAssociationObj()) {
 m_obj->acquire();
}

ConstCaloHitMCParticleAssociation::ConstCaloHitMCParticleAssociation(float fraction) : m_obj(new CaloHitMCParticleAssociationObj()){
 m_obj->acquire();
   m_obj->data.fraction = fraction;
}


ConstCaloHitMCParticleAssociation::ConstCaloHitMCParticleAssociation(const ConstCaloHitMCParticleAssociation& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

ConstCaloHitMCParticleAssociation& ConstCaloHitMCParticleAssociation::operator=(const ConstCaloHitMCParticleAssociation& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

ConstCaloHitMCParticleAssociation::ConstCaloHitMCParticleAssociation(CaloHitMCParticleAssociationObj* obj) : m_obj(obj) {
  if(m_obj != nullptr)
    m_obj->acquire();
}

ConstCaloHitMCParticleAssociation ConstCaloHitMCParticleAssociation::clone() const {
  return {new CaloHitMCParticleAssociationObj(*m_obj)};
}

ConstCaloHitMCParticleAssociation::~ConstCaloHitMCParticleAssociation(){
  if ( m_obj != nullptr) m_obj->release();
}

  /// Access the  Fraction of the particle energy used in the hit.
  const float& ConstCaloHitMCParticleAssociation::fraction() const { return m_obj->data.fraction; }
  /// Access the  the hit
  const fcc::ConstCaloHit ConstCaloHitMCParticleAssociation::hit() const {
    if (m_obj->m_hit == nullptr) {
      return fcc::ConstCaloHit(nullptr);
    }
    return fcc::ConstCaloHit(*(m_obj->m_hit));} /// Access the  the particle
  const fcc::ConstMCParticle ConstCaloHitMCParticleAssociation::particle() const {
    if (m_obj->m_particle == nullptr) {
      return fcc::ConstMCParticle(nullptr);
    }
    return fcc::ConstMCParticle(*(m_obj->m_particle));}


bool  ConstCaloHitMCParticleAssociation::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID ConstCaloHitMCParticleAssociation::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool ConstCaloHitMCParticleAssociation::operator==(const CaloHitMCParticleAssociation& other) const {
     return (m_obj==other.m_obj);
}

//bool operator< (const CaloHitMCParticleAssociation& p1, const CaloHitMCParticleAssociation& p2 ) {
//  if( p1.m_containerID == p2.m_containerID ) {
//    return p1.m_index < p2.m_index;
//  } else {
//    return p1.m_containerID < p2.m_containerID;
//  }
//}

} // namespace fcc
