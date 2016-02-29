// datamodel specific includes
#include "IntTag.h"
#include "IntTagConst.h"
#include "IntTagObj.h"
#include "IntTagData.h"
#include "IntTagCollection.h"
#include <iostream>


namespace fcc {

IntTag::IntTag() : m_obj(new IntTagObj()){
 m_obj->acquire();
}

IntTag::IntTag(int Value) : m_obj(new IntTagObj()){
 m_obj->acquire();
   m_obj->data.Value = Value;
}


IntTag::IntTag(const IntTag& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

IntTag& IntTag::operator=(const IntTag& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

IntTag::IntTag(IntTagObj* obj) : m_obj(obj){
  if(m_obj != nullptr)
    m_obj->acquire();
}

IntTag IntTag::clone() const {
  return {new IntTagObj(*m_obj)};
}

IntTag::~IntTag(){
  if ( m_obj != nullptr) m_obj->release();
}

IntTag::operator ConstIntTag() const {return ConstIntTag(m_obj);}

  const int& IntTag::Value() const { return m_obj->data.Value; }

void IntTag::Value(int value){ m_obj->data.Value = value;}


bool  IntTag::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID IntTag::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool IntTag::operator==(const ConstIntTag& other) const {
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
