// datamodel specific includes
#include "SimCaloHit.h"
#include "SimCaloHitConst.h"
#include "SimCaloHitObj.h"
#include "SimCaloHitData.h"
#include "SimCaloHitCollection.h"
#include <iostream>


namespace fcc {

ConstSimCaloHit::ConstSimCaloHit() : m_obj(new SimCaloHitObj()) {
 m_obj->acquire();
}

ConstSimCaloHit::ConstSimCaloHit(fcc::BareHit Core) : m_obj(new SimCaloHitObj()){
 m_obj->acquire();
   m_obj->data.Core = Core;
}


ConstSimCaloHit::ConstSimCaloHit(const ConstSimCaloHit& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

ConstSimCaloHit& ConstSimCaloHit::operator=(const ConstSimCaloHit& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

ConstSimCaloHit::ConstSimCaloHit(SimCaloHitObj* obj) : m_obj(obj) {
  if(m_obj != nullptr)
    m_obj->acquire();
}

ConstSimCaloHit ConstSimCaloHit::clone() const {
  return {new SimCaloHitObj(*m_obj)};
}

ConstSimCaloHit::~ConstSimCaloHit(){
  if ( m_obj != nullptr) m_obj->release();
}

  const fcc::BareHit& ConstSimCaloHit::Core() const { return m_obj->data.Core; }



bool  ConstSimCaloHit::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID ConstSimCaloHit::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool ConstSimCaloHit::operator==(const SimCaloHit& other) const {
     return (m_obj==other.m_obj);
}

//bool operator< (const SimCaloHit& p1, const SimCaloHit& p2 ) {
//  if( p1.m_containerID == p2.m_containerID ) {
//    return p1.m_index < p2.m_index;
//  } else {
//    return p1.m_containerID < p2.m_containerID;
//  }
//}

} // namespace fcc
