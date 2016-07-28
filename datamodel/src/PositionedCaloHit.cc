// datamodel specific includes
#include "PositionedCaloHit.h"
#include "PositionedCaloHitConst.h"
#include "PositionedCaloHitObj.h"
#include "PositionedCaloHitData.h"
#include "PositionedCaloHitCollection.h"
#include <iostream>


namespace fcc {

PositionedCaloHit::PositionedCaloHit() : m_obj(new PositionedCaloHitObj()){
 m_obj->acquire();
}

PositionedCaloHit::PositionedCaloHit(fcc::Point position,fcc::BareHit core) : m_obj(new PositionedCaloHitObj()) {
  m_obj->acquire();
    m_obj->data.position = position;  m_obj->data.core = core;
}


PositionedCaloHit::PositionedCaloHit(const PositionedCaloHit& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

PositionedCaloHit& PositionedCaloHit::operator=(const PositionedCaloHit& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

PositionedCaloHit::PositionedCaloHit(PositionedCaloHitObj* obj) : m_obj(obj){
  if(m_obj != nullptr)
    m_obj->acquire();
}

PositionedCaloHit PositionedCaloHit::clone() const {
  return {new PositionedCaloHitObj(*m_obj)};
}

PositionedCaloHit::~PositionedCaloHit(){
  if ( m_obj != nullptr) m_obj->release();
}

PositionedCaloHit::operator ConstPositionedCaloHit() const {return ConstPositionedCaloHit(m_obj);}

  const fcc::Point& PositionedCaloHit::position() const { return m_obj->data.position; }
const float& PositionedCaloHit::x() const { return m_obj->data.position.x; }
const float& PositionedCaloHit::y() const { return m_obj->data.position.y; }
const float& PositionedCaloHit::z() const { return m_obj->data.position.z; }
  const fcc::BareHit& PositionedCaloHit::core() const { return m_obj->data.core; }
const unsigned& PositionedCaloHit::bits() const { return m_obj->data.core.bits; }
const ulonglong& PositionedCaloHit::cellId() const { return m_obj->data.core.cellId; }
const float& PositionedCaloHit::energy() const { return m_obj->data.core.energy; }
const float& PositionedCaloHit::time() const { return m_obj->data.core.time; }

  fcc::Point& PositionedCaloHit::position() { return m_obj->data.position; }
void PositionedCaloHit::position(class fcc::Point value) { m_obj->data.position = value; }
void PositionedCaloHit::x(float value){ m_obj->data.position.x = value; }
void PositionedCaloHit::y(float value){ m_obj->data.position.y = value; }
void PositionedCaloHit::z(float value){ m_obj->data.position.z = value; }
  fcc::BareHit& PositionedCaloHit::core() { return m_obj->data.core; }
void PositionedCaloHit::core(class fcc::BareHit value) { m_obj->data.core = value; }
void PositionedCaloHit::bits(unsigned value){ m_obj->data.core.bits = value; }
void PositionedCaloHit::cellId(ulonglong value){ m_obj->data.core.cellId = value; }
void PositionedCaloHit::energy(float value){ m_obj->data.core.energy = value; }
void PositionedCaloHit::time(float value){ m_obj->data.core.time = value; }



bool  PositionedCaloHit::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID PositionedCaloHit::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool PositionedCaloHit::operator==(const ConstPositionedCaloHit& other) const {
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
