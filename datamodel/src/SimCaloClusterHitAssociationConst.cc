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

ConstSimCaloClusterHitAssociation::ConstSimCaloClusterHitAssociation() : m_obj(new SimCaloClusterHitAssociationObj()) {
 m_obj->acquire();
}



ConstSimCaloClusterHitAssociation::ConstSimCaloClusterHitAssociation(const ConstSimCaloClusterHitAssociation& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

ConstSimCaloClusterHitAssociation& ConstSimCaloClusterHitAssociation::operator=(const ConstSimCaloClusterHitAssociation& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

ConstSimCaloClusterHitAssociation::ConstSimCaloClusterHitAssociation(SimCaloClusterHitAssociationObj* obj) : m_obj(obj) {
  if(m_obj != nullptr)
    m_obj->acquire();
}

ConstSimCaloClusterHitAssociation ConstSimCaloClusterHitAssociation::clone() const {
  return {new SimCaloClusterHitAssociationObj(*m_obj)};
}

ConstSimCaloClusterHitAssociation::~ConstSimCaloClusterHitAssociation(){
  if ( m_obj != nullptr) m_obj->release();
}

  const fcc::ConstSimCaloCluster ConstSimCaloClusterHitAssociation::Cluster() const {
    if (m_obj->m_Cluster == nullptr) {
      return fcc::ConstSimCaloCluster(nullptr);
    }
    return fcc::ConstSimCaloCluster(*(m_obj->m_Cluster));}  const fcc::ConstSimCaloHit ConstSimCaloClusterHitAssociation::Hit() const {
    if (m_obj->m_Hit == nullptr) {
      return fcc::ConstSimCaloHit(nullptr);
    }
    return fcc::ConstSimCaloHit(*(m_obj->m_Hit));}


bool  ConstSimCaloClusterHitAssociation::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID ConstSimCaloClusterHitAssociation::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool ConstSimCaloClusterHitAssociation::operator==(const SimCaloClusterHitAssociation& other) const {
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
