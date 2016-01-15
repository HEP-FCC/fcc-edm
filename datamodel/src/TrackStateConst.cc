// datamodel specific includes
#include "TrackState.h"
#include "TrackStateConst.h"
#include "TrackStateObj.h"
#include "TrackStateData.h"
#include "TrackStateCollection.h"
#include <iostream>




ConstTrackState::ConstTrackState() : m_obj(new TrackStateObj()){
 m_obj->acquire();
}

ConstTrackState::ConstTrackState(float Location,float Omega,float D0,float Z0) : m_obj(new TrackStateObj()){
 m_obj->acquire();
   m_obj->data.Location = Location;  m_obj->data.Omega = Omega;  m_obj->data.D0 = D0;  m_obj->data.Z0 = Z0;
}


ConstTrackState::ConstTrackState(const ConstTrackState& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

ConstTrackState& ConstTrackState::operator=(const ConstTrackState& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

ConstTrackState::ConstTrackState(TrackStateObj* obj) : m_obj(obj){
  if(m_obj != nullptr)
    m_obj->acquire();
}

ConstTrackState ConstTrackState::clone() const {
  return {new TrackStateObj(*m_obj)};
}

ConstTrackState::~ConstTrackState(){
  if ( m_obj != nullptr) m_obj->release();
}

  const float& ConstTrackState::Location() const { return m_obj->data.Location; }
  const float& ConstTrackState::Omega() const { return m_obj->data.Omega; }
  const float& ConstTrackState::D0() const { return m_obj->data.D0; }
  const float& ConstTrackState::Z0() const { return m_obj->data.Z0; }


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


