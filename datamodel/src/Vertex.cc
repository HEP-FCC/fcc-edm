// datamodel specific includes
#include "Vertex.h"
#include "VertexConst.h"
#include "VertexObj.h"
#include "VertexData.h"
#include "VertexCollection.h"
#include <iostream>


namespace fcc {

Vertex::Vertex() : m_obj(new VertexObj()){
 m_obj->acquire();
}

Vertex::Vertex(float Chi2,unsigned Ndf,fcc::Point Position,unsigned Bits) : m_obj(new VertexObj()) {
  m_obj->acquire();
    m_obj->data.Chi2 = Chi2;  m_obj->data.Ndf = Ndf;  m_obj->data.Position = Position;  m_obj->data.Bits = Bits;
}


Vertex::Vertex(const Vertex& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

Vertex& Vertex::operator=(const Vertex& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

Vertex::Vertex(VertexObj* obj) : m_obj(obj){
  if(m_obj != nullptr)
    m_obj->acquire();
}

Vertex Vertex::clone() const {
  return {new VertexObj(*m_obj)};
}

Vertex::~Vertex(){
  if ( m_obj != nullptr) m_obj->release();
}

Vertex::operator ConstVertex() const {return ConstVertex(m_obj);}

  const float& Vertex::Chi2() const { return m_obj->data.Chi2; }
  const unsigned& Vertex::Ndf() const { return m_obj->data.Ndf; }
  const fcc::Point& Vertex::Position() const { return m_obj->data.Position; }
  const unsigned& Vertex::Bits() const { return m_obj->data.Bits; }

void Vertex::Chi2(float value){ m_obj->data.Chi2 = value; }
void Vertex::Ndf(unsigned value){ m_obj->data.Ndf = value; }
  fcc::Point& Vertex::Position() { return m_obj->data.Position; }
void Vertex::Position(class fcc::Point value) { m_obj->data.Position = value; }
void Vertex::Bits(unsigned value){ m_obj->data.Bits = value; }



bool  Vertex::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID Vertex::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool Vertex::operator==(const ConstVertex& other) const {
  return (m_obj==other.m_obj);
}


//bool operator< (const Vertex& p1, const Vertex& p2 ) {
//  if( p1.m_containerID == p2.m_containerID ) {
//    return p1.m_index < p2.m_index;
//  } else {
//    return p1.m_containerID < p2.m_containerID;
//  }
//}

} // namespace fcc
