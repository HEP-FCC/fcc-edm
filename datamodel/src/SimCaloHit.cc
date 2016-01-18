// datamodel specific includes
#include "SimCaloHit.h"
#include "SimCaloHitConst.h"
#include "SimCaloHitObj.h"
#include "SimCaloHitData.h"
#include "SimCaloHitCollection.h"
#include <iostream>




SimCaloHit::SimCaloHit() : m_obj(new SimCaloHitObj()){
 m_obj->acquire();
}

SimCaloHit::SimCaloHit(BareHit Core) : m_obj(new SimCaloHitObj()){
 m_obj->acquire();
   m_obj->data.Core = Core;
}


SimCaloHit::SimCaloHit(const SimCaloHit& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

SimCaloHit& SimCaloHit::operator=(const SimCaloHit& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

SimCaloHit::SimCaloHit(SimCaloHitObj* obj) : m_obj(obj){
  if(m_obj != nullptr)
    m_obj->acquire();
}

SimCaloHit SimCaloHit::clone() const {
  return {new SimCaloHitObj(*m_obj)};
}

SimCaloHit::~SimCaloHit(){
  if ( m_obj != nullptr) m_obj->release();
}

SimCaloHit::operator ConstSimCaloHit() const {return ConstSimCaloHit(m_obj);}

  const BareHit& SimCaloHit::Core() const { return m_obj->data.Core; }

  BareHit& SimCaloHit::Core() { return m_obj->data.Core; }
void SimCaloHit::Core(class BareHit value){ m_obj->data.Core = value;}


bool  SimCaloHit::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID SimCaloHit::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool SimCaloHit::operator==(const ConstSimCaloHit& other) const {
     return (m_obj==other.m_obj);
}


//bool operator< (const SimCaloHit& p1, const SimCaloHit& p2 ) {
//  if( p1.m_containerID == p2.m_containerID ) {
//    return p1.m_index < p2.m_index;
//  } else {
//    return p1.m_containerID < p2.m_containerID;
//  }
//}


