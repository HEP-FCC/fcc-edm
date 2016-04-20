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

GenJetTagAssociation::GenJetTagAssociation() : m_obj(new GenJetTagAssociationObj()){
 m_obj->acquire();
}



GenJetTagAssociation::GenJetTagAssociation(const GenJetTagAssociation& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

GenJetTagAssociation& GenJetTagAssociation::operator=(const GenJetTagAssociation& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

GenJetTagAssociation::GenJetTagAssociation(GenJetTagAssociationObj* obj) : m_obj(obj){
  if(m_obj != nullptr)
    m_obj->acquire();
}

GenJetTagAssociation GenJetTagAssociation::clone() const {
  return {new GenJetTagAssociationObj(*m_obj)};
}

GenJetTagAssociation::~GenJetTagAssociation(){
  if ( m_obj != nullptr) m_obj->release();
}

GenJetTagAssociation::operator ConstGenJetTagAssociation() const {return ConstGenJetTagAssociation(m_obj);}

  const fcc::ConstGenJet GenJetTagAssociation::Jet() const {
    if (m_obj->m_Jet == nullptr) {
      return fcc::ConstGenJet(nullptr);
    }
    return fcc::ConstGenJet(*(m_obj->m_Jet));
  } const fcc::ConstTag GenJetTagAssociation::Tag() const {
    if (m_obj->m_Tag == nullptr) {
      return fcc::ConstTag(nullptr);
    }
    return fcc::ConstTag(*(m_obj->m_Tag));
  }
void GenJetTagAssociation::Jet(fcc::ConstGenJet value) {
  if (m_obj->m_Jet != nullptr) delete m_obj->m_Jet;
  m_obj->m_Jet = new ConstGenJet(value);
}
void GenJetTagAssociation::Tag(fcc::ConstTag value) {
  if (m_obj->m_Tag != nullptr) delete m_obj->m_Tag;
  m_obj->m_Tag = new ConstTag(value);
}



bool  GenJetTagAssociation::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID GenJetTagAssociation::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool GenJetTagAssociation::operator==(const ConstGenJetTagAssociation& other) const {
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
