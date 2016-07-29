// datamodel specific includes
#include "TaggedJet.h"
#include "TaggedJetConst.h"
#include "TaggedJetObj.h"
#include "TaggedJetData.h"
#include "TaggedJetCollection.h"
#include <iostream>
#include "Jet.h"


namespace fcc {

ConstTaggedJet::ConstTaggedJet() : m_obj(new TaggedJetObj()) {
 m_obj->acquire();
}

ConstTaggedJet::ConstTaggedJet(float tag) : m_obj(new TaggedJetObj()){
 m_obj->acquire();
   m_obj->data.tag = tag;
}


ConstTaggedJet::ConstTaggedJet(const ConstTaggedJet& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

ConstTaggedJet& ConstTaggedJet::operator=(const ConstTaggedJet& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

ConstTaggedJet::ConstTaggedJet(TaggedJetObj* obj) : m_obj(obj) {
  if(m_obj != nullptr)
    m_obj->acquire();
}

ConstTaggedJet ConstTaggedJet::clone() const {
  return {new TaggedJetObj(*m_obj)};
}

ConstTaggedJet::~ConstTaggedJet(){
  if ( m_obj != nullptr) m_obj->release();
}

  /// Access the  Result of the tagging algorithm
  const float& ConstTaggedJet::tag() const { return m_obj->data.tag; }
  /// Access the  Reference to the jet
  const fcc::ConstJet ConstTaggedJet::jet() const {
    if (m_obj->m_jet == nullptr) {
      return fcc::ConstJet(nullptr);
    }
    return fcc::ConstJet(*(m_obj->m_jet));}


bool  ConstTaggedJet::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID ConstTaggedJet::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool ConstTaggedJet::operator==(const TaggedJet& other) const {
     return (m_obj==other.m_obj);
}

//bool operator< (const TaggedJet& p1, const TaggedJet& p2 ) {
//  if( p1.m_containerID == p2.m_containerID ) {
//    return p1.m_index < p2.m_index;
//  } else {
//    return p1.m_containerID < p2.m_containerID;
//  }
//}

} // namespace fcc
