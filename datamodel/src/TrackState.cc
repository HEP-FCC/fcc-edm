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

TrackState::TrackState(float Location,float Omega,float D0,float Z0) : m_obj(new TrackStateObj()){
 m_obj->acquire();
   m_obj->data.Location = Location;  m_obj->data.Omega = Omega;  m_obj->data.D0 = D0;  m_obj->data.Z0 = Z0;
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

  const float& TrackState::Location() const { return m_obj->data.Location; }
  const float& TrackState::Omega() const { return m_obj->data.Omega; }
  const float& TrackState::D0() const { return m_obj->data.D0; }
  const float& TrackState::Z0() const { return m_obj->data.Z0; }

void TrackState::Location(float value){ m_obj->data.Location = value;}
void TrackState::Omega(float value){ m_obj->data.Omega = value;}
void TrackState::D0(float value){ m_obj->data.D0 = value;}
void TrackState::Z0(float value){ m_obj->data.Z0 = value;}


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
