// datamodel specific includes
#include "TrackClusterHitsAssociation.h"
#include "TrackClusterHitsAssociationConst.h"
#include "TrackClusterHitsAssociationObj.h"
#include "TrackClusterHitsAssociationData.h"
#include "TrackClusterHitsAssociationCollection.h"
#include <iostream>
#include "TrackCluster.h"
#include "TrackHit.h"




TrackClusterHitsAssociation::TrackClusterHitsAssociation() : m_obj(new TrackClusterHitsAssociationObj()){
 m_obj->acquire();
}



TrackClusterHitsAssociation::TrackClusterHitsAssociation(const TrackClusterHitsAssociation& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

TrackClusterHitsAssociation& TrackClusterHitsAssociation::operator=(const TrackClusterHitsAssociation& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

TrackClusterHitsAssociation::TrackClusterHitsAssociation(TrackClusterHitsAssociationObj* obj) : m_obj(obj){
  if(m_obj != nullptr)
    m_obj->acquire();
}

TrackClusterHitsAssociation TrackClusterHitsAssociation::clone() const {
  return {new TrackClusterHitsAssociationObj(*m_obj)};
}

TrackClusterHitsAssociation::~TrackClusterHitsAssociation(){
  if ( m_obj != nullptr) m_obj->release();
}

TrackClusterHitsAssociation::operator ConstTrackClusterHitsAssociation() const {return ConstTrackClusterHitsAssociation(m_obj);}

  const ConstTrackCluster TrackClusterHitsAssociation::Cluster() const { if (m_obj->m_Cluster == nullptr) {
 return ConstTrackCluster(nullptr);}
 return ConstTrackCluster(*(m_obj->m_Cluster));}
  const ConstTrackHit TrackClusterHitsAssociation::Hit() const { if (m_obj->m_Hit == nullptr) {
 return ConstTrackHit(nullptr);}
 return ConstTrackHit(*(m_obj->m_Hit));}

void TrackClusterHitsAssociation::Cluster(ConstTrackCluster value) { if (m_obj->m_Cluster != nullptr) delete m_obj->m_Cluster; m_obj->m_Cluster = new ConstTrackCluster(value); }
void TrackClusterHitsAssociation::Hit(ConstTrackHit value) { if (m_obj->m_Hit != nullptr) delete m_obj->m_Hit; m_obj->m_Hit = new ConstTrackHit(value); }


bool  TrackClusterHitsAssociation::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID TrackClusterHitsAssociation::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool TrackClusterHitsAssociation::operator==(const ConstTrackClusterHitsAssociation& other) const {
     return (m_obj==other.m_obj);
}


//bool operator< (const TrackClusterHitsAssociation& p1, const TrackClusterHitsAssociation& p2 ) {
//  if( p1.m_containerID == p2.m_containerID ) {
//    return p1.m_index < p2.m_index;
//  } else {
//    return p1.m_containerID < p2.m_containerID;
//  }
//}


