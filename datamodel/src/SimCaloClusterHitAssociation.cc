// datamodel specific includes
#include "SimCaloClusterHitAssociation.h"
#include "SimCaloClusterHitAssociationConst.h"
#include "SimCaloClusterHitAssociationObj.h"
#include "SimCaloClusterHitAssociationData.h"
#include "SimCaloClusterHitAssociationCollection.h"
#include <iostream>
#include "SimCaloCluster.h"
#include "SimCaloHit.h"


namespace fcc {

SimCaloClusterHitAssociation::SimCaloClusterHitAssociation() : m_obj(new SimCaloClusterHitAssociationObj()){
 m_obj->acquire();
}



SimCaloClusterHitAssociation::SimCaloClusterHitAssociation(const SimCaloClusterHitAssociation& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

SimCaloClusterHitAssociation& SimCaloClusterHitAssociation::operator=(const SimCaloClusterHitAssociation& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

SimCaloClusterHitAssociation::SimCaloClusterHitAssociation(SimCaloClusterHitAssociationObj* obj) : m_obj(obj){
  if(m_obj != nullptr)
    m_obj->acquire();
}

SimCaloClusterHitAssociation SimCaloClusterHitAssociation::clone() const {
  return {new SimCaloClusterHitAssociationObj(*m_obj)};
}

SimCaloClusterHitAssociation::~SimCaloClusterHitAssociation(){
  if ( m_obj != nullptr) m_obj->release();
}

SimCaloClusterHitAssociation::operator ConstSimCaloClusterHitAssociation() const {return ConstSimCaloClusterHitAssociation(m_obj);}

  const fcc::ConstSimCaloCluster SimCaloClusterHitAssociation::Cluster() const {
    if (m_obj->m_Cluster == nullptr) {
      return fcc::ConstSimCaloCluster(nullptr);
    }
    return fcc::ConstSimCaloCluster(*(m_obj->m_Cluster));
  } const fcc::ConstSimCaloHit SimCaloClusterHitAssociation::Hit() const {
    if (m_obj->m_Hit == nullptr) {
      return fcc::ConstSimCaloHit(nullptr);
    }
    return fcc::ConstSimCaloHit(*(m_obj->m_Hit));
  }
void SimCaloClusterHitAssociation::Cluster(fcc::ConstSimCaloCluster value) {
  if (m_obj->m_Cluster != nullptr) delete m_obj->m_Cluster;
  m_obj->m_Cluster = new ConstSimCaloCluster(value);
}
void SimCaloClusterHitAssociation::Hit(fcc::ConstSimCaloHit value) {
  if (m_obj->m_Hit != nullptr) delete m_obj->m_Hit;
  m_obj->m_Hit = new ConstSimCaloHit(value);
}



bool  SimCaloClusterHitAssociation::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID SimCaloClusterHitAssociation::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool SimCaloClusterHitAssociation::operator==(const ConstSimCaloClusterHitAssociation& other) const {
  return (m_obj==other.m_obj);
}


//bool operator< (const SimCaloClusterHitAssociation& p1, const SimCaloClusterHitAssociation& p2 ) {
//  if( p1.m_containerID == p2.m_containerID ) {
//    return p1.m_index < p2.m_index;
//  } else {
//    return p1.m_containerID < p2.m_containerID;
//  }
//}

} // namespace fcc
