// datamodel specific includes
#include "TrackState.h"
#include "TrackStateConst.h"
#include "TrackStateObj.h"
#include "TrackStateData.h"
#include "TrackStateCollection.h"
#include <iostream>


namespace fcc {

TrackState::TrackState() : m_obj(new TrackStateObj()){
 m_obj->acquire();
}

TrackState::TrackState(float location,float omega,float d0,float z0) : m_obj(new TrackStateObj()) {
  m_obj->acquire();
    m_obj->data.location = location;  m_obj->data.omega = omega;  m_obj->data.d0 = d0;  m_obj->data.z0 = z0;
}


TrackState::TrackState(const TrackState& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

TrackState& TrackState::operator=(const TrackState& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

TrackState::TrackState(TrackStateObj* obj) : m_obj(obj){
  if(m_obj != nullptr)
    m_obj->acquire();
}

TrackState TrackState::clone() const {
  return {new TrackStateObj(*m_obj)};
}

TrackState::~TrackState(){
  if ( m_obj != nullptr) m_obj->release();
}

TrackState::operator ConstTrackState() const {return ConstTrackState(m_obj);}

  const float& TrackState::location() const { return m_obj->data.location; }
  const float& TrackState::omega() const { return m_obj->data.omega; }
  const float& TrackState::d0() const { return m_obj->data.d0; }
  const float& TrackState::z0() const { return m_obj->data.z0; }

void TrackState::location(float value){ m_obj->data.location = value; }
void TrackState::omega(float value){ m_obj->data.omega = value; }
void TrackState::d0(float value){ m_obj->data.d0 = value; }
void TrackState::z0(float value){ m_obj->data.z0 = value; }



bool  TrackState::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID TrackState::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool TrackState::operator==(const ConstTrackState& other) const {
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
