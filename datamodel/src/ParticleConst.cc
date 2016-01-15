// datamodel specific includes
#include "Particle.h"
#include "ParticleConst.h"
#include "ParticleObj.h"
#include "ParticleData.h"
#include "ParticleCollection.h"
#include <iostream>




ConstParticle::ConstParticle() : m_obj(new ParticleObj()){
 m_obj->acquire();
}

ConstParticle::ConstParticle(BareParticle Core) : m_obj(new ParticleObj()){
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

ConstParticle::ConstParticle(ParticleObj* obj) : m_obj(obj){
  if(m_obj != nullptr)
    m_obj->acquire();
}

ConstParticle ConstParticle::clone() const {
  return {new ParticleObj(*m_obj)};
}

ConstParticle::~ConstParticle(){
  if ( m_obj != nullptr) m_obj->release();
}

  const BareParticle& ConstParticle::Core() const { return m_obj->data.Core; }


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


