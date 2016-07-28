// datamodel specific includes
#include "PositionedTrackHit.h"
#include "PositionedTrackHitConst.h"
#include "PositionedTrackHitObj.h"
#include "PositionedTrackHitData.h"
#include "PositionedTrackHitCollection.h"
#include <iostream>


namespace fcc {

ConstPositionedTrackHit::ConstPositionedTrackHit() : m_obj(new PositionedTrackHitObj()) {
 m_obj->acquire();
}

ConstPositionedTrackHit::ConstPositionedTrackHit(fcc::Point position,fcc::BareHit core) : m_obj(new PositionedTrackHitObj()){
 m_obj->acquire();
   m_obj->data.position = position;  m_obj->data.core = core;
}


ConstPositionedTrackHit::ConstPositionedTrackHit(const ConstPositionedTrackHit& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

ConstPositionedTrackHit& ConstPositionedTrackHit::operator=(const ConstPositionedTrackHit& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

ConstPositionedTrackHit::ConstPositionedTrackHit(PositionedTrackHitObj* obj) : m_obj(obj) {
  if(m_obj != nullptr)
    m_obj->acquire();
}

ConstPositionedTrackHit ConstPositionedTrackHit::clone() const {
  return {new PositionedTrackHitObj(*m_obj)};
}

ConstPositionedTrackHit::~ConstPositionedTrackHit(){
  if ( m_obj != nullptr) m_obj->release();
}

  const float& ConstPositionedTrackHit::x() const { return m_obj->data.position.x; }
  const float& ConstPositionedTrackHit::y() const { return m_obj->data.position.y; }
  const float& ConstPositionedTrackHit::z() const { return m_obj->data.position.z; }
  /// Access the  The global position
  const fcc::Point& ConstPositionedTrackHit::position() const { return m_obj->data.position; }
  const unsigned& ConstPositionedTrackHit::bits() const { return m_obj->data.core.bits; }
  const ulonglong& ConstPositionedTrackHit::cellId() const { return m_obj->data.core.cellId; }
  const float& ConstPositionedTrackHit::energy() const { return m_obj->data.core.energy; }
  const float& ConstPositionedTrackHit::time() const { return m_obj->data.core.time; }
  /// Access the  The hit
  const fcc::BareHit& ConstPositionedTrackHit::core() const { return m_obj->data.core; }



bool  ConstPositionedTrackHit::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID ConstPositionedTrackHit::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool ConstPositionedTrackHit::operator==(const PositionedTrackHit& other) const {
     return (m_obj==other.m_obj);
}

//bool operator< (const PositionedTrackHit& p1, const PositionedTrackHit& p2 ) {
//  if( p1.m_containerID == p2.m_containerID ) {
//    return p1.m_index < p2.m_index;
//  } else {
//    return p1.m_containerID < p2.m_containerID;
//  }
//}

} // namespace fcc
