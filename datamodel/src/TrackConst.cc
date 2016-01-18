// datamodel specific includes
#include "Track.h"
#include "TrackConst.h"
#include "TrackObj.h"
#include "TrackData.h"
#include "TrackCollection.h"
#include <iostream>




ConstTrack::ConstTrack() : m_obj(new TrackObj()){
 m_obj->acquire();
}

ConstTrack::ConstTrack(float Chi2,unsigned Ndf,unsigned Bits) : m_obj(new TrackObj()){
 m_obj->acquire();
   m_obj->data.Chi2 = Chi2;  m_obj->data.Ndf = Ndf;  m_obj->data.Bits = Bits;
}


ConstTrack::ConstTrack(const ConstTrack& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

ConstTrack& ConstTrack::operator=(const ConstTrack& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

ConstTrack::ConstTrack(TrackObj* obj) : m_obj(obj){
  if(m_obj != nullptr)
    m_obj->acquire();
}

ConstTrack ConstTrack::clone() const {
  return {new TrackObj(*m_obj)};
}

ConstTrack::~ConstTrack(){
  if ( m_obj != nullptr) m_obj->release();
}

  const float& ConstTrack::Chi2() const { return m_obj->data.Chi2; }
  const unsigned& ConstTrack::Ndf() const { return m_obj->data.Ndf; }
  const unsigned& ConstTrack::Bits() const { return m_obj->data.Bits; }


bool  ConstTrack::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID ConstTrack::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool ConstTrack::operator==(const Track& other) const {
     return (m_obj==other.m_obj);
}

//bool operator< (const Track& p1, const Track& p2 ) {
//  if( p1.m_containerID == p2.m_containerID ) {
//    return p1.m_index < p2.m_index;
//  } else {
//    return p1.m_containerID < p2.m_containerID;
//  }
//}


