// datamodel specific includes
#include "GenVertex.h"
#include "GenVertexConst.h"
#include "GenVertexObj.h"
#include "GenVertexData.h"
#include "GenVertexCollection.h"
#include <iostream>


namespace fcc {

ConstGenVertex::ConstGenVertex() : m_obj(new GenVertexObj()){
 m_obj->acquire();
}

ConstGenVertex::ConstGenVertex(fcc::Point Position,float Ctau) : m_obj(new GenVertexObj()){
 m_obj->acquire();
   m_obj->data.Position = Position;  m_obj->data.Ctau = Ctau;
}


ConstGenVertex::ConstGenVertex(const ConstGenVertex& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

ConstGenVertex& ConstGenVertex::operator=(const ConstGenVertex& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

ConstGenVertex::ConstGenVertex(GenVertexObj* obj) : m_obj(obj){
  if(m_obj != nullptr)
    m_obj->acquire();
}

ConstGenVertex ConstGenVertex::clone() const {
  return {new GenVertexObj(*m_obj)};
}

ConstGenVertex::~ConstGenVertex(){
  if ( m_obj != nullptr) m_obj->release();
}

  const fcc::Point& ConstGenVertex::Position() const { return m_obj->data.Position; }
  const float& ConstGenVertex::Ctau() const { return m_obj->data.Ctau; }


bool  ConstGenVertex::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID ConstGenVertex::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool ConstGenVertex::operator==(const GenVertex& other) const {
     return (m_obj==other.m_obj);
}

//bool operator< (const GenVertex& p1, const GenVertex& p2 ) {
//  if( p1.m_containerID == p2.m_containerID ) {
//    return p1.m_index < p2.m_index;
//  } else {
//    return p1.m_containerID < p2.m_containerID;
//  }
//}

} // namespace fcc
