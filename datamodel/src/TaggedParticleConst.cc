// datamodel specific includes
#include "TaggedParticle.h"
#include "TaggedParticleConst.h"
#include "TaggedParticleObj.h"
#include "TaggedParticleData.h"
#include "TaggedParticleCollection.h"
#include <iostream>
#include "Particle.h"


namespace fcc {

ConstTaggedParticle::ConstTaggedParticle() : m_obj(new TaggedParticleObj()) {
 m_obj->acquire();
}

ConstTaggedParticle::ConstTaggedParticle(float value) : m_obj(new TaggedParticleObj()){
 m_obj->acquire();
   m_obj->data.value = value;
}


ConstTaggedParticle::ConstTaggedParticle(const ConstTaggedParticle& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

ConstTaggedParticle& ConstTaggedParticle::operator=(const ConstTaggedParticle& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

ConstTaggedParticle::ConstTaggedParticle(TaggedParticleObj* obj) : m_obj(obj) {
  if(m_obj != nullptr)
    m_obj->acquire();
}

ConstTaggedParticle ConstTaggedParticle::clone() const {
  return {new TaggedParticleObj(*m_obj)};
}

ConstTaggedParticle::~ConstTaggedParticle(){
  if ( m_obj != nullptr) m_obj->release();
}

  /// Access the  the value of the tag
  const float& ConstTaggedParticle::value() const { return m_obj->data.value; }
  /// Access the  Reference to the Particle
  const fcc::ConstParticle ConstTaggedParticle::particle() const {
    if (m_obj->m_particle == nullptr) {
      return fcc::ConstParticle(nullptr);
    }
    return fcc::ConstParticle(*(m_obj->m_particle));}


bool  ConstTaggedParticle::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID ConstTaggedParticle::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool ConstTaggedParticle::operator==(const TaggedParticle& other) const {
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
