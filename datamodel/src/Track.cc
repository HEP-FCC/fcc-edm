// datamodel specific includes
#include "Track.h"
#include "TrackConst.h"
#include "TrackObj.h"
#include "TrackData.h"
#include "TrackCollection.h"
#include <iostream>


namespace fcc {

Track::Track() : m_obj(new TrackObj()){
 m_obj->acquire();
}

Track::Track(float chi2,unsigned ndf,unsigned bits) : m_obj(new TrackObj()) {
  m_obj->acquire();
    m_obj->data.chi2 = chi2;  m_obj->data.ndf = ndf;  m_obj->data.bits = bits;
}


Track::Track(const Track& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

Track& Track::operator=(const Track& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

Track::Track(TrackObj* obj) : m_obj(obj){
  if(m_obj != nullptr)
    m_obj->acquire();
}

Track Track::clone() const {
  return {new TrackObj(*m_obj)};
}

Track::~Track(){
  if ( m_obj != nullptr) m_obj->release();
}

Track::operator ConstTrack() const {return ConstTrack(m_obj);}

  const float& Track::chi2() const { return m_obj->data.chi2; }
  const unsigned& Track::ndf() const { return m_obj->data.ndf; }
  const unsigned& Track::bits() const { return m_obj->data.bits; }

void Track::chi2(float value){ m_obj->data.chi2 = value; }
void Track::ndf(unsigned value){ m_obj->data.ndf = value; }
void Track::bits(unsigned value){ m_obj->data.bits = value; }

std::vector<fcc::ConstTrackCluster>::const_iterator Track::clusters_begin() const {
  auto ret_value = m_obj->m_clusters->begin();
  std::advance(ret_value, m_obj->data.clusters_begin);
  return ret_value;
}

std::vector<fcc::ConstTrackCluster>::const_iterator Track::clusters_end() const {
  auto ret_value = m_obj->m_clusters->begin();
//fg: this code fails if m_obj->data.clusters==0
//  std::advance(ret_value, m_obj->data.clusters_end-1);
//  return ++ret_value;
  std::advance(ret_value, m_obj->data.clusters_end);
  return ret_value;
}

void Track::addclusters(fcc::ConstTrackCluster component) {
  m_obj->m_clusters->push_back(component);
  m_obj->data.clusters_end++;
}

unsigned int Track::clusters_size() const {
  return (m_obj->data.clusters_end-m_obj->data.clusters_begin);
}

fcc::ConstTrackCluster Track::clusters(unsigned int index) const {
  if (clusters_size() > index) {
    return m_obj->m_clusters->at(m_obj->data.clusters_begin+index);
  }
  else throw std::out_of_range ("index out of bounds for existing references");
}
std::vector<fcc::ConstTrackState>::const_iterator Track::states_begin() const {
  auto ret_value = m_obj->m_states->begin();
  std::advance(ret_value, m_obj->data.states_begin);
  return ret_value;
}

std::vector<fcc::ConstTrackState>::const_iterator Track::states_end() const {
  auto ret_value = m_obj->m_states->begin();
//fg: this code fails if m_obj->data.states==0
//  std::advance(ret_value, m_obj->data.states_end-1);
//  return ++ret_value;
  std::advance(ret_value, m_obj->data.states_end);
  return ret_value;
}

void Track::addstates(fcc::ConstTrackState component) {
  m_obj->m_states->push_back(component);
  m_obj->data.states_end++;
}

unsigned int Track::states_size() const {
  return (m_obj->data.states_end-m_obj->data.states_begin);
}

fcc::ConstTrackState Track::states(unsigned int index) const {
  if (states_size() > index) {
    return m_obj->m_states->at(m_obj->data.states_begin+index);
  }
  else throw std::out_of_range ("index out of bounds for existing references");
}


bool  Track::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID Track::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool Track::operator==(const ConstTrack& other) const {
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
