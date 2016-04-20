// datamodel specific includes
#include "ParticleTrackAssociation.h"
#include "ParticleTrackAssociationConst.h"
#include "ParticleTrackAssociationObj.h"
#include "ParticleTrackAssociationData.h"
#include "ParticleTrackAssociationCollection.h"
#include <iostream>
#include "Particle.h"
#include "Track.h"


namespace fcc {

ParticleTrackAssociation::ParticleTrackAssociation() : m_obj(new ParticleTrackAssociationObj()){
 m_obj->acquire();
}



ParticleTrackAssociation::ParticleTrackAssociation(const ParticleTrackAssociation& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

ParticleTrackAssociation& ParticleTrackAssociation::operator=(const ParticleTrackAssociation& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

ParticleTrackAssociation::ParticleTrackAssociation(ParticleTrackAssociationObj* obj) : m_obj(obj){
  if(m_obj != nullptr)
    m_obj->acquire();
}

ParticleTrackAssociation ParticleTrackAssociation::clone() const {
  return {new ParticleTrackAssociationObj(*m_obj)};
}

ParticleTrackAssociation::~ParticleTrackAssociation(){
  if ( m_obj != nullptr) m_obj->release();
}

ParticleTrackAssociation::operator ConstParticleTrackAssociation() const {return ConstParticleTrackAssociation(m_obj);}

  const fcc::ConstParticle ParticleTrackAssociation::Particle() const {
    if (m_obj->m_Particle == nullptr) {
      return fcc::ConstParticle(nullptr);
    }
    return fcc::ConstParticle(*(m_obj->m_Particle));
  } const fcc::ConstTrack ParticleTrackAssociation::Track() const {
    if (m_obj->m_Track == nullptr) {
      return fcc::ConstTrack(nullptr);
    }
    return fcc::ConstTrack(*(m_obj->m_Track));
  }
void ParticleTrackAssociation::Particle(fcc::ConstParticle value) {
  if (m_obj->m_Particle != nullptr) delete m_obj->m_Particle;
  m_obj->m_Particle = new ConstParticle(value);
}
void ParticleTrackAssociation::Track(fcc::ConstTrack value) {
  if (m_obj->m_Track != nullptr) delete m_obj->m_Track;
  m_obj->m_Track = new ConstTrack(value);
}



bool  ParticleTrackAssociation::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID ParticleTrackAssociation::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool ParticleTrackAssociation::operator==(const ConstParticleTrackAssociation& other) const {
  return (m_obj==other.m_obj);
}


//bool operator< (const ParticleTrackAssociation& p1, const ParticleTrackAssociation& p2 ) {
//  if( p1.m_containerID == p2.m_containerID ) {
//    return p1.m_index < p2.m_index;
//  } else {
//    return p1.m_containerID < p2.m_containerID;
//  }
//}

} // namespace fcc
