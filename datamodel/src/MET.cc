// datamodel specific includes
#include "MET.h"
#include "METConst.h"
#include "METObj.h"
#include "METData.h"
#include "METCollection.h"
#include <iostream>


namespace fcc {

MET::MET() : m_obj(new METObj()){
 m_obj->acquire();
}

MET::MET(float magnitude,float phi,float scalarSum) : m_obj(new METObj()) {
  m_obj->acquire();
    m_obj->data.magnitude = magnitude;  m_obj->data.phi = phi;  m_obj->data.scalarSum = scalarSum;
}


MET::MET(const MET& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

MET& MET::operator=(const MET& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

MET::MET(METObj* obj) : m_obj(obj){
  if(m_obj != nullptr)
    m_obj->acquire();
}

MET MET::clone() const {
  return {new METObj(*m_obj)};
}

MET::~MET(){
  if ( m_obj != nullptr) m_obj->release();
}

MET::operator ConstMET() const {return ConstMET(m_obj);}

  const float& MET::magnitude() const { return m_obj->data.magnitude; }
  const float& MET::phi() const { return m_obj->data.phi; }
  const float& MET::scalarSum() const { return m_obj->data.scalarSum; }

void MET::magnitude(float value){ m_obj->data.magnitude = value; }
void MET::phi(float value){ m_obj->data.phi = value; }
void MET::scalarSum(float value){ m_obj->data.scalarSum = value; }



bool  MET::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID MET::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool MET::operator==(const ConstMET& other) const {
  return (m_obj==other.m_obj);
}


//bool operator< (const MET& p1, const MET& p2 ) {
//  if( p1.m_containerID == p2.m_containerID ) {
//    return p1.m_index < p2.m_index;
//  } else {
//    return p1.m_containerID < p2.m_containerID;
//  }
//}

} // namespace fcc
