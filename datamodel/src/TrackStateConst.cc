// datamodel specific includes
#include "TrackState.h"
#include "TrackStateConst.h"
#include "TrackStateObj.h"
#include "TrackStateData.h"
#include "TrackStateCollection.h"
#include <iostream>


namespace fcc {

ConstTrackState::ConstTrackState() : m_obj(new TrackStateObj()) {
 m_obj->acquire();
}

ConstTrackState::ConstTrackState(float location,float omega,float d0,float z0) : m_obj(new TrackStateObj()){
 m_obj->acquire();
   m_obj->data.location = location;  m_obj->data.omega = omega;  m_obj->data.d0 = d0;  m_obj->data.z0 = z0;
}


ConstTrackState::ConstTrackState(const ConstTrackState& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

ConstTrackState& ConstTrackState::operator=(const ConstTrackState& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

ConstTrackState::ConstTrackState(TrackStateObj* obj) : m_obj(obj) {
  if(m_obj != nullptr)
    m_obj->acquire();
}

ConstTrackState ConstTrackState::clone() const {
  return {new TrackStateObj(*m_obj)};
}

ConstTrackState::~ConstTrackState(){
  if ( m_obj != nullptr) m_obj->release();
}

  /// Access the  Location on the track. (Radius?)
  const float& ConstTrackState::location() const { return m_obj->data.location; }
  /// Access the  Track curvature in cm.
  const float& ConstTrackState::omega() const { return m_obj->data.omega; }
  /// Access the  Transverse impact parameter
  const float& ConstTrackState::d0() const { return m_obj->data.d0; }
  /// Access the  Longitudinal impact parameter
  const float& ConstTrackState::z0() const { return m_obj->data.z0; }



bool  ConstTrackState::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID ConstTrackState::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool ConstTrackState::operator==(const TrackState& other) const {
     return (m_obj==other.m_obj);
}

//bool operator< (const TrackState& p1, const TrackState& p2 ) {
//  if( p1.m_containerID == p2.m_containerID ) {
//    return p1.m_index < p2.m_index;
//  } else {
//    return p1.m_containerID < p2.m_containerID;
//  }
//}

} // namespace fcc
