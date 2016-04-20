// datamodel specific includes
#include "TrackClusterHitsAssociation.h"
#include "TrackClusterHitsAssociationConst.h"
#include "TrackClusterHitsAssociationObj.h"
#include "TrackClusterHitsAssociationData.h"
#include "TrackClusterHitsAssociationCollection.h"
#include <iostream>
#include "TrackCluster.h"
#include "TrackHit.h"


namespace fcc {

ConstTrackClusterHitsAssociation::ConstTrackClusterHitsAssociation() : m_obj(new TrackClusterHitsAssociationObj()) {
 m_obj->acquire();
}



ConstTrackClusterHitsAssociation::ConstTrackClusterHitsAssociation(const ConstTrackClusterHitsAssociation& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

ConstTrackClusterHitsAssociation& ConstTrackClusterHitsAssociation::operator=(const ConstTrackClusterHitsAssociation& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

ConstTrackClusterHitsAssociation::ConstTrackClusterHitsAssociation(TrackClusterHitsAssociationObj* obj) : m_obj(obj) {
  if(m_obj != nullptr)
    m_obj->acquire();
}

ConstTrackClusterHitsAssociation ConstTrackClusterHitsAssociation::clone() const {
  return {new TrackClusterHitsAssociationObj(*m_obj)};
}

ConstTrackClusterHitsAssociation::~ConstTrackClusterHitsAssociation(){
  if ( m_obj != nullptr) m_obj->release();
}

  const fcc::ConstTrackCluster ConstTrackClusterHitsAssociation::Cluster() const {
    if (m_obj->m_Cluster == nullptr) {
      return fcc::ConstTrackCluster(nullptr);
    }
    return fcc::ConstTrackCluster(*(m_obj->m_Cluster));}  const fcc::ConstTrackHit ConstTrackClusterHitsAssociation::Hit() const {
    if (m_obj->m_Hit == nullptr) {
      return fcc::ConstTrackHit(nullptr);
    }
    return fcc::ConstTrackHit(*(m_obj->m_Hit));}


bool  ConstTrackClusterHitsAssociation::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID ConstTrackClusterHitsAssociation::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool ConstTrackClusterHitsAssociation::operator==(const TrackClusterHitsAssociation& other) const {
     return (m_obj==other.m_obj);
}

//bool operator< (const TrackClusterHitsAssociation& p1, const TrackClusterHitsAssociation& p2 ) {
//  if( p1.m_containerID == p2.m_containerID ) {
//    return p1.m_index < p2.m_index;
//  } else {
//    return p1.m_containerID < p2.m_containerID;
//  }
//}

} // namespace fcc
