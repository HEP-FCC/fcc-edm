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

Vertex::Vertex(float chi2,unsigned ndf,fcc::Point position,unsigned bits) : m_obj(new VertexObj()) {
  m_obj->acquire();
    m_obj->data.chi2 = chi2;  m_obj->data.ndf = ndf;  m_obj->data.position = position;  m_obj->data.bits = bits;
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

  const float& Vertex::chi2() const { return m_obj->data.chi2; }
  const unsigned& Vertex::ndf() const { return m_obj->data.ndf; }
  const fcc::Point& Vertex::position() const { return m_obj->data.position; }
const float& Vertex::x() const { return m_obj->data.position.x; }
const float& Vertex::y() const { return m_obj->data.position.y; }
const float& Vertex::z() const { return m_obj->data.position.z; }
  const unsigned& Vertex::bits() const { return m_obj->data.bits; }

void Vertex::chi2(float value){ m_obj->data.chi2 = value; }
void Vertex::ndf(unsigned value){ m_obj->data.ndf = value; }
  fcc::Point& Vertex::position() { return m_obj->data.position; }
void Vertex::position(class fcc::Point value) { m_obj->data.position = value; }
void Vertex::x(float value){ m_obj->data.position.x = value; }
void Vertex::y(float value){ m_obj->data.position.y = value; }
void Vertex::z(float value){ m_obj->data.position.z = value; }
void Vertex::bits(unsigned value){ m_obj->data.bits = value; }

std::vector<fcc::ConstWeightedTrack>::const_iterator Vertex::tracks_begin() const {
  auto ret_value = m_obj->m_tracks->begin();
  std::advance(ret_value, m_obj->data.tracks_begin);
  return ret_value;
}

std::vector<fcc::ConstWeightedTrack>::const_iterator Vertex::tracks_end() const {
  auto ret_value = m_obj->m_tracks->begin();
//fg: this code fails if m_obj->data.tracks==0
//  std::advance(ret_value, m_obj->data.tracks_end-1);
//  return ++ret_value;
  std::advance(ret_value, m_obj->data.tracks_end);
  return ret_value;
}

void Vertex::addtracks(fcc::ConstWeightedTrack component) {
  m_obj->m_tracks->push_back(component);
  m_obj->data.tracks_end++;
}

unsigned int Vertex::tracks_size() const {
  return (m_obj->data.tracks_end-m_obj->data.tracks_begin);
}

fcc::ConstWeightedTrack Vertex::tracks(unsigned int index) const {
  if (tracks_size() > index) {
    return m_obj->m_tracks->at(m_obj->data.tracks_begin+index);
  }
  else throw std::out_of_range ("index out of bounds for existing references");
}


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
