// datamodel specific includes
#include "TaggedGenJet.h"
#include "TaggedGenJetConst.h"
#include "TaggedGenJetObj.h"
#include "TaggedGenJetData.h"
#include "TaggedGenJetCollection.h"
#include <iostream>
#include "GenJet.h"


namespace fcc {

TaggedGenJet::TaggedGenJet() : m_obj(new TaggedGenJetObj()){
 m_obj->acquire();
}

TaggedGenJet::TaggedGenJet(float tag) : m_obj(new TaggedGenJetObj()) {
  m_obj->acquire();
    m_obj->data.tag = tag;
}


TaggedGenJet::TaggedGenJet(const TaggedGenJet& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

TaggedGenJet& TaggedGenJet::operator=(const TaggedGenJet& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

TaggedGenJet::TaggedGenJet(TaggedGenJetObj* obj) : m_obj(obj){
  if(m_obj != nullptr)
    m_obj->acquire();
}

TaggedGenJet TaggedGenJet::clone() const {
  return {new TaggedGenJetObj(*m_obj)};
}

TaggedGenJet::~TaggedGenJet(){
  if ( m_obj != nullptr) m_obj->release();
}

TaggedGenJet::operator ConstTaggedGenJet() const {return ConstTaggedGenJet(m_obj);}

  const float& TaggedGenJet::tag() const { return m_obj->data.tag; }
  const fcc::ConstGenJet TaggedGenJet::jet() const {
    if (m_obj->m_jet == nullptr) {
      return fcc::ConstGenJet(nullptr);
    }
    return fcc::ConstGenJet(*(m_obj->m_jet));
  }
void TaggedGenJet::tag(float value){ m_obj->data.tag = value; }
void TaggedGenJet::jet(fcc::ConstGenJet value) {
  if (m_obj->m_jet != nullptr) delete m_obj->m_jet;
  m_obj->m_jet = new ConstGenJet(value);
}



bool  TaggedGenJet::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID TaggedGenJet::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool TaggedGenJet::operator==(const ConstTaggedGenJet& other) const {
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
