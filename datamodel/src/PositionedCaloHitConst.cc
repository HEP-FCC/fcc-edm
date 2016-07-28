// datamodel specific includes
#include "PositionedCaloHit.h"
#include "PositionedCaloHitConst.h"
#include "PositionedCaloHitObj.h"
#include "PositionedCaloHitData.h"
#include "PositionedCaloHitCollection.h"
#include <iostream>


namespace fcc {

ConstPositionedCaloHit::ConstPositionedCaloHit() : m_obj(new PositionedCaloHitObj()) {
 m_obj->acquire();
}

ConstPositionedCaloHit::ConstPositionedCaloHit(fcc::Point position,fcc::BareHit core) : m_obj(new PositionedCaloHitObj()){
 m_obj->acquire();
   m_obj->data.position = position;  m_obj->data.core = core;
}


ConstPositionedCaloHit::ConstPositionedCaloHit(const ConstPositionedCaloHit& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

ConstPositionedCaloHit& ConstPositionedCaloHit::operator=(const ConstPositionedCaloHit& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

ConstPositionedCaloHit::ConstPositionedCaloHit(PositionedCaloHitObj* obj) : m_obj(obj) {
  if(m_obj != nullptr)
    m_obj->acquire();
}

ConstPositionedCaloHit ConstPositionedCaloHit::clone() const {
  return {new PositionedCaloHitObj(*m_obj)};
}

ConstPositionedCaloHit::~ConstPositionedCaloHit(){
  if ( m_obj != nullptr) m_obj->release();
}

  const float& ConstPositionedCaloHit::x() const { return m_obj->data.position.x; }
  const float& ConstPositionedCaloHit::y() const { return m_obj->data.position.y; }
  const float& ConstPositionedCaloHit::z() const { return m_obj->data.position.z; }
  /// Access the  The global position
  const fcc::Point& ConstPositionedCaloHit::position() const { return m_obj->data.position; }
  const unsigned& ConstPositionedCaloHit::bits() const { return m_obj->data.core.bits; }
  const ulonglong& ConstPositionedCaloHit::cellId() const { return m_obj->data.core.cellId; }
  const float& ConstPositionedCaloHit::energy() const { return m_obj->data.core.energy; }
  const float& ConstPositionedCaloHit::time() const { return m_obj->data.core.time; }
  /// Access the  The hit
  const fcc::BareHit& ConstPositionedCaloHit::core() const { return m_obj->data.core; }



bool  ConstPositionedCaloHit::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID ConstPositionedCaloHit::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool ConstPositionedCaloHit::operator==(const PositionedCaloHit& other) const {
     return (m_obj==other.m_obj);
}

//bool operator< (const PositionedCaloHit& p1, const PositionedCaloHit& p2 ) {
//  if( p1.m_containerID == p2.m_containerID ) {
//    return p1.m_index < p2.m_index;
//  } else {
//    return p1.m_containerID < p2.m_containerID;
//  }
//}

} // namespace fcc
