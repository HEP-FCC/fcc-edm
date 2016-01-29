// datamodel specific includes
#include "SimCaloCluster.h"
#include "SimCaloClusterConst.h"
#include "SimCaloClusterObj.h"
#include "SimCaloClusterData.h"
#include "SimCaloClusterCollection.h"
#include <iostream>


namespace fcc {

SimCaloCluster::SimCaloCluster() : m_obj(new SimCaloClusterObj()){
 m_obj->acquire();
}

SimCaloCluster::SimCaloCluster(fcc::BareCluster Core) : m_obj(new SimCaloClusterObj()){
 m_obj->acquire();
   m_obj->data.Core = Core;
}


SimCaloCluster::SimCaloCluster(const SimCaloCluster& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

SimCaloCluster& SimCaloCluster::operator=(const SimCaloCluster& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

SimCaloCluster::SimCaloCluster(SimCaloClusterObj* obj) : m_obj(obj){
  if(m_obj != nullptr)
    m_obj->acquire();
}

SimCaloCluster SimCaloCluster::clone() const {
  return {new SimCaloClusterObj(*m_obj)};
}

SimCaloCluster::~SimCaloCluster(){
  if ( m_obj != nullptr) m_obj->release();
}

SimCaloCluster::operator ConstSimCaloCluster() const {return ConstSimCaloCluster(m_obj);}

  const fcc::BareCluster& SimCaloCluster::Core() const { return m_obj->data.Core; }

  fcc::BareCluster& SimCaloCluster::Core() { return m_obj->data.Core; }
void SimCaloCluster::Core(class fcc::BareCluster value){ m_obj->data.Core = value;}


bool  SimCaloCluster::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID SimCaloCluster::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool SimCaloCluster::operator==(const ConstSimCaloCluster& other) const {
     return (m_obj==other.m_obj);
}


//bool operator< (const SimCaloCluster& p1, const SimCaloCluster& p2 ) {
//  if( p1.m_containerID == p2.m_containerID ) {
//    return p1.m_index < p2.m_index;
//  } else {
//    return p1.m_containerID < p2.m_containerID;
//  }
//}

} // namespace fcc
