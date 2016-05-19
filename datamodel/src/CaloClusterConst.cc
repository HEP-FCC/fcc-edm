// datamodel specific includes
#include "CaloCluster.h"
#include "CaloClusterConst.h"
#include "CaloClusterObj.h"
#include "CaloClusterData.h"
#include "CaloClusterCollection.h"
#include <iostream>


namespace fcc {

ConstCaloCluster::ConstCaloCluster() : m_obj(new CaloClusterObj()) {
 m_obj->acquire();
}

ConstCaloCluster::ConstCaloCluster(fcc::BareCluster Core) : m_obj(new CaloClusterObj()){
 m_obj->acquire();
   m_obj->data.Core = Core;
}


ConstCaloCluster::ConstCaloCluster(const ConstCaloCluster& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

ConstCaloCluster& ConstCaloCluster::operator=(const ConstCaloCluster& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

ConstCaloCluster::ConstCaloCluster(CaloClusterObj* obj) : m_obj(obj) {
  if(m_obj != nullptr)
    m_obj->acquire();
}

ConstCaloCluster ConstCaloCluster::clone() const {
  return {new CaloClusterObj(*m_obj)};
}

ConstCaloCluster::~ConstCaloCluster(){
  if ( m_obj != nullptr) m_obj->release();
}

  const fcc::BareCluster& ConstCaloCluster::Core() const { return m_obj->data.Core; }



bool  ConstCaloCluster::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID ConstCaloCluster::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool ConstCaloCluster::operator==(const CaloCluster& other) const {
     return (m_obj==other.m_obj);
}

//bool operator< (const CaloCluster& p1, const CaloCluster& p2 ) {
//  if( p1.m_containerID == p2.m_containerID ) {
//    return p1.m_index < p2.m_index;
//  } else {
//    return p1.m_containerID < p2.m_containerID;
//  }
//}

} // namespace fcc
