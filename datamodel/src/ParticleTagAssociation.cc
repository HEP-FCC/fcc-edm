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

ParticleTagAssociation::ParticleTagAssociation() : m_obj(new ParticleTagAssociationObj()){
 m_obj->acquire();
}



ParticleTagAssociation::ParticleTagAssociation(const ParticleTagAssociation& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

ParticleTagAssociation& ParticleTagAssociation::operator=(const ParticleTagAssociation& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

ParticleTagAssociation::ParticleTagAssociation(ParticleTagAssociationObj* obj) : m_obj(obj){
  if(m_obj != nullptr)
    m_obj->acquire();
}

ParticleTagAssociation ParticleTagAssociation::clone() const {
  return {new ParticleTagAssociationObj(*m_obj)};
}

ParticleTagAssociation::~ParticleTagAssociation(){
  if ( m_obj != nullptr) m_obj->release();
}

ParticleTagAssociation::operator ConstParticleTagAssociation() const {return ConstParticleTagAssociation(m_obj);}

  const fcc::ConstParticle ParticleTagAssociation::Particle() const { if (m_obj->m_Particle == nullptr) {
 return fcc::ConstParticle(nullptr);}
 return fcc::ConstParticle(*(m_obj->m_Particle));}
  const fcc::ConstTag ParticleTagAssociation::Tag() const { if (m_obj->m_Tag == nullptr) {
 return fcc::ConstTag(nullptr);}
 return fcc::ConstTag(*(m_obj->m_Tag));}

void ParticleTagAssociation::Particle(fcc::ConstParticle value) { if (m_obj->m_Particle != nullptr) delete m_obj->m_Particle; m_obj->m_Particle = new ConstParticle(value); }
void ParticleTagAssociation::Tag(fcc::ConstTag value) { if (m_obj->m_Tag != nullptr) delete m_obj->m_Tag; m_obj->m_Tag = new ConstTag(value); }


bool  ParticleTagAssociation::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID ParticleTagAssociation::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool ParticleTagAssociation::operator==(const ConstParticleTagAssociation& other) const {
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
