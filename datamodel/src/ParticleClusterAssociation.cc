// datamodel specific includes
#include "ParticleClusterAssociation.h"
#include "ParticleClusterAssociationConst.h"
#include "ParticleClusterAssociationObj.h"
#include "ParticleClusterAssociationData.h"
#include "ParticleClusterAssociationCollection.h"
#include <iostream>
#include "Particle.h"
#include "CaloCluster.h"




ParticleClusterAssociation::ParticleClusterAssociation() : m_obj(new ParticleClusterAssociationObj()){
 m_obj->acquire();
}



ParticleClusterAssociation::ParticleClusterAssociation(const ParticleClusterAssociation& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

ParticleClusterAssociation& ParticleClusterAssociation::operator=(const ParticleClusterAssociation& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

ParticleClusterAssociation::ParticleClusterAssociation(ParticleClusterAssociationObj* obj) : m_obj(obj){
  if(m_obj != nullptr)
    m_obj->acquire();
}

ParticleClusterAssociation ParticleClusterAssociation::clone() const {
  return {new ParticleClusterAssociationObj(*m_obj)};
}

ParticleClusterAssociation::~ParticleClusterAssociation(){
  if ( m_obj != nullptr) m_obj->release();
}

ParticleClusterAssociation::operator ConstParticleClusterAssociation() const {return ConstParticleClusterAssociation(m_obj);}

  const ConstParticle ParticleClusterAssociation::Particle() const { if (m_obj->m_Particle == nullptr) {
 return ConstParticle(nullptr);}
 return ConstParticle(*(m_obj->m_Particle));}
  const ConstCaloCluster ParticleClusterAssociation::Cluster() const { if (m_obj->m_Cluster == nullptr) {
 return ConstCaloCluster(nullptr);}
 return ConstCaloCluster(*(m_obj->m_Cluster));}

void ParticleClusterAssociation::Particle(ConstParticle value) { if (m_obj->m_Particle != nullptr) delete m_obj->m_Particle; m_obj->m_Particle = new ConstParticle(value); }
void ParticleClusterAssociation::Cluster(ConstCaloCluster value) { if (m_obj->m_Cluster != nullptr) delete m_obj->m_Cluster; m_obj->m_Cluster = new ConstCaloCluster(value); }


bool  ParticleClusterAssociation::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID ParticleClusterAssociation::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool ParticleClusterAssociation::operator==(const ConstParticleClusterAssociation& other) const {
     return (m_obj==other.m_obj);
}


//bool operator< (const ParticleClusterAssociation& p1, const ParticleClusterAssociation& p2 ) {
//  if( p1.m_containerID == p2.m_containerID ) {
//    return p1.m_index < p2.m_index;
//  } else {
//    return p1.m_containerID < p2.m_containerID;
//  }
//}


