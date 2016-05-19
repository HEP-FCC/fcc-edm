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

TrackHit::TrackHit(fcc::BareHit Core) : m_obj(new TrackHitObj()) {
  m_obj->acquire();
    m_obj->data.Core = Core;
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

  const fcc::BareHit& TrackHit::Core() const { return m_obj->data.Core; }

  fcc::BareHit& TrackHit::Core() { return m_obj->data.Core; }
void TrackHit::Core(class fcc::BareHit value) { m_obj->data.Core = value; }



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
