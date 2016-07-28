// datamodel specific includes
#include "PositionedTrackHit.h"
#include "PositionedTrackHitConst.h"
#include "PositionedTrackHitObj.h"
#include "PositionedTrackHitData.h"
#include "PositionedTrackHitCollection.h"
#include <iostream>


namespace fcc {

PositionedTrackHit::PositionedTrackHit() : m_obj(new PositionedTrackHitObj()){
 m_obj->acquire();
}

PositionedTrackHit::PositionedTrackHit(fcc::Point position,fcc::BareHit core) : m_obj(new PositionedTrackHitObj()) {
  m_obj->acquire();
    m_obj->data.position = position;  m_obj->data.core = core;
}


PositionedTrackHit::PositionedTrackHit(const PositionedTrackHit& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

PositionedTrackHit& PositionedTrackHit::operator=(const PositionedTrackHit& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

PositionedTrackHit::PositionedTrackHit(PositionedTrackHitObj* obj) : m_obj(obj){
  if(m_obj != nullptr)
    m_obj->acquire();
}

PositionedTrackHit PositionedTrackHit::clone() const {
  return {new PositionedTrackHitObj(*m_obj)};
}

PositionedTrackHit::~PositionedTrackHit(){
  if ( m_obj != nullptr) m_obj->release();
}

PositionedTrackHit::operator ConstPositionedTrackHit() const {return ConstPositionedTrackHit(m_obj);}

  const fcc::Point& PositionedTrackHit::position() const { return m_obj->data.position; }
const float& PositionedTrackHit::x() const { return m_obj->data.position.x; }
const float& PositionedTrackHit::y() const { return m_obj->data.position.y; }
const float& PositionedTrackHit::z() const { return m_obj->data.position.z; }
  const fcc::BareHit& PositionedTrackHit::core() const { return m_obj->data.core; }
const unsigned& PositionedTrackHit::bits() const { return m_obj->data.core.bits; }
const ulonglong& PositionedTrackHit::cellId() const { return m_obj->data.core.cellId; }
const float& PositionedTrackHit::energy() const { return m_obj->data.core.energy; }
const float& PositionedTrackHit::time() const { return m_obj->data.core.time; }

  fcc::Point& PositionedTrackHit::position() { return m_obj->data.position; }
void PositionedTrackHit::position(class fcc::Point value) { m_obj->data.position = value; }
void PositionedTrackHit::x(float value){ m_obj->data.position.x = value; }
void PositionedTrackHit::y(float value){ m_obj->data.position.y = value; }
void PositionedTrackHit::z(float value){ m_obj->data.position.z = value; }
  fcc::BareHit& PositionedTrackHit::core() { return m_obj->data.core; }
void PositionedTrackHit::core(class fcc::BareHit value) { m_obj->data.core = value; }
void PositionedTrackHit::bits(unsigned value){ m_obj->data.core.bits = value; }
void PositionedTrackHit::cellId(ulonglong value){ m_obj->data.core.cellId = value; }
void PositionedTrackHit::energy(float value){ m_obj->data.core.energy = value; }
void PositionedTrackHit::time(float value){ m_obj->data.core.time = value; }



bool  PositionedTrackHit::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID PositionedTrackHit::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool PositionedTrackHit::operator==(const ConstPositionedTrackHit& other) const {
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
