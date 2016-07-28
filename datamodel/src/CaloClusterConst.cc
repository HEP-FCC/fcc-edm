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

ConstCaloCluster::ConstCaloCluster(fcc::BareCluster core) : m_obj(new CaloClusterObj()){
 m_obj->acquire();
   m_obj->data.core = core;
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

  const unsigned& ConstCaloCluster::bits() const { return m_obj->data.core.bits; }
  const float& ConstCaloCluster::energy() const { return m_obj->data.core.energy; }
  const ::fcc::Point& ConstCaloCluster::position() const { return m_obj->data.core.position; }
  const float& ConstCaloCluster::time() const { return m_obj->data.core.time; }
  /// Access the  contains basic cluster information
  const fcc::BareCluster& ConstCaloCluster::core() const { return m_obj->data.core; }

std::vector<fcc::ConstCaloHit>::const_iterator ConstCaloCluster::hits_begin() const {
  auto ret_value = m_obj->m_hits->begin();
  std::advance(ret_value, m_obj->data.hits_begin);
  return ret_value;
}

std::vector<fcc::ConstCaloHit>::const_iterator ConstCaloCluster::hits_end() const {
  auto ret_value = m_obj->m_hits->begin();
  std::advance(ret_value, m_obj->data.hits_end-1);
  return ++ret_value;
}

unsigned int ConstCaloCluster::hits_size() const {
  return (m_obj->data.hits_end-m_obj->data.hits_begin);
}

fcc::ConstCaloHit ConstCaloCluster::hits(unsigned int index) const {
  if (hits_size() > index) {
    return m_obj->m_hits->at(m_obj->data.hits_begin+index);
  }
  else throw std::out_of_range ("index out of bounds for existing references");
}


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
