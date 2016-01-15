// datamodel specific includes
#include "ParticleTrackAssociation.h"
#include "ParticleTrackAssociationConst.h"
#include "ParticleTrackAssociationObj.h"
#include "ParticleTrackAssociationData.h"
#include "ParticleTrackAssociationCollection.h"
#include <iostream>
#include "Particle.h"
#include "Track.h"




ConstParticleTrackAssociation::ConstParticleTrackAssociation() : m_obj(new ParticleTrackAssociationObj()){
 m_obj->acquire();
}



ConstParticleTrackAssociation::ConstParticleTrackAssociation(const ConstParticleTrackAssociation& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

ConstParticleTrackAssociation& ConstParticleTrackAssociation::operator=(const ConstParticleTrackAssociation& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

ConstParticleTrackAssociation::ConstParticleTrackAssociation(ParticleTrackAssociationObj* obj) : m_obj(obj){
  if(m_obj != nullptr)
    m_obj->acquire();
}

ConstParticleTrackAssociation ConstParticleTrackAssociation::clone() const {
  return {new ParticleTrackAssociationObj(*m_obj)};
}

ConstParticleTrackAssociation::~ConstParticleTrackAssociation(){
  if ( m_obj != nullptr) m_obj->release();
}

  const ConstParticle ConstParticleTrackAssociation::Particle() const { if (m_obj->m_Particle == nullptr) {
 return ConstParticle(nullptr);}
 return ConstParticle(*(m_obj->m_Particle));}
  const ConstTrack ConstParticleTrackAssociation::Track() const { if (m_obj->m_Track == nullptr) {
 return ConstTrack(nullptr);}
 return ConstTrack(*(m_obj->m_Track));}


bool  ConstParticleTrackAssociation::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID ConstParticleTrackAssociation::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool ConstParticleTrackAssociation::operator==(const ParticleTrackAssociation& other) const {
     return (m_obj==other.m_obj);
}

//bool operator< (const ParticleTrackAssociation& p1, const ParticleTrackAssociation& p2 ) {
//  if( p1.m_containerID == p2.m_containerID ) {
//    return p1.m_index < p2.m_index;
//  } else {
//    return p1.m_containerID < p2.m_containerID;
//  }
//}


