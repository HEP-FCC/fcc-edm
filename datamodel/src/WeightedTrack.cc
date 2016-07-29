// datamodel specific includes
#include "WeightedTrack.h"
#include "WeightedTrackConst.h"
#include "WeightedTrackObj.h"
#include "WeightedTrackData.h"
#include "WeightedTrackCollection.h"
#include <iostream>
#include "Track.h"


namespace fcc {

WeightedTrack::WeightedTrack() : m_obj(new WeightedTrackObj()){
 m_obj->acquire();
}

WeightedTrack::WeightedTrack(float weight) : m_obj(new WeightedTrackObj()) {
  m_obj->acquire();
    m_obj->data.weight = weight;
}


WeightedTrack::WeightedTrack(const WeightedTrack& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

WeightedTrack& WeightedTrack::operator=(const WeightedTrack& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

WeightedTrack::WeightedTrack(WeightedTrackObj* obj) : m_obj(obj){
  if(m_obj != nullptr)
    m_obj->acquire();
}

WeightedTrack WeightedTrack::clone() const {
  return {new WeightedTrackObj(*m_obj)};
}

WeightedTrack::~WeightedTrack(){
  if ( m_obj != nullptr) m_obj->release();
}

WeightedTrack::operator ConstWeightedTrack() const {return ConstWeightedTrack(m_obj);}

  const float& WeightedTrack::weight() const { return m_obj->data.weight; }
  const fcc::ConstTrack WeightedTrack::track() const {
    if (m_obj->m_track == nullptr) {
      return fcc::ConstTrack(nullptr);
    }
    return fcc::ConstTrack(*(m_obj->m_track));
  }
void WeightedTrack::weight(float value){ m_obj->data.weight = value; }
void WeightedTrack::track(fcc::ConstTrack value) {
  if (m_obj->m_track != nullptr) delete m_obj->m_track;
  m_obj->m_track = new ConstTrack(value);
}



bool  WeightedTrack::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID WeightedTrack::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool WeightedTrack::operator==(const ConstWeightedTrack& other) const {
  return (m_obj==other.m_obj);
}


//bool operator< (const WeightedTrack& p1, const WeightedTrack& p2 ) {
//  if( p1.m_containerID == p2.m_containerID ) {
//    return p1.m_index < p2.m_index;
//  } else {
//    return p1.m_containerID < p2.m_containerID;
//  }
//}

} // namespace fcc
