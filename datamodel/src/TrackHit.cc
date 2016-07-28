// datamodel specific includes
#include "TrackHit.h"
#include "TrackHitConst.h"
#include "TrackHitObj.h"
#include "TrackHitData.h"
#include "TrackHitCollection.h"
#include <iostream>


namespace fcc {

TrackHit::TrackHit() : m_obj(new TrackHitObj()){
 m_obj->acquire();
}

TrackHit::TrackHit(fcc::BareHit core) : m_obj(new TrackHitObj()) {
  m_obj->acquire();
    m_obj->data.core = core;
}


TrackHit::TrackHit(const TrackHit& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

TrackHit& TrackHit::operator=(const TrackHit& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

TrackHit::TrackHit(TrackHitObj* obj) : m_obj(obj){
  if(m_obj != nullptr)
    m_obj->acquire();
}

TrackHit TrackHit::clone() const {
  return {new TrackHitObj(*m_obj)};
}

TrackHit::~TrackHit(){
  if ( m_obj != nullptr) m_obj->release();
}

TrackHit::operator ConstTrackHit() const {return ConstTrackHit(m_obj);}

  const fcc::BareHit& TrackHit::core() const { return m_obj->data.core; }
const unsigned& TrackHit::bits() const { return m_obj->data.core.bits; }
const ulonglong& TrackHit::cellId() const { return m_obj->data.core.cellId; }
const float& TrackHit::energy() const { return m_obj->data.core.energy; }
const float& TrackHit::time() const { return m_obj->data.core.time; }

  fcc::BareHit& TrackHit::core() { return m_obj->data.core; }
void TrackHit::core(class fcc::BareHit value) { m_obj->data.core = value; }
void TrackHit::bits(unsigned value){ m_obj->data.core.bits = value; }
void TrackHit::cellId(ulonglong value){ m_obj->data.core.cellId = value; }
void TrackHit::energy(float value){ m_obj->data.core.energy = value; }
void TrackHit::time(float value){ m_obj->data.core.time = value; }



bool  TrackHit::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID TrackHit::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool TrackHit::operator==(const ConstTrackHit& other) const {
  return (m_obj==other.m_obj);
}


//bool operator< (const TrackHit& p1, const TrackHit& p2 ) {
//  if( p1.m_containerID == p2.m_containerID ) {
//    return p1.m_index < p2.m_index;
//  } else {
//    return p1.m_containerID < p2.m_containerID;
//  }
//}

} // namespace fcc
