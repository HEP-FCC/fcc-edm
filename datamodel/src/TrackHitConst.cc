// datamodel specific includes
#include "TrackHit.h"
#include "TrackHitConst.h"
#include "TrackHitObj.h"
#include "TrackHitData.h"
#include "TrackHitCollection.h"
#include <iostream>


namespace fcc {

ConstTrackHit::ConstTrackHit() : m_obj(new TrackHitObj()) {
 m_obj->acquire();
}

ConstTrackHit::ConstTrackHit(fcc::BareHit core) : m_obj(new TrackHitObj()){
 m_obj->acquire();
   m_obj->data.core = core;
}


ConstTrackHit::ConstTrackHit(const ConstTrackHit& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

ConstTrackHit& ConstTrackHit::operator=(const ConstTrackHit& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

ConstTrackHit::ConstTrackHit(TrackHitObj* obj) : m_obj(obj) {
  if(m_obj != nullptr)
    m_obj->acquire();
}

ConstTrackHit ConstTrackHit::clone() const {
  return {new TrackHitObj(*m_obj)};
}

ConstTrackHit::~ConstTrackHit(){
  if ( m_obj != nullptr) m_obj->release();
}

  const unsigned& ConstTrackHit::bits() const { return m_obj->data.core.bits; }
  const unsigned long long& ConstTrackHit::cellId() const { return m_obj->data.core.cellId; }
  const float& ConstTrackHit::energy() const { return m_obj->data.core.energy; }
  const float& ConstTrackHit::time() const { return m_obj->data.core.time; }
  /// Access the  contains basic hit information
  const fcc::BareHit& ConstTrackHit::core() const { return m_obj->data.core; }



bool  ConstTrackHit::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID ConstTrackHit::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool ConstTrackHit::operator==(const TrackHit& other) const {
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
