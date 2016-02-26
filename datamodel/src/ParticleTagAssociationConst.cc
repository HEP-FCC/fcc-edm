// datamodel specific includes
#include "ParticleTagAssociation.h"
#include "ParticleTagAssociationConst.h"
#include "ParticleTagAssociationObj.h"
#include "ParticleTagAssociationData.h"
#include "ParticleTagAssociationCollection.h"
#include <iostream>
#include "Particle.h"
#include "Tag.h"


namespace fcc {

ConstParticleTagAssociation::ConstParticleTagAssociation() : m_obj(new ParticleTagAssociationObj()){
 m_obj->acquire();
}



ConstParticleTagAssociation::ConstParticleTagAssociation(const ConstParticleTagAssociation& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

ConstParticleTagAssociation& ConstParticleTagAssociation::operator=(const ConstParticleTagAssociation& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

ConstParticleTagAssociation::ConstParticleTagAssociation(ParticleTagAssociationObj* obj) : m_obj(obj){
  if(m_obj != nullptr)
    m_obj->acquire();
}

ConstParticleTagAssociation ConstParticleTagAssociation::clone() const {
  return {new ParticleTagAssociationObj(*m_obj)};
}

ConstParticleTagAssociation::~ConstParticleTagAssociation(){
  if ( m_obj != nullptr) m_obj->release();
}

  const fcc::ConstParticle ConstParticleTagAssociation::Particle() const { if (m_obj->m_Particle == nullptr) {
 return fcc::ConstParticle(nullptr);}
 return fcc::ConstParticle(*(m_obj->m_Particle));}
  const fcc::ConstTag ConstParticleTagAssociation::Tag() const { if (m_obj->m_Tag == nullptr) {
 return fcc::ConstTag(nullptr);}
 return fcc::ConstTag(*(m_obj->m_Tag));}


bool  ConstParticleTagAssociation::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID ConstParticleTagAssociation::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool ConstParticleTagAssociation::operator==(const ParticleTagAssociation& other) const {
     return (m_obj==other.m_obj);
}

//bool operator< (const ParticleTagAssociation& p1, const ParticleTagAssociation& p2 ) {
//  if( p1.m_containerID == p2.m_containerID ) {
//    return p1.m_index < p2.m_index;
//  } else {
//    return p1.m_containerID < p2.m_containerID;
//  }
//}

} // namespace fcc
