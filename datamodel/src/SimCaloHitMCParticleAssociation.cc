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

SimCaloHitMCParticleAssociation::SimCaloHitMCParticleAssociation() : m_obj(new SimCaloHitMCParticleAssociationObj()){
 m_obj->acquire();
}

SimCaloHitMCParticleAssociation::SimCaloHitMCParticleAssociation(float Fraction) : m_obj(new SimCaloHitMCParticleAssociationObj()){
 m_obj->acquire();
   m_obj->data.Fraction = Fraction;
}


SimCaloHitMCParticleAssociation::SimCaloHitMCParticleAssociation(const SimCaloHitMCParticleAssociation& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

SimCaloHitMCParticleAssociation& SimCaloHitMCParticleAssociation::operator=(const SimCaloHitMCParticleAssociation& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

SimCaloHitMCParticleAssociation::SimCaloHitMCParticleAssociation(SimCaloHitMCParticleAssociationObj* obj) : m_obj(obj){
  if(m_obj != nullptr)
    m_obj->acquire();
}

SimCaloHitMCParticleAssociation SimCaloHitMCParticleAssociation::clone() const {
  return {new SimCaloHitMCParticleAssociationObj(*m_obj)};
}

SimCaloHitMCParticleAssociation::~SimCaloHitMCParticleAssociation(){
  if ( m_obj != nullptr) m_obj->release();
}

SimCaloHitMCParticleAssociation::operator ConstSimCaloHitMCParticleAssociation() const {return ConstSimCaloHitMCParticleAssociation(m_obj);}

  const float& SimCaloHitMCParticleAssociation::Fraction() const { return m_obj->data.Fraction; }
  const fcc::ConstSimCaloHit SimCaloHitMCParticleAssociation::Hit() const { if (m_obj->m_Hit == nullptr) {
 return fcc::ConstSimCaloHit(nullptr);}
 return fcc::ConstSimCaloHit(*(m_obj->m_Hit));}
  const fcc::ConstMCParticle SimCaloHitMCParticleAssociation::Particle() const { if (m_obj->m_Particle == nullptr) {
 return fcc::ConstMCParticle(nullptr);}
 return fcc::ConstMCParticle(*(m_obj->m_Particle));}

void SimCaloHitMCParticleAssociation::Fraction(float value){ m_obj->data.Fraction = value;}
void SimCaloHitMCParticleAssociation::Hit(fcc::ConstSimCaloHit value) { if (m_obj->m_Hit != nullptr) delete m_obj->m_Hit; m_obj->m_Hit = new ConstSimCaloHit(value); }
void SimCaloHitMCParticleAssociation::Particle(fcc::ConstMCParticle value) { if (m_obj->m_Particle != nullptr) delete m_obj->m_Particle; m_obj->m_Particle = new ConstMCParticle(value); }


bool  SimCaloHitMCParticleAssociation::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID SimCaloHitMCParticleAssociation::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool SimCaloHitMCParticleAssociation::operator==(const ConstSimCaloHitMCParticleAssociation& other) const {
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
