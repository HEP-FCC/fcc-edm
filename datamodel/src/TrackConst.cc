// datamodel specific includes
#include "Track.h"
#include "TrackConst.h"
#include "TrackObj.h"
#include "TrackData.h"
#include "TrackCollection.h"
#include <iostream>


namespace fcc {

ConstTrack::ConstTrack() : m_obj(new TrackObj()) {
 m_obj->acquire();
}

ConstTrack::ConstTrack(float chi2,unsigned ndf,unsigned bits) : m_obj(new TrackObj()){
 m_obj->acquire();
   m_obj->data.chi2 = chi2;  m_obj->data.ndf = ndf;  m_obj->data.bits = bits;
}


ConstTrack::ConstTrack(const ConstTrack& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

ConstTrack& ConstTrack::operator=(const ConstTrack& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

ConstTrack::ConstTrack(TrackObj* obj) : m_obj(obj) {
  if(m_obj != nullptr)
    m_obj->acquire();
}

ConstTrack ConstTrack::clone() const {
  return {new TrackObj(*m_obj)};
}

ConstTrack::~ConstTrack(){
  if ( m_obj != nullptr) m_obj->release();
}

  /// Access the  chi2 returned by the track fit
  const float& ConstTrack::chi2() const { return m_obj->data.chi2; }
  /// Access the  Number of degrees of freedom of the track fit
  const unsigned& ConstTrack::ndf() const { return m_obj->data.ndf; }
  /// Access the  Stores flags
  const unsigned& ConstTrack::bits() const { return m_obj->data.bits; }

std::vector<fcc::ConstTrackCluster>::const_iterator ConstTrack::clusters_begin() const {
  auto ret_value = m_obj->m_clusters->begin();
  std::advance(ret_value, m_obj->data.clusters_begin);
  return ret_value;
}

std::vector<fcc::ConstTrackCluster>::const_iterator ConstTrack::clusters_end() const {
  auto ret_value = m_obj->m_clusters->begin();
  std::advance(ret_value, m_obj->data.clusters_end-1);
  return ++ret_value;
}

unsigned int ConstTrack::clusters_size() const {
  return (m_obj->data.clusters_end-m_obj->data.clusters_begin);
}

fcc::ConstTrackCluster ConstTrack::clusters(unsigned int index) const {
  if (clusters_size() > index) {
    return m_obj->m_clusters->at(m_obj->data.clusters_begin+index);
  }
  else throw std::out_of_range ("index out of bounds for existing references");
}
std::vector<fcc::ConstTrackState>::const_iterator ConstTrack::states_begin() const {
  auto ret_value = m_obj->m_states->begin();
  std::advance(ret_value, m_obj->data.states_begin);
  return ret_value;
}

std::vector<fcc::ConstTrackState>::const_iterator ConstTrack::states_end() const {
  auto ret_value = m_obj->m_states->begin();
  std::advance(ret_value, m_obj->data.states_end-1);
  return ++ret_value;
}

unsigned int ConstTrack::states_size() const {
  return (m_obj->data.states_end-m_obj->data.states_begin);
}

fcc::ConstTrackState ConstTrack::states(unsigned int index) const {
  if (states_size() > index) {
    return m_obj->m_states->at(m_obj->data.states_begin+index);
  }
  else throw std::out_of_range ("index out of bounds for existing references");
}


bool  ConstTrack::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID ConstTrack::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool ConstTrack::operator==(const Track& other) const {
     return (m_obj==other.m_obj);
}

//bool operator< (const Track& p1, const Track& p2 ) {
//  if( p1.m_containerID == p2.m_containerID ) {
//    return p1.m_index < p2.m_index;
//  } else {
//    return p1.m_containerID < p2.m_containerID;
//  }
//}

} // namespace fcc
