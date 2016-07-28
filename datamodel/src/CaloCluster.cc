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

CaloCluster::CaloCluster(fcc::BareCluster core) : m_obj(new CaloClusterObj()) {
  m_obj->acquire();
    m_obj->data.core = core;
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

  const fcc::BareCluster& CaloCluster::core() const { return m_obj->data.core; }
const unsigned& CaloCluster::bits() const { return m_obj->data.core.bits; }
const float& CaloCluster::energy() const { return m_obj->data.core.energy; }
const ::fcc::Point& CaloCluster::position() const { return m_obj->data.core.position; }
const float& CaloCluster::time() const { return m_obj->data.core.time; }

  fcc::BareCluster& CaloCluster::core() { return m_obj->data.core; }
void CaloCluster::core(class fcc::BareCluster value) { m_obj->data.core = value; }
void CaloCluster::bits(unsigned value){ m_obj->data.core.bits = value; }
void CaloCluster::energy(float value){ m_obj->data.core.energy = value; }
::fcc::Point& CaloCluster::position() { return m_obj->data.core.position; }
void CaloCluster::position(class ::fcc::Point value) { m_obj->data.core.position = value; }
void CaloCluster::time(float value){ m_obj->data.core.time = value; }

std::vector<fcc::ConstCaloHit>::const_iterator CaloCluster::hits_begin() const {
  auto ret_value = m_obj->m_hits->begin();
  std::advance(ret_value, m_obj->data.hits_begin);
  return ret_value;
}

std::vector<fcc::ConstCaloHit>::const_iterator CaloCluster::hits_end() const {
  auto ret_value = m_obj->m_hits->begin();
//fg: this code fails if m_obj->data.hits==0
//  std::advance(ret_value, m_obj->data.hits_end-1);
//  return ++ret_value;
  std::advance(ret_value, m_obj->data.hits_end);
  return ret_value;
}

void CaloCluster::addhits(fcc::ConstCaloHit component) {
  m_obj->m_hits->push_back(component);
  m_obj->data.hits_end++;
}

unsigned int CaloCluster::hits_size() const {
  return (m_obj->data.hits_end-m_obj->data.hits_begin);
}

fcc::ConstCaloHit CaloCluster::hits(unsigned int index) const {
  if (hits_size() > index) {
    return m_obj->m_hits->at(m_obj->data.hits_begin+index);
  }
  else throw std::out_of_range ("index out of bounds for existing references");
}


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
