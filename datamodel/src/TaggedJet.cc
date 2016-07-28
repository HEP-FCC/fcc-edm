// datamodel specific includes
#include "TaggedJet.h"
#include "TaggedJetConst.h"
#include "TaggedJetObj.h"
#include "TaggedJetData.h"
#include "TaggedJetCollection.h"
#include <iostream>
#include "Jet.h"


namespace fcc {

TaggedJet::TaggedJet() : m_obj(new TaggedJetObj()){
 m_obj->acquire();
}

TaggedJet::TaggedJet(float tag) : m_obj(new TaggedJetObj()) {
  m_obj->acquire();
    m_obj->data.tag = tag;
}


TaggedJet::TaggedJet(const TaggedJet& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

TaggedJet& TaggedJet::operator=(const TaggedJet& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

TaggedJet::TaggedJet(TaggedJetObj* obj) : m_obj(obj){
  if(m_obj != nullptr)
    m_obj->acquire();
}

TaggedJet TaggedJet::clone() const {
  return {new TaggedJetObj(*m_obj)};
}

TaggedJet::~TaggedJet(){
  if ( m_obj != nullptr) m_obj->release();
}

TaggedJet::operator ConstTaggedJet() const {return ConstTaggedJet(m_obj);}

  const float& TaggedJet::tag() const { return m_obj->data.tag; }
  const fcc::ConstJet TaggedJet::jet() const {
    if (m_obj->m_jet == nullptr) {
      return fcc::ConstJet(nullptr);
    }
    return fcc::ConstJet(*(m_obj->m_jet));
  }
void TaggedJet::tag(float value){ m_obj->data.tag = value; }
void TaggedJet::jet(fcc::ConstJet value) {
  if (m_obj->m_jet != nullptr) delete m_obj->m_jet;
  m_obj->m_jet = new ConstJet(value);
}



bool  TaggedJet::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID TaggedJet::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool TaggedJet::operator==(const ConstTaggedJet& other) const {
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
