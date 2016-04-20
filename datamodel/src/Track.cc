// datamodel specific includes
#include "Track.h"
#include "TrackConst.h"
#include "TrackObj.h"
#include "TrackData.h"
#include "TrackCollection.h"
#include <iostream>


namespace fcc {

Track::Track() : m_obj(new TrackObj()){
 m_obj->acquire();
}

Track::Track(float Chi2,unsigned Ndf,unsigned Bits) : m_obj(new TrackObj()) {
  m_obj->acquire();
    m_obj->data.Chi2 = Chi2;  m_obj->data.Ndf = Ndf;  m_obj->data.Bits = Bits;
}


Track::Track(const Track& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

Track& Track::operator=(const Track& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

Track::Track(TrackObj* obj) : m_obj(obj){
  if(m_obj != nullptr)
    m_obj->acquire();
}

Track Track::clone() const {
  return {new TrackObj(*m_obj)};
}

Track::~Track(){
  if ( m_obj != nullptr) m_obj->release();
}

Track::operator ConstTrack() const {return ConstTrack(m_obj);}

  const float& Track::Chi2() const { return m_obj->data.Chi2; }
  const unsigned& Track::Ndf() const { return m_obj->data.Ndf; }
  const unsigned& Track::Bits() const { return m_obj->data.Bits; }

void Track::Chi2(float value){ m_obj->data.Chi2 = value; }
void Track::Ndf(unsigned value){ m_obj->data.Ndf = value; }
void Track::Bits(unsigned value){ m_obj->data.Bits = value; }



bool  Track::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID Track::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool Track::operator==(const ConstTrack& other) const {
  return (m_obj==other.m_obj);
}


//bool operator< (const Track& p1, const Track& p2 ) {
//  if( p1.m_containerID == p2.m_containerID ) {
//    return p1.m_index < p2.m_index;
//  } else {
//    return p1.m_containerID < p2.m_containerID;
//  }
//}

} // namespace fcc
