// datamodel specific includes
#include "GenJetTagAssociation.h"
#include "GenJetTagAssociationConst.h"
#include "GenJetTagAssociationObj.h"
#include "GenJetTagAssociationData.h"
#include "GenJetTagAssociationCollection.h"
#include <iostream>
#include "GenJet.h"
#include "Tag.h"


namespace fcc {

ConstGenJetTagAssociation::ConstGenJetTagAssociation() : m_obj(new GenJetTagAssociationObj()) {
 m_obj->acquire();
}



ConstGenJetTagAssociation::ConstGenJetTagAssociation(const ConstGenJetTagAssociation& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

ConstGenJetTagAssociation& ConstGenJetTagAssociation::operator=(const ConstGenJetTagAssociation& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

ConstGenJetTagAssociation::ConstGenJetTagAssociation(GenJetTagAssociationObj* obj) : m_obj(obj) {
  if(m_obj != nullptr)
    m_obj->acquire();
}

ConstGenJetTagAssociation ConstGenJetTagAssociation::clone() const {
  return {new GenJetTagAssociationObj(*m_obj)};
}

ConstGenJetTagAssociation::~ConstGenJetTagAssociation(){
  if ( m_obj != nullptr) m_obj->release();
}

  const fcc::ConstGenJet ConstGenJetTagAssociation::Jet() const {
    if (m_obj->m_Jet == nullptr) {
      return fcc::ConstGenJet(nullptr);
    }
    return fcc::ConstGenJet(*(m_obj->m_Jet));}  const fcc::ConstTag ConstGenJetTagAssociation::Tag() const {
    if (m_obj->m_Tag == nullptr) {
      return fcc::ConstTag(nullptr);
    }
    return fcc::ConstTag(*(m_obj->m_Tag));}


bool  ConstGenJetTagAssociation::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID ConstGenJetTagAssociation::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool ConstGenJetTagAssociation::operator==(const GenJetTagAssociation& other) const {
     return (m_obj==other.m_obj);
}

//bool operator< (const GenJetTagAssociation& p1, const GenJetTagAssociation& p2 ) {
//  if( p1.m_containerID == p2.m_containerID ) {
//    return p1.m_index < p2.m_index;
//  } else {
//    return p1.m_containerID < p2.m_containerID;
//  }
//}

} // namespace fcc
