// datamodel specific includes
#include "CaloHit.h"
#include "CaloHitConst.h"
#include "CaloHitObj.h"
#include "CaloHitData.h"
#include "CaloHitCollection.h"
#include <iostream>


namespace fcc {

ConstCaloHit::ConstCaloHit() : m_obj(new CaloHitObj()){
 m_obj->acquire();
}

ConstCaloHit::ConstCaloHit(fcc::BareHit Core) : m_obj(new CaloHitObj()){
 m_obj->acquire();
   m_obj->data.Core = Core;
}


ConstCaloHit::ConstCaloHit(const ConstCaloHit& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

ConstCaloHit& ConstCaloHit::operator=(const ConstCaloHit& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

ConstCaloHit::ConstCaloHit(CaloHitObj* obj) : m_obj(obj){
  if(m_obj != nullptr)
    m_obj->acquire();
}

ConstCaloHit ConstCaloHit::clone() const {
  return {new CaloHitObj(*m_obj)};
}

ConstCaloHit::~ConstCaloHit(){
  if ( m_obj != nullptr) m_obj->release();
}

  const fcc::BareHit& ConstCaloHit::Core() const { return m_obj->data.Core; }


bool  ConstCaloHit::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID ConstCaloHit::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool ConstCaloHit::operator==(const CaloHit& other) const {
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
