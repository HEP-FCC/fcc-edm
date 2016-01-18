// datamodel specific includes
#include "MCParticleAssociation.h"
#include "MCParticleAssociationConst.h"
#include "MCParticleAssociationObj.h"
#include "MCParticleAssociationData.h"
#include "MCParticleAssociationCollection.h"
#include <iostream>
#include "MCParticle.h"
#include "MCParticle.h"




ConstMCParticleAssociation::ConstMCParticleAssociation() : m_obj(new MCParticleAssociationObj()){
 m_obj->acquire();
}



ConstMCParticleAssociation::ConstMCParticleAssociation(const ConstMCParticleAssociation& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

ConstMCParticleAssociation& ConstMCParticleAssociation::operator=(const ConstMCParticleAssociation& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

ConstMCParticleAssociation::ConstMCParticleAssociation(MCParticleAssociationObj* obj) : m_obj(obj){
  if(m_obj != nullptr)
    m_obj->acquire();
}

ConstMCParticleAssociation ConstMCParticleAssociation::clone() const {
  return {new MCParticleAssociationObj(*m_obj)};
}

ConstMCParticleAssociation::~ConstMCParticleAssociation(){
  if ( m_obj != nullptr) m_obj->release();
}

  const ConstMCParticle ConstMCParticleAssociation::Mother() const { if (m_obj->m_Mother == nullptr) {
 return ConstMCParticle(nullptr);}
 return ConstMCParticle(*(m_obj->m_Mother));}
  const ConstMCParticle ConstMCParticleAssociation::Daughter() const { if (m_obj->m_Daughter == nullptr) {
 return ConstMCParticle(nullptr);}
 return ConstMCParticle(*(m_obj->m_Daughter));}


bool  ConstMCParticleAssociation::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID ConstMCParticleAssociation::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool ConstMCParticleAssociation::operator==(const MCParticleAssociation& other) const {
     return (m_obj==other.m_obj);
}

//bool operator< (const MCParticleAssociation& p1, const MCParticleAssociation& p2 ) {
//  if( p1.m_containerID == p2.m_containerID ) {
//    return p1.m_index < p2.m_index;
//  } else {
//    return p1.m_containerID < p2.m_containerID;
//  }
//}


