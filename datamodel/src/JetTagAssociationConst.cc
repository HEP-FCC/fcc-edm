// datamodel specific includes
#include "JetTagAssociation.h"
#include "JetTagAssociationConst.h"
#include "JetTagAssociationObj.h"
#include "JetTagAssociationData.h"
#include "JetTagAssociationCollection.h"
#include <iostream>
#include "Jet.h"
#include "Tag.h"


namespace fcc {

ConstJetTagAssociation::ConstJetTagAssociation() : m_obj(new JetTagAssociationObj()){
 m_obj->acquire();
}



ConstJetTagAssociation::ConstJetTagAssociation(const ConstJetTagAssociation& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

ConstJetTagAssociation& ConstJetTagAssociation::operator=(const ConstJetTagAssociation& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

ConstJetTagAssociation::ConstJetTagAssociation(JetTagAssociationObj* obj) : m_obj(obj){
  if(m_obj != nullptr)
    m_obj->acquire();
}

ConstJetTagAssociation ConstJetTagAssociation::clone() const {
  return {new JetTagAssociationObj(*m_obj)};
}

ConstJetTagAssociation::~ConstJetTagAssociation(){
  if ( m_obj != nullptr) m_obj->release();
}

  const fcc::ConstJet ConstJetTagAssociation::Jet() const { if (m_obj->m_Jet == nullptr) {
 return fcc::ConstJet(nullptr);}
 return fcc::ConstJet(*(m_obj->m_Jet));}
  const fcc::ConstTag ConstJetTagAssociation::Tag() const { if (m_obj->m_Tag == nullptr) {
 return fcc::ConstTag(nullptr);}
 return fcc::ConstTag(*(m_obj->m_Tag));}


bool  ConstJetTagAssociation::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID ConstJetTagAssociation::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool ConstJetTagAssociation::operator==(const JetTagAssociation& other) const {
     return (m_obj==other.m_obj);
}

//bool operator< (const JetTagAssociation& p1, const JetTagAssociation& p2 ) {
//  if( p1.m_containerID == p2.m_containerID ) {
//    return p1.m_index < p2.m_index;
//  } else {
//    return p1.m_containerID < p2.m_containerID;
//  }
//}

} // namespace fcc
