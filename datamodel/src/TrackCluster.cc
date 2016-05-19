// datamodel specific includes
#include "TrackCluster.h"
#include "TrackClusterConst.h"
#include "TrackClusterObj.h"
#include "TrackClusterData.h"
#include "TrackClusterCollection.h"
#include <iostream>


namespace fcc {

TrackCluster::TrackCluster() : m_obj(new TrackClusterObj()){
 m_obj->acquire();
}

TrackCluster::TrackCluster(fcc::BareCluster Core) : m_obj(new TrackClusterObj()) {
  m_obj->acquire();
    m_obj->data.Core = Core;
}


TrackCluster::TrackCluster(const TrackCluster& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

TrackCluster& TrackCluster::operator=(const TrackCluster& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

TrackCluster::TrackCluster(TrackClusterObj* obj) : m_obj(obj){
  if(m_obj != nullptr)
    m_obj->acquire();
}

TrackCluster TrackCluster::clone() const {
  return {new TrackClusterObj(*m_obj)};
}

TrackCluster::~TrackCluster(){
  if ( m_obj != nullptr) m_obj->release();
}

TrackCluster::operator ConstTrackCluster() const {return ConstTrackCluster(m_obj);}

  const fcc::BareCluster& TrackCluster::Core() const { return m_obj->data.Core; }

  fcc::BareCluster& TrackCluster::Core() { return m_obj->data.Core; }
void TrackCluster::Core(class fcc::BareCluster value) { m_obj->data.Core = value; }



bool  TrackCluster::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID TrackCluster::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool TrackCluster::operator==(const ConstTrackCluster& other) const {
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
