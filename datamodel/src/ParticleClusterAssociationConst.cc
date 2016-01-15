// datamodel specific includes
#include "ParticleClusterAssociation.h"
#include "ParticleClusterAssociationConst.h"
#include "ParticleClusterAssociationObj.h"
#include "ParticleClusterAssociationData.h"
#include "ParticleClusterAssociationCollection.h"
#include <iostream>
#include "Particle.h"
#include "CaloCluster.h"




ConstParticleClusterAssociation::ConstParticleClusterAssociation() : m_obj(new ParticleClusterAssociationObj()){
 m_obj->acquire();
}



ConstParticleClusterAssociation::ConstParticleClusterAssociation(const ConstParticleClusterAssociation& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

ConstParticleClusterAssociation& ConstParticleClusterAssociation::operator=(const ConstParticleClusterAssociation& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

ConstParticleClusterAssociation::ConstParticleClusterAssociation(ParticleClusterAssociationObj* obj) : m_obj(obj){
  if(m_obj != nullptr)
    m_obj->acquire();
}

ConstParticleClusterAssociation ConstParticleClusterAssociation::clone() const {
  return {new ParticleClusterAssociationObj(*m_obj)};
}

ConstParticleClusterAssociation::~ConstParticleClusterAssociation(){
  if ( m_obj != nullptr) m_obj->release();
}

  const ConstParticle ConstParticleClusterAssociation::Particle() const { if (m_obj->m_Particle == nullptr) {
 return ConstParticle(nullptr);}
 return ConstParticle(*(m_obj->m_Particle));}
  const ConstCaloCluster ConstParticleClusterAssociation::Cluster() const { if (m_obj->m_Cluster == nullptr) {
 return ConstCaloCluster(nullptr);}
 return ConstCaloCluster(*(m_obj->m_Cluster));}


bool  ConstParticleClusterAssociation::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID ConstParticleClusterAssociation::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool ConstParticleClusterAssociation::operator==(const ParticleClusterAssociation& other) const {
     return (m_obj==other.m_obj);
}

//bool operator< (const ParticleClusterAssociation& p1, const ParticleClusterAssociation& p2 ) {
//  if( p1.m_containerID == p2.m_containerID ) {
//    return p1.m_index < p2.m_index;
//  } else {
//    return p1.m_containerID < p2.m_containerID;
//  }
//}


