// datamodel specific includes
#include "TaggedParticle.h"
#include "TaggedParticleConst.h"
#include "TaggedParticleObj.h"
#include "TaggedParticleData.h"
#include "TaggedParticleCollection.h"
#include <iostream>
#include "Particle.h"


namespace fcc {

TaggedParticle::TaggedParticle() : m_obj(new TaggedParticleObj()){
 m_obj->acquire();
}

TaggedParticle::TaggedParticle(float value) : m_obj(new TaggedParticleObj()) {
  m_obj->acquire();
    m_obj->data.value = value;
}


TaggedParticle::TaggedParticle(const TaggedParticle& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

TaggedParticle& TaggedParticle::operator=(const TaggedParticle& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

TaggedParticle::TaggedParticle(TaggedParticleObj* obj) : m_obj(obj){
  if(m_obj != nullptr)
    m_obj->acquire();
}

TaggedParticle TaggedParticle::clone() const {
  return {new TaggedParticleObj(*m_obj)};
}

TaggedParticle::~TaggedParticle(){
  if ( m_obj != nullptr) m_obj->release();
}

TaggedParticle::operator ConstTaggedParticle() const {return ConstTaggedParticle(m_obj);}

  const float& TaggedParticle::value() const { return m_obj->data.value; }
  const fcc::ConstParticle TaggedParticle::particle() const {
    if (m_obj->m_particle == nullptr) {
      return fcc::ConstParticle(nullptr);
    }
    return fcc::ConstParticle(*(m_obj->m_particle));
  }
void TaggedParticle::value(float value){ m_obj->data.value = value; }
void TaggedParticle::particle(fcc::ConstParticle value) {
  if (m_obj->m_particle != nullptr) delete m_obj->m_particle;
  m_obj->m_particle = new ConstParticle(value);
}



bool  TaggedParticle::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID TaggedParticle::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool TaggedParticle::operator==(const ConstTaggedParticle& other) const {
  return (m_obj==other.m_obj);
}


//bool operator< (const TaggedParticle& p1, const TaggedParticle& p2 ) {
//  if( p1.m_containerID == p2.m_containerID ) {
//    return p1.m_index < p2.m_index;
//  } else {
//    return p1.m_containerID < p2.m_containerID;
//  }
//}

} // namespace fcc
