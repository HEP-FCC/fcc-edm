// datamodel specific includes
#include "VertexTrackAssociation.h"
#include "VertexTrackAssociationConst.h"
#include "VertexTrackAssociationObj.h"
#include "VertexTrackAssociationData.h"
#include "VertexTrackAssociationCollection.h"
#include <iostream>
#include "Track.h"
#include "Vertex.h"




VertexTrackAssociation::VertexTrackAssociation() : m_obj(new VertexTrackAssociationObj()){
 m_obj->acquire();
}

VertexTrackAssociation::VertexTrackAssociation(float Weight) : m_obj(new VertexTrackAssociationObj()){
 m_obj->acquire();
   m_obj->data.Weight = Weight;
}


VertexTrackAssociation::VertexTrackAssociation(const VertexTrackAssociation& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

VertexTrackAssociation& VertexTrackAssociation::operator=(const VertexTrackAssociation& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

VertexTrackAssociation::VertexTrackAssociation(VertexTrackAssociationObj* obj) : m_obj(obj){
  if(m_obj != nullptr)
    m_obj->acquire();
}

VertexTrackAssociation VertexTrackAssociation::clone() const {
  return {new VertexTrackAssociationObj(*m_obj)};
}

VertexTrackAssociation::~VertexTrackAssociation(){
  if ( m_obj != nullptr) m_obj->release();
}

VertexTrackAssociation::operator ConstVertexTrackAssociation() const {return ConstVertexTrackAssociation(m_obj);}

  const float& VertexTrackAssociation::Weight() const { return m_obj->data.Weight; }
  const ConstTrack VertexTrackAssociation::Track() const { if (m_obj->m_Track == nullptr) {
 return ConstTrack(nullptr);}
 return ConstTrack(*(m_obj->m_Track));}
  const ConstVertex VertexTrackAssociation::Vertex() const { if (m_obj->m_Vertex == nullptr) {
 return ConstVertex(nullptr);}
 return ConstVertex(*(m_obj->m_Vertex));}

void VertexTrackAssociation::Weight(float value){ m_obj->data.Weight = value;}
void VertexTrackAssociation::Track(ConstTrack value) { if (m_obj->m_Track != nullptr) delete m_obj->m_Track; m_obj->m_Track = new ConstTrack(value); }
void VertexTrackAssociation::Vertex(ConstVertex value) { if (m_obj->m_Vertex != nullptr) delete m_obj->m_Vertex; m_obj->m_Vertex = new ConstVertex(value); }


bool  VertexTrackAssociation::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID VertexTrackAssociation::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool VertexTrackAssociation::operator==(const ConstVertexTrackAssociation& other) const {
     return (m_obj==other.m_obj);
}


//bool operator< (const VertexTrackAssociation& p1, const VertexTrackAssociation& p2 ) {
//  if( p1.m_containerID == p2.m_containerID ) {
//    return p1.m_index < p2.m_index;
//  } else {
//    return p1.m_containerID < p2.m_containerID;
//  }
//}


