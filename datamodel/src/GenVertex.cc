// datamodel specific includes
#include "GenVertex.h"
#include "GenVertexConst.h"
#include "GenVertexObj.h"
#include "GenVertexData.h"
#include "GenVertexCollection.h"
#include <iostream>


namespace fcc {

GenVertex::GenVertex() : m_obj(new GenVertexObj()){
 m_obj->acquire();
}

GenVertex::GenVertex(fcc::Point position,float ctau) : m_obj(new GenVertexObj()) {
  m_obj->acquire();
    m_obj->data.position = position;  m_obj->data.ctau = ctau;
}


GenVertex::GenVertex(const GenVertex& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

GenVertex& GenVertex::operator=(const GenVertex& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

GenVertex::GenVertex(GenVertexObj* obj) : m_obj(obj){
  if(m_obj != nullptr)
    m_obj->acquire();
}

GenVertex GenVertex::clone() const {
  return {new GenVertexObj(*m_obj)};
}

GenVertex::~GenVertex(){
  if ( m_obj != nullptr) m_obj->release();
}

GenVertex::operator ConstGenVertex() const {return ConstGenVertex(m_obj);}

  const fcc::Point& GenVertex::position() const { return m_obj->data.position; }
const float& GenVertex::x() const { return m_obj->data.position.x; }
const float& GenVertex::y() const { return m_obj->data.position.y; }
const float& GenVertex::z() const { return m_obj->data.position.z; }
  const float& GenVertex::ctau() const { return m_obj->data.ctau; }

  fcc::Point& GenVertex::position() { return m_obj->data.position; }
void GenVertex::position(class fcc::Point value) { m_obj->data.position = value; }
void GenVertex::x(float value){ m_obj->data.position.x = value; }
void GenVertex::y(float value){ m_obj->data.position.y = value; }
void GenVertex::z(float value){ m_obj->data.position.z = value; }
void GenVertex::ctau(float value){ m_obj->data.ctau = value; }



bool  GenVertex::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID GenVertex::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool GenVertex::operator==(const ConstGenVertex& other) const {
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
