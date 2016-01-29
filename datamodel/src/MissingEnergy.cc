// datamodel specific includes
#include "MissingEnergy.h"
#include "MissingEnergyConst.h"
#include "MissingEnergyObj.h"
#include "MissingEnergyData.h"
#include "MissingEnergyCollection.h"
#include <iostream>


namespace fcc {

MissingEnergy::MissingEnergy() : m_obj(new MissingEnergyObj()){
 m_obj->acquire();
}

MissingEnergy::MissingEnergy(float Energy,float Phi) : m_obj(new MissingEnergyObj()){
 m_obj->acquire();
   m_obj->data.Energy = Energy;  m_obj->data.Phi = Phi;
}


MissingEnergy::MissingEnergy(const MissingEnergy& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

MissingEnergy& MissingEnergy::operator=(const MissingEnergy& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

MissingEnergy::MissingEnergy(MissingEnergyObj* obj) : m_obj(obj){
  if(m_obj != nullptr)
    m_obj->acquire();
}

MissingEnergy MissingEnergy::clone() const {
  return {new MissingEnergyObj(*m_obj)};
}

MissingEnergy::~MissingEnergy(){
  if ( m_obj != nullptr) m_obj->release();
}

MissingEnergy::operator ConstMissingEnergy() const {return ConstMissingEnergy(m_obj);}

  const float& MissingEnergy::Energy() const { return m_obj->data.Energy; }
  const float& MissingEnergy::Phi() const { return m_obj->data.Phi; }

void MissingEnergy::Energy(float value){ m_obj->data.Energy = value;}
void MissingEnergy::Phi(float value){ m_obj->data.Phi = value;}


bool  MissingEnergy::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID MissingEnergy::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool MissingEnergy::operator==(const ConstMissingEnergy& other) const {
     return (m_obj==other.m_obj);
}


//bool operator< (const MissingEnergy& p1, const MissingEnergy& p2 ) {
//  if( p1.m_containerID == p2.m_containerID ) {
//    return p1.m_index < p2.m_index;
//  } else {
//    return p1.m_containerID < p2.m_containerID;
//  }
//}

} // namespace fcc
