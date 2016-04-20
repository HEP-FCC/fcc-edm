// datamodel specific includes
#include "Tag.h"
#include "TagConst.h"
#include "TagObj.h"
#include "TagData.h"
#include "TagCollection.h"
#include <iostream>


namespace fcc {

ConstTag::ConstTag() : m_obj(new TagObj()) {
 m_obj->acquire();
}

ConstTag::ConstTag(float Value) : m_obj(new TagObj()){
 m_obj->acquire();
   m_obj->data.Value = Value;
}


ConstTag::ConstTag(const ConstTag& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

ConstTag& ConstTag::operator=(const ConstTag& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

ConstTag::ConstTag(TagObj* obj) : m_obj(obj) {
  if(m_obj != nullptr)
    m_obj->acquire();
}

ConstTag ConstTag::clone() const {
  return {new TagObj(*m_obj)};
}

ConstTag::~ConstTag(){
  if ( m_obj != nullptr) m_obj->release();
}

  const float& ConstTag::Value() const { return m_obj->data.Value; }



bool  ConstTag::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID ConstTag::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool ConstTag::operator==(const Tag& other) const {
     return (m_obj==other.m_obj);
}

//bool operator< (const Tag& p1, const Tag& p2 ) {
//  if( p1.m_containerID == p2.m_containerID ) {
//    return p1.m_index < p2.m_index;
//  } else {
//    return p1.m_containerID < p2.m_containerID;
//  }
//}

} // namespace fcc
