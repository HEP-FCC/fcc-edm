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

TrackCluster::TrackCluster(fcc::BareCluster core) : m_obj(new TrackClusterObj()) {
  m_obj->acquire();
    m_obj->data.core = core;
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

  const fcc::BareCluster& TrackCluster::core() const { return m_obj->data.core; }
const unsigned& TrackCluster::bits() const { return m_obj->data.core.bits; }
const float& TrackCluster::energy() const { return m_obj->data.core.energy; }
const ::fcc::Point& TrackCluster::position() const { return m_obj->data.core.position; }
const float& TrackCluster::time() const { return m_obj->data.core.time; }

  fcc::BareCluster& TrackCluster::core() { return m_obj->data.core; }
void TrackCluster::core(class fcc::BareCluster value) { m_obj->data.core = value; }
void TrackCluster::bits(unsigned value){ m_obj->data.core.bits = value; }
void TrackCluster::energy(float value){ m_obj->data.core.energy = value; }
::fcc::Point& TrackCluster::position() { return m_obj->data.core.position; }
void TrackCluster::position(class ::fcc::Point value) { m_obj->data.core.position = value; }
void TrackCluster::time(float value){ m_obj->data.core.time = value; }

std::vector<fcc::ConstTrackHit>::const_iterator TrackCluster::hits_begin() const {
  auto ret_value = m_obj->m_hits->begin();
  std::advance(ret_value, m_obj->data.hits_begin);
  return ret_value;
}

std::vector<fcc::ConstTrackHit>::const_iterator TrackCluster::hits_end() const {
  auto ret_value = m_obj->m_hits->begin();
//fg: this code fails if m_obj->data.hits==0
//  std::advance(ret_value, m_obj->data.hits_end-1);
//  return ++ret_value;
  std::advance(ret_value, m_obj->data.hits_end);
  return ret_value;
}

void TrackCluster::addhits(fcc::ConstTrackHit component) {
  m_obj->m_hits->push_back(component);
  m_obj->data.hits_end++;
}

unsigned int TrackCluster::hits_size() const {
  return (m_obj->data.hits_end-m_obj->data.hits_begin);
}

fcc::ConstTrackHit TrackCluster::hits(unsigned int index) const {
  if (hits_size() > index) {
    return m_obj->m_hits->at(m_obj->data.hits_begin+index);
  }
  else throw std::out_of_range ("index out of bounds for existing references");
}


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
