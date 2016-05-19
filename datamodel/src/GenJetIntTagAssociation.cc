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

GenJetIntTagAssociation::GenJetIntTagAssociation() : m_obj(new GenJetIntTagAssociationObj()){
 m_obj->acquire();
}



GenJetIntTagAssociation::GenJetIntTagAssociation(const GenJetIntTagAssociation& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

GenJetIntTagAssociation& GenJetIntTagAssociation::operator=(const GenJetIntTagAssociation& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

GenJetIntTagAssociation::GenJetIntTagAssociation(GenJetIntTagAssociationObj* obj) : m_obj(obj){
  if(m_obj != nullptr)
    m_obj->acquire();
}

GenJetIntTagAssociation GenJetIntTagAssociation::clone() const {
  return {new GenJetIntTagAssociationObj(*m_obj)};
}

GenJetIntTagAssociation::~GenJetIntTagAssociation(){
  if ( m_obj != nullptr) m_obj->release();
}

GenJetIntTagAssociation::operator ConstGenJetIntTagAssociation() const {return ConstGenJetIntTagAssociation(m_obj);}

  const fcc::ConstGenJet GenJetIntTagAssociation::Jet() const {
    if (m_obj->m_Jet == nullptr) {
      return fcc::ConstGenJet(nullptr);
    }
    return fcc::ConstGenJet(*(m_obj->m_Jet));
  } const fcc::ConstIntTag GenJetIntTagAssociation::Tag() const {
    if (m_obj->m_Tag == nullptr) {
      return fcc::ConstIntTag(nullptr);
    }
    return fcc::ConstIntTag(*(m_obj->m_Tag));
  }
void GenJetIntTagAssociation::Jet(fcc::ConstGenJet value) {
  if (m_obj->m_Jet != nullptr) delete m_obj->m_Jet;
  m_obj->m_Jet = new ConstGenJet(value);
}
void GenJetIntTagAssociation::Tag(fcc::ConstIntTag value) {
  if (m_obj->m_Tag != nullptr) delete m_obj->m_Tag;
  m_obj->m_Tag = new ConstIntTag(value);
}



bool  GenJetIntTagAssociation::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID GenJetIntTagAssociation::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool GenJetIntTagAssociation::operator==(const ConstGenJetIntTagAssociation& other) const {
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
