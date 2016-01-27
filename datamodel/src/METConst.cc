// datamodel specific includes
#include "MET.h"
#include "METConst.h"
#include "METObj.h"
#include "METData.h"
#include "METCollection.h"
#include <iostream>




ConstMET::ConstMET() : m_obj(new METObj()){
 m_obj->acquire();
}

ConstMET::ConstMET(float Magnitude,float Phi,float ScalarSum) : m_obj(new METObj()){
 m_obj->acquire();
   m_obj->data.Magnitude = Magnitude;  m_obj->data.Phi = Phi;  m_obj->data.ScalarSum = ScalarSum;
}


ConstMET::ConstMET(const ConstMET& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

ConstMET& ConstMET::operator=(const ConstMET& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

ConstMET::ConstMET(METObj* obj) : m_obj(obj){
  if(m_obj != nullptr)
    m_obj->acquire();
}

ConstMET ConstMET::clone() const {
  return {new METObj(*m_obj)};
}

ConstMET::~ConstMET(){
  if ( m_obj != nullptr) m_obj->release();
}

  const float& ConstMET::Magnitude() const { return m_obj->data.Magnitude; }
  const float& ConstMET::Phi() const { return m_obj->data.Phi; }
  const float& ConstMET::ScalarSum() const { return m_obj->data.ScalarSum; }


bool  ConstMET::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID ConstMET::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool ConstMET::operator==(const MET& other) const {
     return (m_obj==other.m_obj);
}

//bool operator< (const MET& p1, const MET& p2 ) {
//  if( p1.m_containerID == p2.m_containerID ) {
//    return p1.m_index < p2.m_index;
//  } else {
//    return p1.m_containerID < p2.m_containerID;
//  }
//}


