// datamodel specific includes
#include "TaggedGenJet.h"
#include "TaggedGenJetConst.h"
#include "TaggedGenJetObj.h"
#include "TaggedGenJetData.h"
#include "TaggedGenJetCollection.h"
#include <iostream>
#include "GenJet.h"


namespace fcc {

ConstTaggedGenJet::ConstTaggedGenJet() : m_obj(new TaggedGenJetObj()) {
 m_obj->acquire();
}

ConstTaggedGenJet::ConstTaggedGenJet(float tag) : m_obj(new TaggedGenJetObj()){
 m_obj->acquire();
   m_obj->data.tag = tag;
}


ConstTaggedGenJet::ConstTaggedGenJet(const ConstTaggedGenJet& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

ConstTaggedGenJet& ConstTaggedGenJet::operator=(const ConstTaggedGenJet& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

ConstTaggedGenJet::ConstTaggedGenJet(TaggedGenJetObj* obj) : m_obj(obj) {
  if(m_obj != nullptr)
    m_obj->acquire();
}

ConstTaggedGenJet ConstTaggedGenJet::clone() const {
  return {new TaggedGenJetObj(*m_obj)};
}

ConstTaggedGenJet::~ConstTaggedGenJet(){
  if ( m_obj != nullptr) m_obj->release();
}

  /// Access the  Result of the tagging algorithm
  const float& ConstTaggedGenJet::tag() const { return m_obj->data.tag; }
  /// Access the  Reference to the gen jet
  const fcc::ConstGenJet ConstTaggedGenJet::jet() const {
    if (m_obj->m_jet == nullptr) {
      return fcc::ConstGenJet(nullptr);
    }
    return fcc::ConstGenJet(*(m_obj->m_jet));}


bool  ConstTaggedGenJet::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID ConstTaggedGenJet::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool ConstTaggedGenJet::operator==(const TaggedGenJet& other) const {
     return (m_obj==other.m_obj);
}

//bool operator< (const TaggedGenJet& p1, const TaggedGenJet& p2 ) {
//  if( p1.m_containerID == p2.m_containerID ) {
//    return p1.m_index < p2.m_index;
//  } else {
//    return p1.m_containerID < p2.m_containerID;
//  }
//}

} // namespace fcc
