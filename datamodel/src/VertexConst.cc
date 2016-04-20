// datamodel specific includes
#include "Vertex.h"
#include "VertexConst.h"
#include "VertexObj.h"
#include "VertexData.h"
#include "VertexCollection.h"
#include <iostream>


namespace fcc {

ConstVertex::ConstVertex() : m_obj(new VertexObj()) {
 m_obj->acquire();
}

ConstVertex::ConstVertex(float Chi2,unsigned Ndf,fcc::Point Position,unsigned Bits) : m_obj(new VertexObj()){
 m_obj->acquire();
   m_obj->data.Chi2 = Chi2;  m_obj->data.Ndf = Ndf;  m_obj->data.Position = Position;  m_obj->data.Bits = Bits;
}


ConstVertex::ConstVertex(const ConstVertex& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

ConstVertex& ConstVertex::operator=(const ConstVertex& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

ConstVertex::ConstVertex(VertexObj* obj) : m_obj(obj) {
  if(m_obj != nullptr)
    m_obj->acquire();
}

ConstVertex ConstVertex::clone() const {
  return {new VertexObj(*m_obj)};
}

ConstVertex::~ConstVertex(){
  if ( m_obj != nullptr) m_obj->release();
}

  const float& ConstVertex::Chi2() const { return m_obj->data.Chi2; }
  const unsigned& ConstVertex::Ndf() const { return m_obj->data.Ndf; }
  const fcc::Point& ConstVertex::Position() const { return m_obj->data.Position; }
  const unsigned& ConstVertex::Bits() const { return m_obj->data.Bits; }



bool  ConstVertex::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID ConstVertex::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool ConstVertex::operator==(const Vertex& other) const {
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
