// datamodel specific includes
#include "GenVertex.h"
#include "GenVertexConst.h"
#include "GenVertexObj.h"
#include "GenVertexData.h"
#include "GenVertexCollection.h"
#include <iostream>




GenVertex::GenVertex() : m_obj(new GenVertexObj()){
 m_obj->acquire();
}

GenVertex::GenVertex(Point Position,float Ctau) : m_obj(new GenVertexObj()){
 m_obj->acquire();
   m_obj->data.Position = Position;  m_obj->data.Ctau = Ctau;
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

  const Point& GenVertex::Position() const { return m_obj->data.Position; }
  const float& GenVertex::Ctau() const { return m_obj->data.Ctau; }

  Point& GenVertex::Position() { return m_obj->data.Position; }
void GenVertex::Position(class Point value){ m_obj->data.Position = value;}
void GenVertex::Ctau(float value){ m_obj->data.Ctau = value;}


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


