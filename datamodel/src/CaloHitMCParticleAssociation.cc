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

CaloHitMCParticleAssociation::CaloHitMCParticleAssociation() : m_obj(new CaloHitMCParticleAssociationObj()){
 m_obj->acquire();
}

CaloHitMCParticleAssociation::CaloHitMCParticleAssociation(float fraction) : m_obj(new CaloHitMCParticleAssociationObj()) {
  m_obj->acquire();
    m_obj->data.fraction = fraction;
}


CaloHitMCParticleAssociation::CaloHitMCParticleAssociation(const CaloHitMCParticleAssociation& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

CaloHitMCParticleAssociation& CaloHitMCParticleAssociation::operator=(const CaloHitMCParticleAssociation& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

CaloHitMCParticleAssociation::CaloHitMCParticleAssociation(CaloHitMCParticleAssociationObj* obj) : m_obj(obj){
  if(m_obj != nullptr)
    m_obj->acquire();
}

CaloHitMCParticleAssociation CaloHitMCParticleAssociation::clone() const {
  return {new CaloHitMCParticleAssociationObj(*m_obj)};
}

CaloHitMCParticleAssociation::~CaloHitMCParticleAssociation(){
  if ( m_obj != nullptr) m_obj->release();
}

CaloHitMCParticleAssociation::operator ConstCaloHitMCParticleAssociation() const {return ConstCaloHitMCParticleAssociation(m_obj);}

  const float& CaloHitMCParticleAssociation::fraction() const { return m_obj->data.fraction; }
  const fcc::ConstCaloHit CaloHitMCParticleAssociation::hit() const {
    if (m_obj->m_hit == nullptr) {
      return fcc::ConstCaloHit(nullptr);
    }
    return fcc::ConstCaloHit(*(m_obj->m_hit));
  } const fcc::ConstMCParticle CaloHitMCParticleAssociation::particle() const {
    if (m_obj->m_particle == nullptr) {
      return fcc::ConstMCParticle(nullptr);
    }
    return fcc::ConstMCParticle(*(m_obj->m_particle));
  }
void CaloHitMCParticleAssociation::fraction(float value){ m_obj->data.fraction = value; }
void CaloHitMCParticleAssociation::hit(fcc::ConstCaloHit value) {
  if (m_obj->m_hit != nullptr) delete m_obj->m_hit;
  m_obj->m_hit = new ConstCaloHit(value);
}
void CaloHitMCParticleAssociation::particle(fcc::ConstMCParticle value) {
  if (m_obj->m_particle != nullptr) delete m_obj->m_particle;
  m_obj->m_particle = new ConstMCParticle(value);
}



bool  CaloHitMCParticleAssociation::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID CaloHitMCParticleAssociation::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool CaloHitMCParticleAssociation::operator==(const ConstCaloHitMCParticleAssociation& other) const {
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
