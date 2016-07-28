// datamodel specific includes
#include "Particle.h"
#include "ParticleConst.h"
#include "ParticleObj.h"
#include "ParticleData.h"
#include "ParticleCollection.h"
#include <iostream>


namespace fcc {

ConstParticle::ConstParticle() : m_obj(new ParticleObj()) {
 m_obj->acquire();
}

ConstParticle::ConstParticle(fcc::BareParticle Core) : m_obj(new ParticleObj()){
 m_obj->acquire();
   m_obj->data.Core = Core;
}


ConstParticle::ConstParticle(const ConstParticle& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

ConstParticle& ConstParticle::operator=(const ConstParticle& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

ConstParticle::ConstParticle(ParticleObj* obj) : m_obj(obj) {
  if(m_obj != nullptr)
    m_obj->acquire();
}

ConstParticle ConstParticle::clone() const {
  return {new ParticleObj(*m_obj)};
}

ConstParticle::~ConstParticle(){
  if ( m_obj != nullptr) m_obj->release();
}

  const unsigned& ConstParticle::bits() const { return m_obj->data.Core.bits; }
  const int& ConstParticle::charge() const { return m_obj->data.Core.charge; }
  const ::fcc::LorentzVector& ConstParticle::p4() const { return m_obj->data.Core.p4; }
  const unsigned& ConstParticle::status() const { return m_obj->data.Core.status; }
  const int& ConstParticle::type() const { return m_obj->data.Core.type; }
  const ::fcc::Point& ConstParticle::vertex() const { return m_obj->data.Core.vertex; }
  /// Access the  Contains basic particle information.
  const fcc::BareParticle& ConstParticle::Core() const { return m_obj->data.Core; }

std::vector<fcc::ConstTrack>::const_iterator ConstParticle::tracks_begin() const {
  auto ret_value = m_obj->m_tracks->begin();
  std::advance(ret_value, m_obj->data.tracks_begin);
  return ret_value;
}

std::vector<fcc::ConstTrack>::const_iterator ConstParticle::tracks_end() const {
  auto ret_value = m_obj->m_tracks->begin();
  std::advance(ret_value, m_obj->data.tracks_end-1);
  return ++ret_value;
}

unsigned int ConstParticle::tracks_size() const {
  return (m_obj->data.tracks_end-m_obj->data.tracks_begin);
}

fcc::ConstTrack ConstParticle::tracks(unsigned int index) const {
  if (tracks_size() > index) {
    return m_obj->m_tracks->at(m_obj->data.tracks_begin+index);
  }
  else throw std::out_of_range ("index out of bounds for existing references");
}
std::vector<fcc::ConstCaloCluster>::const_iterator ConstParticle::clusters_begin() const {
  auto ret_value = m_obj->m_clusters->begin();
  std::advance(ret_value, m_obj->data.clusters_begin);
  return ret_value;
}

std::vector<fcc::ConstCaloCluster>::const_iterator ConstParticle::clusters_end() const {
  auto ret_value = m_obj->m_clusters->begin();
  std::advance(ret_value, m_obj->data.clusters_end-1);
  return ++ret_value;
}

unsigned int ConstParticle::clusters_size() const {
  return (m_obj->data.clusters_end-m_obj->data.clusters_begin);
}

fcc::ConstCaloCluster ConstParticle::clusters(unsigned int index) const {
  if (clusters_size() > index) {
    return m_obj->m_clusters->at(m_obj->data.clusters_begin+index);
  }
  else throw std::out_of_range ("index out of bounds for existing references");
}


bool  ConstParticle::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID ConstParticle::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool ConstParticle::operator==(const Particle& other) const {
     return (m_obj==other.m_obj);
}

//bool operator< (const Particle& p1, const Particle& p2 ) {
//  if( p1.m_containerID == p2.m_containerID ) {
//    return p1.m_index < p2.m_index;
//  } else {
//    return p1.m_containerID < p2.m_containerID;
//  }
//}

} // namespace fcc
