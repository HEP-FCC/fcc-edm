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

ConstTrackCluster::ConstTrackCluster(fcc::BareCluster core) : m_obj(new TrackClusterObj()){
 m_obj->acquire();
   m_obj->data.core = core;
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

  const unsigned& ConstTrackCluster::bits() const { return m_obj->data.core.bits; }
  const float& ConstTrackCluster::energy() const { return m_obj->data.core.energy; }
  const ::fcc::Point& ConstTrackCluster::position() const { return m_obj->data.core.position; }
  const float& ConstTrackCluster::time() const { return m_obj->data.core.time; }
  /// Access the  contains basic cluster information
  const fcc::BareCluster& ConstTrackCluster::core() const { return m_obj->data.core; }

std::vector<fcc::ConstTrackHit>::const_iterator ConstTrackCluster::hits_begin() const {
  auto ret_value = m_obj->m_hits->begin();
  std::advance(ret_value, m_obj->data.hits_begin);
  return ret_value;
}

std::vector<fcc::ConstTrackHit>::const_iterator ConstTrackCluster::hits_end() const {
  auto ret_value = m_obj->m_hits->begin();
  std::advance(ret_value, m_obj->data.hits_end-1);
  return ++ret_value;
}

unsigned int ConstTrackCluster::hits_size() const {
  return (m_obj->data.hits_end-m_obj->data.hits_begin);
}

fcc::ConstTrackHit ConstTrackCluster::hits(unsigned int index) const {
  if (hits_size() > index) {
    return m_obj->m_hits->at(m_obj->data.hits_begin+index);
  }
  else throw std::out_of_range ("index out of bounds for existing references");
}


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
