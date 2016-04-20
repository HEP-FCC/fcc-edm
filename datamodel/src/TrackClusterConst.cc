// datamodel specific includes
#include "TrackCluster.h"
#include "TrackClusterConst.h"
#include "TrackClusterObj.h"
#include "TrackClusterData.h"
#include "TrackClusterCollection.h"
#include <iostream>


namespace fcc {

ConstTrackCluster::ConstTrackCluster() : m_obj(new TrackClusterObj()) {
 m_obj->acquire();
}

ConstTrackCluster::ConstTrackCluster(fcc::BareCluster Core) : m_obj(new TrackClusterObj()){
 m_obj->acquire();
   m_obj->data.Core = Core;
}


ConstTrackCluster::ConstTrackCluster(const ConstTrackCluster& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

ConstTrackCluster& ConstTrackCluster::operator=(const ConstTrackCluster& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

ConstTrackCluster::ConstTrackCluster(TrackClusterObj* obj) : m_obj(obj) {
  if(m_obj != nullptr)
    m_obj->acquire();
}

ConstTrackCluster ConstTrackCluster::clone() const {
  return {new TrackClusterObj(*m_obj)};
}

ConstTrackCluster::~ConstTrackCluster(){
  if ( m_obj != nullptr) m_obj->release();
}

  const fcc::BareCluster& ConstTrackCluster::Core() const { return m_obj->data.Core; }



bool  ConstTrackCluster::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID ConstTrackCluster::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool ConstTrackCluster::operator==(const TrackCluster& other) const {
     return (m_obj==other.m_obj);
}

//bool operator< (const TrackCluster& p1, const TrackCluster& p2 ) {
//  if( p1.m_containerID == p2.m_containerID ) {
//    return p1.m_index < p2.m_index;
//  } else {
//    return p1.m_containerID < p2.m_containerID;
//  }
//}

} // namespace fcc
