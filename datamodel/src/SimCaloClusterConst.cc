// datamodel specific includes
#include "SimCaloCluster.h"
#include "SimCaloClusterConst.h"
#include "SimCaloClusterObj.h"
#include "SimCaloClusterData.h"
#include "SimCaloClusterCollection.h"
#include <iostream>




ConstSimCaloCluster::ConstSimCaloCluster() : m_obj(new SimCaloClusterObj()){
 m_obj->acquire();
}

ConstSimCaloCluster::ConstSimCaloCluster(BareCluster Core) : m_obj(new SimCaloClusterObj()){
 m_obj->acquire();
   m_obj->data.Core = Core;
}


ConstSimCaloCluster::ConstSimCaloCluster(const ConstSimCaloCluster& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

ConstSimCaloCluster& ConstSimCaloCluster::operator=(const ConstSimCaloCluster& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

ConstSimCaloCluster::ConstSimCaloCluster(SimCaloClusterObj* obj) : m_obj(obj){
  if(m_obj != nullptr)
    m_obj->acquire();
}

ConstSimCaloCluster ConstSimCaloCluster::clone() const {
  return {new SimCaloClusterObj(*m_obj)};
}

ConstSimCaloCluster::~ConstSimCaloCluster(){
  if ( m_obj != nullptr) m_obj->release();
}

  const BareCluster& ConstSimCaloCluster::Core() const { return m_obj->data.Core; }


bool  ConstSimCaloCluster::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID ConstSimCaloCluster::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool ConstSimCaloCluster::operator==(const SimCaloCluster& other) const {
     return (m_obj==other.m_obj);
}

//bool operator< (const SimCaloCluster& p1, const SimCaloCluster& p2 ) {
//  if( p1.m_containerID == p2.m_containerID ) {
//    return p1.m_index < p2.m_index;
//  } else {
//    return p1.m_containerID < p2.m_containerID;
//  }
//}


