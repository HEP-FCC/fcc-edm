// datamodel specific includes
#include "GenJet.h"
#include "GenJetConst.h"
#include "GenJetObj.h"
#include "GenJetData.h"
#include "GenJetCollection.h"
#include <iostream>


namespace fcc {

ConstGenJet::ConstGenJet() : m_obj(new GenJetObj()){
 m_obj->acquire();
}

ConstGenJet::ConstGenJet(fcc::BareJet Core) : m_obj(new GenJetObj()){
 m_obj->acquire();
   m_obj->data.Core = Core;
}


ConstGenJet::ConstGenJet(const ConstGenJet& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

ConstGenJet& ConstGenJet::operator=(const ConstGenJet& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

ConstGenJet::ConstGenJet(GenJetObj* obj) : m_obj(obj){
  if(m_obj != nullptr)
    m_obj->acquire();
}

ConstGenJet ConstGenJet::clone() const {
  return {new GenJetObj(*m_obj)};
}

ConstGenJet::~ConstGenJet(){
  if ( m_obj != nullptr) m_obj->release();
}

  const fcc::BareJet& ConstGenJet::Core() const { return m_obj->data.Core; }


bool  ConstGenJet::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID ConstGenJet::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool ConstGenJet::operator==(const GenJet& other) const {
     return (m_obj==other.m_obj);
}

//bool operator< (const GenJet& p1, const GenJet& p2 ) {
//  if( p1.m_containerID == p2.m_containerID ) {
//    return p1.m_index < p2.m_index;
//  } else {
//    return p1.m_containerID < p2.m_containerID;
//  }
//}

} // namespace fcc
