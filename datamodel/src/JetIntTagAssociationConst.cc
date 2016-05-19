// datamodel specific includes
#include "JetIntTagAssociation.h"
#include "JetIntTagAssociationConst.h"
#include "JetIntTagAssociationObj.h"
#include "JetIntTagAssociationData.h"
#include "JetIntTagAssociationCollection.h"
#include <iostream>
#include "Jet.h"
#include "IntTag.h"


namespace fcc {

ConstJetIntTagAssociation::ConstJetIntTagAssociation() : m_obj(new JetIntTagAssociationObj()) {
 m_obj->acquire();
}



ConstJetIntTagAssociation::ConstJetIntTagAssociation(const ConstJetIntTagAssociation& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

ConstJetIntTagAssociation& ConstJetIntTagAssociation::operator=(const ConstJetIntTagAssociation& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

ConstJetIntTagAssociation::ConstJetIntTagAssociation(JetIntTagAssociationObj* obj) : m_obj(obj) {
  if(m_obj != nullptr)
    m_obj->acquire();
}

ConstJetIntTagAssociation ConstJetIntTagAssociation::clone() const {
  return {new JetIntTagAssociationObj(*m_obj)};
}

ConstJetIntTagAssociation::~ConstJetIntTagAssociation(){
  if ( m_obj != nullptr) m_obj->release();
}

  const fcc::ConstJet ConstJetIntTagAssociation::Jet() const {
    if (m_obj->m_Jet == nullptr) {
      return fcc::ConstJet(nullptr);
    }
    return fcc::ConstJet(*(m_obj->m_Jet));} const fcc::ConstIntTag ConstJetIntTagAssociation::Tag() const {
    if (m_obj->m_Tag == nullptr) {
      return fcc::ConstIntTag(nullptr);
    }
    return fcc::ConstIntTag(*(m_obj->m_Tag));}


bool  ConstJetIntTagAssociation::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID ConstJetIntTagAssociation::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool ConstJetIntTagAssociation::operator==(const JetIntTagAssociation& other) const {
     return (m_obj==other.m_obj);
}

//bool operator< (const JetIntTagAssociation& p1, const JetIntTagAssociation& p2 ) {
//  if( p1.m_containerID == p2.m_containerID ) {
//    return p1.m_index < p2.m_index;
//  } else {
//    return p1.m_containerID < p2.m_containerID;
//  }
//}

} // namespace fcc
