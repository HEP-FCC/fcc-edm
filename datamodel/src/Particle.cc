// datamodel specific includes
#include "Particle.h"
#include "ParticleConst.h"
#include "ParticleObj.h"
#include "ParticleData.h"
#include "ParticleCollection.h"
#include <iostream>




Particle::Particle() : m_obj(new ParticleObj()){
 m_obj->acquire();
}

Particle::Particle(BareParticle Core) : m_obj(new ParticleObj()){
 m_obj->acquire();
   m_obj->data.Core = Core;
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

  const BareParticle& Particle::Core() const { return m_obj->data.Core; }

  BareParticle& Particle::Core() { return m_obj->data.Core; }
void Particle::Core(class BareParticle value){ m_obj->data.Core = value;}


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


