// datamodel specific includes
#include "TrackStateAssociation.h"
#include "TrackStateAssociationConst.h"
#include "TrackStateAssociationObj.h"
#include "TrackStateAssociationData.h"
#include "TrackStateAssociationCollection.h"
#include <iostream>
#include "Track.h"
#include "TrackState.h"


namespace fcc {

ConstTrackStateAssociation::ConstTrackStateAssociation() : m_obj(new TrackStateAssociationObj()){
 m_obj->acquire();
}



ConstTrackStateAssociation::ConstTrackStateAssociation(const ConstTrackStateAssociation& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

ConstTrackStateAssociation& ConstTrackStateAssociation::operator=(const ConstTrackStateAssociation& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

ConstTrackStateAssociation::ConstTrackStateAssociation(TrackStateAssociationObj* obj) : m_obj(obj){
  if(m_obj != nullptr)
    m_obj->acquire();
}

ConstTrackStateAssociation ConstTrackStateAssociation::clone() const {
  return {new TrackStateAssociationObj(*m_obj)};
}

ConstTrackStateAssociation::~ConstTrackStateAssociation(){
  if ( m_obj != nullptr) m_obj->release();
}

  const fcc::ConstTrack ConstTrackStateAssociation::Track() const { if (m_obj->m_Track == nullptr) {
 return fcc::ConstTrack(nullptr);}
 return fcc::ConstTrack(*(m_obj->m_Track));}
  const fcc::ConstTrackState ConstTrackStateAssociation::State() const { if (m_obj->m_State == nullptr) {
 return fcc::ConstTrackState(nullptr);}
 return fcc::ConstTrackState(*(m_obj->m_State));}


bool  ConstTrackStateAssociation::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID ConstTrackStateAssociation::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool ConstTrackStateAssociation::operator==(const TrackStateAssociation& other) const {
     return (m_obj==other.m_obj);
}

//bool operator< (const TrackStateAssociation& p1, const TrackStateAssociation& p2 ) {
//  if( p1.m_containerID == p2.m_containerID ) {
//    return p1.m_index < p2.m_index;
//  } else {
//    return p1.m_containerID < p2.m_containerID;
//  }
//}

} // namespace fcc
