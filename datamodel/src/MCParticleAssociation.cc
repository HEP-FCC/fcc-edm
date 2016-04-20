// datamodel specific includes
#include "MCParticleAssociation.h"
#include "MCParticleAssociationConst.h"
#include "MCParticleAssociationObj.h"
#include "MCParticleAssociationData.h"
#include "MCParticleAssociationCollection.h"
#include <iostream>
#include "MCParticle.h"
#include "MCParticle.h"


namespace fcc {

MCParticleAssociation::MCParticleAssociation() : m_obj(new MCParticleAssociationObj()){
 m_obj->acquire();
}



MCParticleAssociation::MCParticleAssociation(const MCParticleAssociation& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

MCParticleAssociation& MCParticleAssociation::operator=(const MCParticleAssociation& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

MCParticleAssociation::MCParticleAssociation(MCParticleAssociationObj* obj) : m_obj(obj){
  if(m_obj != nullptr)
    m_obj->acquire();
}

MCParticleAssociation MCParticleAssociation::clone() const {
  return {new MCParticleAssociationObj(*m_obj)};
}

MCParticleAssociation::~MCParticleAssociation(){
  if ( m_obj != nullptr) m_obj->release();
}

MCParticleAssociation::operator ConstMCParticleAssociation() const {return ConstMCParticleAssociation(m_obj);}

  const fcc::ConstMCParticle MCParticleAssociation::Mother() const {
    if (m_obj->m_Mother == nullptr) {
      return fcc::ConstMCParticle(nullptr);
    }
    return fcc::ConstMCParticle(*(m_obj->m_Mother));
  } const fcc::ConstMCParticle MCParticleAssociation::Daughter() const {
    if (m_obj->m_Daughter == nullptr) {
      return fcc::ConstMCParticle(nullptr);
    }
    return fcc::ConstMCParticle(*(m_obj->m_Daughter));
  }
void MCParticleAssociation::Mother(fcc::ConstMCParticle value) {
  if (m_obj->m_Mother != nullptr) delete m_obj->m_Mother;
  m_obj->m_Mother = new ConstMCParticle(value);
}
void MCParticleAssociation::Daughter(fcc::ConstMCParticle value) {
  if (m_obj->m_Daughter != nullptr) delete m_obj->m_Daughter;
  m_obj->m_Daughter = new ConstMCParticle(value);
}



bool  MCParticleAssociation::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID MCParticleAssociation::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool MCParticleAssociation::operator==(const ConstMCParticleAssociation& other) const {
  return (m_obj==other.m_obj);
}


//bool operator< (const MCParticleAssociation& p1, const MCParticleAssociation& p2 ) {
//  if( p1.m_containerID == p2.m_containerID ) {
//    return p1.m_index < p2.m_index;
//  } else {
//    return p1.m_containerID < p2.m_containerID;
//  }
//}

} // namespace fcc
