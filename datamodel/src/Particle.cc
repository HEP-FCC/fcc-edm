// datamodel specific includes
#include "Particle.h"
#include "ParticleConst.h"
#include "ParticleObj.h"
#include "ParticleData.h"
#include "ParticleCollection.h"
#include <iostream>


namespace fcc {

Particle::Particle() : m_obj(new ParticleObj()){
 m_obj->acquire();
}

Particle::Particle(fcc::BareParticle core) : m_obj(new ParticleObj()) {
  m_obj->acquire();
    m_obj->data.core = core;
}


Particle::Particle(const Particle& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

Particle& Particle::operator=(const Particle& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

Particle::Particle(ParticleObj* obj) : m_obj(obj){
  if(m_obj != nullptr)
    m_obj->acquire();
}

Particle Particle::clone() const {
  return {new ParticleObj(*m_obj)};
}

Particle::~Particle(){
  if ( m_obj != nullptr) m_obj->release();
}

Particle::operator ConstParticle() const {return ConstParticle(m_obj);}

  const fcc::BareParticle& Particle::core() const { return m_obj->data.core; }
const unsigned& Particle::bits() const { return m_obj->data.core.bits; }
const int& Particle::charge() const { return m_obj->data.core.charge; }
const ::fcc::LorentzVector& Particle::p4() const { return m_obj->data.core.p4; }
const unsigned& Particle::status() const { return m_obj->data.core.status; }
const int& Particle::type() const { return m_obj->data.core.type; }
const ::fcc::Point& Particle::vertex() const { return m_obj->data.core.vertex; }

  fcc::BareParticle& Particle::core() { return m_obj->data.core; }
void Particle::core(class fcc::BareParticle value) { m_obj->data.core = value; }
void Particle::bits(unsigned value){ m_obj->data.core.bits = value; }
void Particle::charge(int value){ m_obj->data.core.charge = value; }
::fcc::LorentzVector& Particle::p4() { return m_obj->data.core.p4; }
void Particle::p4(class ::fcc::LorentzVector value) { m_obj->data.core.p4 = value; }
void Particle::status(unsigned value){ m_obj->data.core.status = value; }
void Particle::type(int value){ m_obj->data.core.type = value; }
::fcc::Point& Particle::vertex() { return m_obj->data.core.vertex; }
void Particle::vertex(class ::fcc::Point value) { m_obj->data.core.vertex = value; }

std::vector<fcc::ConstTrack>::const_iterator Particle::tracks_begin() const {
  auto ret_value = m_obj->m_tracks->begin();
  std::advance(ret_value, m_obj->data.tracks_begin);
  return ret_value;
}

std::vector<fcc::ConstTrack>::const_iterator Particle::tracks_end() const {
  auto ret_value = m_obj->m_tracks->begin();
//fg: this code fails if m_obj->data.tracks==0
//  std::advance(ret_value, m_obj->data.tracks_end-1);
//  return ++ret_value;
  std::advance(ret_value, m_obj->data.tracks_end);
  return ret_value;
}

void Particle::addtracks(fcc::ConstTrack component) {
  m_obj->m_tracks->push_back(component);
  m_obj->data.tracks_end++;
}

unsigned int Particle::tracks_size() const {
  return (m_obj->data.tracks_end-m_obj->data.tracks_begin);
}

fcc::ConstTrack Particle::tracks(unsigned int index) const {
  if (tracks_size() > index) {
    return m_obj->m_tracks->at(m_obj->data.tracks_begin+index);
  }
  else throw std::out_of_range ("index out of bounds for existing references");
}
std::vector<fcc::ConstCaloCluster>::const_iterator Particle::clusters_begin() const {
  auto ret_value = m_obj->m_clusters->begin();
  std::advance(ret_value, m_obj->data.clusters_begin);
  return ret_value;
}

std::vector<fcc::ConstCaloCluster>::const_iterator Particle::clusters_end() const {
  auto ret_value = m_obj->m_clusters->begin();
//fg: this code fails if m_obj->data.clusters==0
//  std::advance(ret_value, m_obj->data.clusters_end-1);
//  return ++ret_value;
  std::advance(ret_value, m_obj->data.clusters_end);
  return ret_value;
}

void Particle::addclusters(fcc::ConstCaloCluster component) {
  m_obj->m_clusters->push_back(component);
  m_obj->data.clusters_end++;
}

unsigned int Particle::clusters_size() const {
  return (m_obj->data.clusters_end-m_obj->data.clusters_begin);
}

fcc::ConstCaloCluster Particle::clusters(unsigned int index) const {
  if (clusters_size() > index) {
    return m_obj->m_clusters->at(m_obj->data.clusters_begin+index);
  }
  else throw std::out_of_range ("index out of bounds for existing references");
}


bool  Particle::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID Particle::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool Particle::operator==(const ConstParticle& other) const {
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
