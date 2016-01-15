// datamodel specific includes
#include "CaloHit.h"
#include "CaloHitConst.h"
#include "CaloHitObj.h"
#include "CaloHitData.h"
#include "CaloHitCollection.h"
#include <iostream>




CaloHit::CaloHit() : m_obj(new CaloHitObj()){
 m_obj->acquire();
}

CaloHit::CaloHit(BareHit Core) : m_obj(new CaloHitObj()){
 m_obj->acquire();
   m_obj->data.Core = Core;
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

  const BareHit& CaloHit::Core() const { return m_obj->data.Core; }

  BareHit& CaloHit::Core() { return m_obj->data.Core; }
void CaloHit::Core(class BareHit value){ m_obj->data.Core = value;}


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


