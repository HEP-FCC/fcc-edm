// datamodel specific includes
#include "Jet.h"
#include "JetConst.h"
#include "JetObj.h"
#include "JetData.h"
#include "JetCollection.h"
#include <iostream>




ConstJet::ConstJet() : m_obj(new JetObj()){
 m_obj->acquire();
}

ConstJet::ConstJet(BareJet Core) : m_obj(new JetObj()){
 m_obj->acquire();
   m_obj->data.Core = Core;
}


ConstJet::ConstJet(const ConstJet& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

ConstJet& ConstJet::operator=(const ConstJet& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

ConstJet::ConstJet(JetObj* obj) : m_obj(obj){
  if(m_obj != nullptr)
    m_obj->acquire();
}

ConstJet ConstJet::clone() const {
  return {new JetObj(*m_obj)};
}

ConstJet::~ConstJet(){
  if ( m_obj != nullptr) m_obj->release();
}

  const BareJet& ConstJet::Core() const { return m_obj->data.Core; }


bool  ConstJet::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID ConstJet::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool ConstJet::operator==(const Jet& other) const {
     return (m_obj==other.m_obj);
}

//bool operator< (const Jet& p1, const Jet& p2 ) {
//  if( p1.m_containerID == p2.m_containerID ) {
//    return p1.m_index < p2.m_index;
//  } else {
//    return p1.m_containerID < p2.m_containerID;
//  }
//}


