// datamodel specific includes
#include "CaloCluster.h"
#include "CaloClusterConst.h"
#include "CaloClusterObj.h"
#include "CaloClusterData.h"
#include "CaloClusterCollection.h"
#include <iostream>


namespace fcc {

CaloCluster::CaloCluster() : m_obj(new CaloClusterObj()){
 m_obj->acquire();
}

CaloCluster::CaloCluster(fcc::BareCluster Core) : m_obj(new CaloClusterObj()){
 m_obj->acquire();
   m_obj->data.Core = Core;
}


CaloCluster::CaloCluster(const CaloCluster& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

CaloCluster& CaloCluster::operator=(const CaloCluster& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

CaloCluster::CaloCluster(CaloClusterObj* obj) : m_obj(obj){
  if(m_obj != nullptr)
    m_obj->acquire();
}

CaloCluster CaloCluster::clone() const {
  return {new CaloClusterObj(*m_obj)};
}

CaloCluster::~CaloCluster(){
  if ( m_obj != nullptr) m_obj->release();
}

CaloCluster::operator ConstCaloCluster() const {return ConstCaloCluster(m_obj);}

  const fcc::BareCluster& CaloCluster::Core() const { return m_obj->data.Core; }

  fcc::BareCluster& CaloCluster::Core() { return m_obj->data.Core; }
void CaloCluster::Core(class fcc::BareCluster value){ m_obj->data.Core = value;}


bool  CaloCluster::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID CaloCluster::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool CaloCluster::operator==(const ConstCaloCluster& other) const {
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
