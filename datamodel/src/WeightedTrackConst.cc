// datamodel specific includes
#include "WeightedTrack.h"
#include "WeightedTrackConst.h"
#include "WeightedTrackObj.h"
#include "WeightedTrackData.h"
#include "WeightedTrackCollection.h"
#include <iostream>
#include "Track.h"


namespace fcc {

ConstWeightedTrack::ConstWeightedTrack() : m_obj(new WeightedTrackObj()) {
 m_obj->acquire();
}

ConstWeightedTrack::ConstWeightedTrack(float weight) : m_obj(new WeightedTrackObj()){
 m_obj->acquire();
   m_obj->data.weight = weight;
}


ConstWeightedTrack::ConstWeightedTrack(const ConstWeightedTrack& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

ConstWeightedTrack& ConstWeightedTrack::operator=(const ConstWeightedTrack& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

ConstWeightedTrack::ConstWeightedTrack(WeightedTrackObj* obj) : m_obj(obj) {
  if(m_obj != nullptr)
    m_obj->acquire();
}

ConstWeightedTrack ConstWeightedTrack::clone() const {
  return {new WeightedTrackObj(*m_obj)};
}

ConstWeightedTrack::~ConstWeightedTrack(){
  if ( m_obj != nullptr) m_obj->release();
}

  /// Access the  Weight of the track in the vertex
  const float& ConstWeightedTrack::weight() const { return m_obj->data.weight; }
  /// Access the  The track.
  const fcc::ConstTrack ConstWeightedTrack::track() const {
    if (m_obj->m_track == nullptr) {
      return fcc::ConstTrack(nullptr);
    }
    return fcc::ConstTrack(*(m_obj->m_track));}


bool  ConstWeightedTrack::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID ConstWeightedTrack::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool ConstWeightedTrack::operator==(const WeightedTrack& other) const {
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
