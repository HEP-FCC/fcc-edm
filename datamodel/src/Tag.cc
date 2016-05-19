// datamodel specific includes
#include "Tag.h"
#include "TagConst.h"
#include "TagObj.h"
#include "TagData.h"
#include "TagCollection.h"
#include <iostream>


namespace fcc {

Tag::Tag() : m_obj(new TagObj()){
 m_obj->acquire();
}

Tag::Tag(float Value) : m_obj(new TagObj()) {
  m_obj->acquire();
    m_obj->data.Value = Value;
}


Tag::Tag(const Tag& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

Tag& Tag::operator=(const Tag& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

Tag::Tag(TagObj* obj) : m_obj(obj){
  if(m_obj != nullptr)
    m_obj->acquire();
}

Tag Tag::clone() const {
  return {new TagObj(*m_obj)};
}

Tag::~Tag(){
  if ( m_obj != nullptr) m_obj->release();
}

Tag::operator ConstTag() const {return ConstTag(m_obj);}

  const float& Tag::Value() const { return m_obj->data.Value; }

void Tag::Value(float value){ m_obj->data.Value = value; }



bool  Tag::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID Tag::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool Tag::operator==(const ConstTag& other) const {
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
