// datamodel specific includes
#include "MissingEnergy.h"
#include "MissingEnergyConst.h"
#include "MissingEnergyObj.h"
#include "MissingEnergyData.h"
#include "MissingEnergyCollection.h"
#include <iostream>




ConstMissingEnergy::ConstMissingEnergy() : m_obj(new MissingEnergyObj()){
 m_obj->acquire();
}

ConstMissingEnergy::ConstMissingEnergy(float Energy,float Phi) : m_obj(new MissingEnergyObj()){
 m_obj->acquire();
   m_obj->data.Energy = Energy;  m_obj->data.Phi = Phi;
}


ConstMissingEnergy::ConstMissingEnergy(const ConstMissingEnergy& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

ConstMissingEnergy& ConstMissingEnergy::operator=(const ConstMissingEnergy& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

ConstMissingEnergy::ConstMissingEnergy(MissingEnergyObj* obj) : m_obj(obj){
  if(m_obj != nullptr)
    m_obj->acquire();
}

ConstMissingEnergy ConstMissingEnergy::clone() const {
  return {new MissingEnergyObj(*m_obj)};
}

ConstMissingEnergy::~ConstMissingEnergy(){
  if ( m_obj != nullptr) m_obj->release();
}

  const float& ConstMissingEnergy::Energy() const { return m_obj->data.Energy; }
  const float& ConstMissingEnergy::Phi() const { return m_obj->data.Phi; }


bool  ConstMissingEnergy::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID ConstMissingEnergy::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool ConstMissingEnergy::operator==(const MissingEnergy& other) const {
     return (m_obj==other.m_obj);
}

//bool operator< (const MissingEnergy& p1, const MissingEnergy& p2 ) {
//  if( p1.m_containerID == p2.m_containerID ) {
//    return p1.m_index < p2.m_index;
//  } else {
//    return p1.m_containerID < p2.m_containerID;
//  }
//}


