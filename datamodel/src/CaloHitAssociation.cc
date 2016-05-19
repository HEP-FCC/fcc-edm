// datamodel specific includes
#include "CaloHitAssociation.h"
#include "CaloHitAssociationConst.h"
#include "CaloHitAssociationObj.h"
#include "CaloHitAssociationData.h"
#include "CaloHitAssociationCollection.h"
#include <iostream>
#include "CaloHit.h"
#include "SimCaloHit.h"


namespace fcc {

CaloHitAssociation::CaloHitAssociation() : m_obj(new CaloHitAssociationObj()){
 m_obj->acquire();
}



CaloHitAssociation::CaloHitAssociation(const CaloHitAssociation& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

CaloHitAssociation& CaloHitAssociation::operator=(const CaloHitAssociation& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

CaloHitAssociation::CaloHitAssociation(CaloHitAssociationObj* obj) : m_obj(obj){
  if(m_obj != nullptr)
    m_obj->acquire();
}

CaloHitAssociation CaloHitAssociation::clone() const {
  return {new CaloHitAssociationObj(*m_obj)};
}

CaloHitAssociation::~CaloHitAssociation(){
  if ( m_obj != nullptr) m_obj->release();
}

CaloHitAssociation::operator ConstCaloHitAssociation() const {return ConstCaloHitAssociation(m_obj);}

  const fcc::ConstCaloHit CaloHitAssociation::Rec() const {
    if (m_obj->m_Rec == nullptr) {
      return fcc::ConstCaloHit(nullptr);
    }
    return fcc::ConstCaloHit(*(m_obj->m_Rec));
  } const fcc::ConstSimCaloHit CaloHitAssociation::Sim() const {
    if (m_obj->m_Sim == nullptr) {
      return fcc::ConstSimCaloHit(nullptr);
    }
    return fcc::ConstSimCaloHit(*(m_obj->m_Sim));
  }
void CaloHitAssociation::Rec(fcc::ConstCaloHit value) {
  if (m_obj->m_Rec != nullptr) delete m_obj->m_Rec;
  m_obj->m_Rec = new ConstCaloHit(value);
}
void CaloHitAssociation::Sim(fcc::ConstSimCaloHit value) {
  if (m_obj->m_Sim != nullptr) delete m_obj->m_Sim;
  m_obj->m_Sim = new ConstSimCaloHit(value);
}



bool  CaloHitAssociation::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID CaloHitAssociation::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool CaloHitAssociation::operator==(const ConstCaloHitAssociation& other) const {
  return (m_obj==other.m_obj);
}


//bool operator< (const CaloHitAssociation& p1, const CaloHitAssociation& p2 ) {
//  if( p1.m_containerID == p2.m_containerID ) {
//    return p1.m_index < p2.m_index;
//  } else {
//    return p1.m_containerID < p2.m_containerID;
//  }
//}

} // namespace fcc
