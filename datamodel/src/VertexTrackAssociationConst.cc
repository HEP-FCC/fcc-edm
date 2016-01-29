// datamodel specific includes
#include "VertexTrackAssociation.h"
#include "VertexTrackAssociationConst.h"
#include "VertexTrackAssociationObj.h"
#include "VertexTrackAssociationData.h"
#include "VertexTrackAssociationCollection.h"
#include <iostream>
#include "Track.h"
#include "Vertex.h"


namespace fcc {

ConstVertexTrackAssociation::ConstVertexTrackAssociation() : m_obj(new VertexTrackAssociationObj()){
 m_obj->acquire();
}

ConstVertexTrackAssociation::ConstVertexTrackAssociation(float Weight) : m_obj(new VertexTrackAssociationObj()){
 m_obj->acquire();
   m_obj->data.Weight = Weight;
}


ConstVertexTrackAssociation::ConstVertexTrackAssociation(const ConstVertexTrackAssociation& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

ConstVertexTrackAssociation& ConstVertexTrackAssociation::operator=(const ConstVertexTrackAssociation& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

ConstVertexTrackAssociation::ConstVertexTrackAssociation(VertexTrackAssociationObj* obj) : m_obj(obj){
  if(m_obj != nullptr)
    m_obj->acquire();
}

ConstVertexTrackAssociation ConstVertexTrackAssociation::clone() const {
  return {new VertexTrackAssociationObj(*m_obj)};
}

ConstVertexTrackAssociation::~ConstVertexTrackAssociation(){
  if ( m_obj != nullptr) m_obj->release();
}

  const float& ConstVertexTrackAssociation::Weight() const { return m_obj->data.Weight; }
  const fcc::ConstTrack ConstVertexTrackAssociation::Track() const { if (m_obj->m_Track == nullptr) {
 return fcc::ConstTrack(nullptr);}
 return fcc::ConstTrack(*(m_obj->m_Track));}
  const fcc::ConstVertex ConstVertexTrackAssociation::Vertex() const { if (m_obj->m_Vertex == nullptr) {
 return fcc::ConstVertex(nullptr);}
 return fcc::ConstVertex(*(m_obj->m_Vertex));}


bool  ConstVertexTrackAssociation::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID ConstVertexTrackAssociation::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool ConstVertexTrackAssociation::operator==(const VertexTrackAssociation& other) const {
     return (m_obj==other.m_obj);
}

//bool operator< (const VertexTrackAssociation& p1, const VertexTrackAssociation& p2 ) {
//  if( p1.m_containerID == p2.m_containerID ) {
//    return p1.m_index < p2.m_index;
//  } else {
//    return p1.m_containerID < p2.m_containerID;
//  }
//}

} // namespace fcc
