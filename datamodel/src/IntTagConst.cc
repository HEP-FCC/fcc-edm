// datamodel specific includes
#include "IntTag.h"
#include "IntTagConst.h"
#include "IntTagObj.h"
#include "IntTagData.h"
#include "IntTagCollection.h"
#include <iostream>


namespace fcc {

ConstIntTag::ConstIntTag() : m_obj(new IntTagObj()) {
 m_obj->acquire();
}

ConstIntTag::ConstIntTag(int Value) : m_obj(new IntTagObj()){
 m_obj->acquire();
   m_obj->data.Value = Value;
}


ConstIntTag::ConstIntTag(const ConstIntTag& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

ConstIntTag& ConstIntTag::operator=(const ConstIntTag& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

ConstIntTag::ConstIntTag(IntTagObj* obj) : m_obj(obj) {
  if(m_obj != nullptr)
    m_obj->acquire();
}

ConstIntTag ConstIntTag::clone() const {
  return {new IntTagObj(*m_obj)};
}

ConstIntTag::~ConstIntTag(){
  if ( m_obj != nullptr) m_obj->release();
}

  const int& ConstIntTag::Value() const { return m_obj->data.Value; }



bool  ConstIntTag::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID ConstIntTag::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool ConstIntTag::operator==(const IntTag& other) const {
     return (m_obj==other.m_obj);
}

//bool operator< (const IntTag& p1, const IntTag& p2 ) {
//  if( p1.m_containerID == p2.m_containerID ) {
//    return p1.m_index < p2.m_index;
//  } else {
//    return p1.m_containerID < p2.m_containerID;
//  }
//}

} // namespace fcc
