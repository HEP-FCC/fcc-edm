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

JetTagAssociation::JetTagAssociation() : m_obj(new JetTagAssociationObj()){
 m_obj->acquire();
}



JetTagAssociation::JetTagAssociation(const JetTagAssociation& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

JetTagAssociation& JetTagAssociation::operator=(const JetTagAssociation& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

JetTagAssociation::JetTagAssociation(JetTagAssociationObj* obj) : m_obj(obj){
  if(m_obj != nullptr)
    m_obj->acquire();
}

JetTagAssociation JetTagAssociation::clone() const {
  return {new JetTagAssociationObj(*m_obj)};
}

JetTagAssociation::~JetTagAssociation(){
  if ( m_obj != nullptr) m_obj->release();
}

JetTagAssociation::operator ConstJetTagAssociation() const {return ConstJetTagAssociation(m_obj);}

  const fcc::ConstJet JetTagAssociation::Jet() const {
    if (m_obj->m_Jet == nullptr) {
      return fcc::ConstJet(nullptr);
    }
    return fcc::ConstJet(*(m_obj->m_Jet));
  } const fcc::ConstTag JetTagAssociation::Tag() const {
    if (m_obj->m_Tag == nullptr) {
      return fcc::ConstTag(nullptr);
    }
    return fcc::ConstTag(*(m_obj->m_Tag));
  }
void JetTagAssociation::Jet(fcc::ConstJet value) {
  if (m_obj->m_Jet != nullptr) delete m_obj->m_Jet;
  m_obj->m_Jet = new ConstJet(value);
}
void JetTagAssociation::Tag(fcc::ConstTag value) {
  if (m_obj->m_Tag != nullptr) delete m_obj->m_Tag;
  m_obj->m_Tag = new ConstTag(value);
}



bool  JetTagAssociation::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID JetTagAssociation::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool JetTagAssociation::operator==(const ConstJetTagAssociation& other) const {
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
