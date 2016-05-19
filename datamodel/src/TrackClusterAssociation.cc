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

TrackClusterAssociation::TrackClusterAssociation() : m_obj(new TrackClusterAssociationObj()){
 m_obj->acquire();
}



TrackClusterAssociation::TrackClusterAssociation(const TrackClusterAssociation& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

TrackClusterAssociation& TrackClusterAssociation::operator=(const TrackClusterAssociation& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

TrackClusterAssociation::TrackClusterAssociation(TrackClusterAssociationObj* obj) : m_obj(obj){
  if(m_obj != nullptr)
    m_obj->acquire();
}

TrackClusterAssociation TrackClusterAssociation::clone() const {
  return {new TrackClusterAssociationObj(*m_obj)};
}

TrackClusterAssociation::~TrackClusterAssociation(){
  if ( m_obj != nullptr) m_obj->release();
}

TrackClusterAssociation::operator ConstTrackClusterAssociation() const {return ConstTrackClusterAssociation(m_obj);}

  const fcc::ConstTrack TrackClusterAssociation::Track() const {
    if (m_obj->m_Track == nullptr) {
      return fcc::ConstTrack(nullptr);
    }
    return fcc::ConstTrack(*(m_obj->m_Track));
  } const fcc::ConstTrackCluster TrackClusterAssociation::Cluster() const {
    if (m_obj->m_Cluster == nullptr) {
      return fcc::ConstTrackCluster(nullptr);
    }
    return fcc::ConstTrackCluster(*(m_obj->m_Cluster));
  }
void TrackClusterAssociation::Track(fcc::ConstTrack value) {
  if (m_obj->m_Track != nullptr) delete m_obj->m_Track;
  m_obj->m_Track = new ConstTrack(value);
}
void TrackClusterAssociation::Cluster(fcc::ConstTrackCluster value) {
  if (m_obj->m_Cluster != nullptr) delete m_obj->m_Cluster;
  m_obj->m_Cluster = new ConstTrackCluster(value);
}



bool  TrackClusterAssociation::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID TrackClusterAssociation::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool TrackClusterAssociation::operator==(const ConstTrackClusterAssociation& other) const {
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
