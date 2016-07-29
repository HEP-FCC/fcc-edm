// datamodel specific includes
#include "CaloHit.h"
#include "CaloHitConst.h"
#include "CaloHitObj.h"
#include "CaloHitData.h"
#include "CaloHitCollection.h"
#include <iostream>


namespace fcc {

CaloHit::CaloHit() : m_obj(new CaloHitObj()){
 m_obj->acquire();
}

CaloHit::CaloHit(fcc::BareHit core) : m_obj(new CaloHitObj()) {
  m_obj->acquire();
    m_obj->data.core = core;
}


CaloHit::CaloHit(const CaloHit& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

CaloHit& CaloHit::operator=(const CaloHit& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

CaloHit::CaloHit(CaloHitObj* obj) : m_obj(obj){
  if(m_obj != nullptr)
    m_obj->acquire();
}

CaloHit CaloHit::clone() const {
  return {new CaloHitObj(*m_obj)};
}

CaloHit::~CaloHit(){
  if ( m_obj != nullptr) m_obj->release();
}

CaloHit::operator ConstCaloHit() const {return ConstCaloHit(m_obj);}

  const fcc::BareHit& CaloHit::core() const { return m_obj->data.core; }
const unsigned& CaloHit::bits() const { return m_obj->data.core.bits; }
const unsigned long long& CaloHit::cellId() const { return m_obj->data.core.cellId; }
const float& CaloHit::energy() const { return m_obj->data.core.energy; }
const float& CaloHit::time() const { return m_obj->data.core.time; }

  fcc::BareHit& CaloHit::core() { return m_obj->data.core; }
void CaloHit::core(class fcc::BareHit value) { m_obj->data.core = value; }
void CaloHit::bits(unsigned value){ m_obj->data.core.bits = value; }
void CaloHit::cellId(unsigned long long value){ m_obj->data.core.cellId = value; }
void CaloHit::energy(float value){ m_obj->data.core.energy = value; }
void CaloHit::time(float value){ m_obj->data.core.time = value; }



bool  CaloHit::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID CaloHit::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool CaloHit::operator==(const ConstCaloHit& other) const {
  return (m_obj==other.m_obj);
}


//bool operator< (const CaloHit& p1, const CaloHit& p2 ) {
//  if( p1.m_containerID == p2.m_containerID ) {
//    return p1.m_index < p2.m_index;
//  } else {
//    return p1.m_containerID < p2.m_containerID;
//  }
//}

} // namespace fcc
