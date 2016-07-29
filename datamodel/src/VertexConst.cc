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

ConstVertex::ConstVertex(float chi2,unsigned ndf,fcc::Point position,unsigned bits) : m_obj(new VertexObj()){
 m_obj->acquire();
   m_obj->data.chi2 = chi2;  m_obj->data.ndf = ndf;  m_obj->data.position = position;  m_obj->data.bits = bits;
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

  /// Access the  chi2 returned by the vertex fit
  const float& ConstVertex::chi2() const { return m_obj->data.chi2; }
  /// Access the  Number of degrees of freedom of the vertex fit
  const unsigned& ConstVertex::ndf() const { return m_obj->data.ndf; }
  const float& ConstVertex::x() const { return m_obj->data.position.x; }
  const float& ConstVertex::y() const { return m_obj->data.position.y; }
  const float& ConstVertex::z() const { return m_obj->data.position.z; }
  /// Access the  Vertex position in cm
  const fcc::Point& ConstVertex::position() const { return m_obj->data.position; }
  /// Access the  Stored flags
  const unsigned& ConstVertex::bits() const { return m_obj->data.bits; }

std::vector<fcc::ConstWeightedTrack>::const_iterator ConstVertex::tracks_begin() const {
  auto ret_value = m_obj->m_tracks->begin();
  std::advance(ret_value, m_obj->data.tracks_begin);
  return ret_value;
}

std::vector<fcc::ConstWeightedTrack>::const_iterator ConstVertex::tracks_end() const {
  auto ret_value = m_obj->m_tracks->begin();
  std::advance(ret_value, m_obj->data.tracks_end-1);
  return ++ret_value;
}

unsigned int ConstVertex::tracks_size() const {
  return (m_obj->data.tracks_end-m_obj->data.tracks_begin);
}

fcc::ConstWeightedTrack ConstVertex::tracks(unsigned int index) const {
  if (tracks_size() > index) {
    return m_obj->m_tracks->at(m_obj->data.tracks_begin+index);
  }
  else throw std::out_of_range ("index out of bounds for existing references");
}


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
