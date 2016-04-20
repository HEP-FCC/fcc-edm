// datamodel specific includes
#include "GenJet.h"
#include "GenJetConst.h"
#include "GenJetObj.h"
#include "GenJetData.h"
#include "GenJetCollection.h"
#include <iostream>


namespace fcc {

GenJet::GenJet() : m_obj(new GenJetObj()){
 m_obj->acquire();
}

GenJet::GenJet(fcc::BareJet Core) : m_obj(new GenJetObj()) {
  m_obj->acquire();
    m_obj->data.Core = Core;
}


GenJet::GenJet(const GenJet& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

GenJet& GenJet::operator=(const GenJet& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

GenJet::GenJet(GenJetObj* obj) : m_obj(obj){
  if(m_obj != nullptr)
    m_obj->acquire();
}

GenJet GenJet::clone() const {
  return {new GenJetObj(*m_obj)};
}

GenJet::~GenJet(){
  if ( m_obj != nullptr) m_obj->release();
}

GenJet::operator ConstGenJet() const {return ConstGenJet(m_obj);}

  const fcc::BareJet& GenJet::Core() const { return m_obj->data.Core; }

  fcc::BareJet& GenJet::Core() { return m_obj->data.Core; }
void GenJet::Core(class fcc::BareJet value) { m_obj->data.Core = value; }



bool  GenJet::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID GenJet::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool GenJet::operator==(const ConstGenJet& other) const {
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
