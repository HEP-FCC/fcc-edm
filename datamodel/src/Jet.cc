// datamodel specific includes
#include "Jet.h"
#include "JetConst.h"
#include "JetObj.h"
#include "JetData.h"
#include "JetCollection.h"
#include <iostream>




Jet::Jet() : m_obj(new JetObj()){
 m_obj->acquire();
}

Jet::Jet(BareJet Core) : m_obj(new JetObj()){
 m_obj->acquire();
   m_obj->data.Core = Core;
}


Jet::Jet(const Jet& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

Jet& Jet::operator=(const Jet& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

Jet::Jet(JetObj* obj) : m_obj(obj){
  if(m_obj != nullptr)
    m_obj->acquire();
}

Jet Jet::clone() const {
  return {new JetObj(*m_obj)};
}

Jet::~Jet(){
  if ( m_obj != nullptr) m_obj->release();
}

Jet::operator ConstJet() const {return ConstJet(m_obj);}

  const BareJet& Jet::Core() const { return m_obj->data.Core; }

  BareJet& Jet::Core() { return m_obj->data.Core; }
void Jet::Core(class BareJet value){ m_obj->data.Core = value;}


bool  Jet::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID Jet::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool Jet::operator==(const ConstJet& other) const {
     return (m_obj==other.m_obj);
}


//bool operator< (const Jet& p1, const Jet& p2 ) {
//  if( p1.m_containerID == p2.m_containerID ) {
//    return p1.m_index < p2.m_index;
//  } else {
//    return p1.m_containerID < p2.m_containerID;
//  }
//}


