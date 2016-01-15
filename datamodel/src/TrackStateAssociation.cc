// datamodel specific includes
#include "TrackStateAssociation.h"
#include "TrackStateAssociationConst.h"
#include "TrackStateAssociationObj.h"
#include "TrackStateAssociationData.h"
#include "TrackStateAssociationCollection.h"
#include <iostream>
#include "Track.h"
#include "TrackState.h"




TrackStateAssociation::TrackStateAssociation() : m_obj(new TrackStateAssociationObj()){
 m_obj->acquire();
}



TrackStateAssociation::TrackStateAssociation(const TrackStateAssociation& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

TrackStateAssociation& TrackStateAssociation::operator=(const TrackStateAssociation& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

TrackStateAssociation::TrackStateAssociation(TrackStateAssociationObj* obj) : m_obj(obj){
  if(m_obj != nullptr)
    m_obj->acquire();
}

TrackStateAssociation TrackStateAssociation::clone() const {
  return {new TrackStateAssociationObj(*m_obj)};
}

TrackStateAssociation::~TrackStateAssociation(){
  if ( m_obj != nullptr) m_obj->release();
}

TrackStateAssociation::operator ConstTrackStateAssociation() const {return ConstTrackStateAssociation(m_obj);}

  const ConstTrack TrackStateAssociation::Track() const { if (m_obj->m_Track == nullptr) {
 return ConstTrack(nullptr);}
 return ConstTrack(*(m_obj->m_Track));}
  const ConstTrackState TrackStateAssociation::State() const { if (m_obj->m_State == nullptr) {
 return ConstTrackState(nullptr);}
 return ConstTrackState(*(m_obj->m_State));}

void TrackStateAssociation::Track(ConstTrack value) { if (m_obj->m_Track != nullptr) delete m_obj->m_Track; m_obj->m_Track = new ConstTrack(value); }
void TrackStateAssociation::State(ConstTrackState value) { if (m_obj->m_State != nullptr) delete m_obj->m_State; m_obj->m_State = new ConstTrackState(value); }


bool  TrackStateAssociation::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID TrackStateAssociation::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool TrackStateAssociation::operator==(const ConstTrackStateAssociation& other) const {
     return (m_obj==other.m_obj);
}


//bool operator< (const TrackStateAssociation& p1, const TrackStateAssociation& p2 ) {
//  if( p1.m_containerID == p2.m_containerID ) {
//    return p1.m_index < p2.m_index;
//  } else {
//    return p1.m_containerID < p2.m_containerID;
//  }
//}


