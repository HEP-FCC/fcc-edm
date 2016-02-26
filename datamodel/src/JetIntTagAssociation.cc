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

JetIntTagAssociation::JetIntTagAssociation() : m_obj(new JetIntTagAssociationObj()){
 m_obj->acquire();
}



JetIntTagAssociation::JetIntTagAssociation(const JetIntTagAssociation& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

JetIntTagAssociation& JetIntTagAssociation::operator=(const JetIntTagAssociation& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

JetIntTagAssociation::JetIntTagAssociation(JetIntTagAssociationObj* obj) : m_obj(obj){
  if(m_obj != nullptr)
    m_obj->acquire();
}

JetIntTagAssociation JetIntTagAssociation::clone() const {
  return {new JetIntTagAssociationObj(*m_obj)};
}

JetIntTagAssociation::~JetIntTagAssociation(){
  if ( m_obj != nullptr) m_obj->release();
}

JetIntTagAssociation::operator ConstJetIntTagAssociation() const {return ConstJetIntTagAssociation(m_obj);}

  const fcc::ConstJet JetIntTagAssociation::Jet() const { if (m_obj->m_Jet == nullptr) {
 return fcc::ConstJet(nullptr);}
 return fcc::ConstJet(*(m_obj->m_Jet));}
  const fcc::ConstIntTag JetIntTagAssociation::Tag() const { if (m_obj->m_Tag == nullptr) {
 return fcc::ConstIntTag(nullptr);}
 return fcc::ConstIntTag(*(m_obj->m_Tag));}

void JetIntTagAssociation::Jet(fcc::ConstJet value) { if (m_obj->m_Jet != nullptr) delete m_obj->m_Jet; m_obj->m_Jet = new ConstJet(value); }
void JetIntTagAssociation::Tag(fcc::ConstIntTag value) { if (m_obj->m_Tag != nullptr) delete m_obj->m_Tag; m_obj->m_Tag = new ConstIntTag(value); }


bool  JetIntTagAssociation::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID JetIntTagAssociation::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool JetIntTagAssociation::operator==(const ConstJetIntTagAssociation& other) const {
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
