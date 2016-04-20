// datamodel specific includes
#include "GenJetIntTagAssociation.h"
#include "GenJetIntTagAssociationConst.h"
#include "GenJetIntTagAssociationObj.h"
#include "GenJetIntTagAssociationData.h"
#include "GenJetIntTagAssociationCollection.h"
#include <iostream>
#include "GenJet.h"
#include "IntTag.h"


namespace fcc {

ConstGenJetIntTagAssociation::ConstGenJetIntTagAssociation() : m_obj(new GenJetIntTagAssociationObj()) {
 m_obj->acquire();
}



ConstGenJetIntTagAssociation::ConstGenJetIntTagAssociation(const ConstGenJetIntTagAssociation& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

ConstGenJetIntTagAssociation& ConstGenJetIntTagAssociation::operator=(const ConstGenJetIntTagAssociation& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

ConstGenJetIntTagAssociation::ConstGenJetIntTagAssociation(GenJetIntTagAssociationObj* obj) : m_obj(obj) {
  if(m_obj != nullptr)
    m_obj->acquire();
}

ConstGenJetIntTagAssociation ConstGenJetIntTagAssociation::clone() const {
  return {new GenJetIntTagAssociationObj(*m_obj)};
}

ConstGenJetIntTagAssociation::~ConstGenJetIntTagAssociation(){
  if ( m_obj != nullptr) m_obj->release();
}

  const fcc::ConstGenJet ConstGenJetIntTagAssociation::Jet() const {
    if (m_obj->m_Jet == nullptr) {
      return fcc::ConstGenJet(nullptr);
    }
    return fcc::ConstGenJet(*(m_obj->m_Jet));}  const fcc::ConstIntTag ConstGenJetIntTagAssociation::Tag() const {
    if (m_obj->m_Tag == nullptr) {
      return fcc::ConstIntTag(nullptr);
    }
    return fcc::ConstIntTag(*(m_obj->m_Tag));}


bool  ConstGenJetIntTagAssociation::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID ConstGenJetIntTagAssociation::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool ConstGenJetIntTagAssociation::operator==(const GenJetIntTagAssociation& other) const {
     return (m_obj==other.m_obj);
}

//bool operator< (const GenJetIntTagAssociation& p1, const GenJetIntTagAssociation& p2 ) {
//  if( p1.m_containerID == p2.m_containerID ) {
//    return p1.m_index < p2.m_index;
//  } else {
//    return p1.m_containerID < p2.m_containerID;
//  }
//}

} // namespace fcc
