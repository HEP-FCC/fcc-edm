// datamodel specific includes
#include "TrackClusterAssociation.h"
#include "TrackClusterAssociationConst.h"
#include "TrackClusterAssociationObj.h"
#include "TrackClusterAssociationData.h"
#include "TrackClusterAssociationCollection.h"
#include <iostream>
#include "Track.h"
#include "TrackCluster.h"


namespace fcc {

ConstTrackClusterAssociation::ConstTrackClusterAssociation() : m_obj(new TrackClusterAssociationObj()) {
 m_obj->acquire();
}



ConstTrackClusterAssociation::ConstTrackClusterAssociation(const ConstTrackClusterAssociation& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

ConstTrackClusterAssociation& ConstTrackClusterAssociation::operator=(const ConstTrackClusterAssociation& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

ConstTrackClusterAssociation::ConstTrackClusterAssociation(TrackClusterAssociationObj* obj) : m_obj(obj) {
  if(m_obj != nullptr)
    m_obj->acquire();
}

ConstTrackClusterAssociation ConstTrackClusterAssociation::clone() const {
  return {new TrackClusterAssociationObj(*m_obj)};
}

ConstTrackClusterAssociation::~ConstTrackClusterAssociation(){
  if ( m_obj != nullptr) m_obj->release();
}

  const fcc::ConstTrack ConstTrackClusterAssociation::Track() const {
    if (m_obj->m_Track == nullptr) {
      return fcc::ConstTrack(nullptr);
    }
    return fcc::ConstTrack(*(m_obj->m_Track));} const fcc::ConstTrackCluster ConstTrackClusterAssociation::Cluster() const {
    if (m_obj->m_Cluster == nullptr) {
      return fcc::ConstTrackCluster(nullptr);
    }
    return fcc::ConstTrackCluster(*(m_obj->m_Cluster));}


bool  ConstTrackClusterAssociation::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID ConstTrackClusterAssociation::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool ConstTrackClusterAssociation::operator==(const TrackClusterAssociation& other) const {
     return (m_obj==other.m_obj);
}

//bool operator< (const TrackClusterAssociation& p1, const TrackClusterAssociation& p2 ) {
//  if( p1.m_containerID == p2.m_containerID ) {
//    return p1.m_index < p2.m_index;
//  } else {
//    return p1.m_containerID < p2.m_containerID;
//  }
//}

} // namespace fcc
