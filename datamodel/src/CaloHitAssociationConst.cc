// datamodel specific includes
#include "CaloHitAssociation.h"
#include "CaloHitAssociationConst.h"
#include "CaloHitAssociationObj.h"
#include "CaloHitAssociationData.h"
#include "CaloHitAssociationCollection.h"
#include <iostream>
#include "CaloHit.h"
#include "CaloHit.h"


namespace fcc {

ConstCaloHitAssociation::ConstCaloHitAssociation() : m_obj(new CaloHitAssociationObj()) {
 m_obj->acquire();
}



ConstCaloHitAssociation::ConstCaloHitAssociation(const ConstCaloHitAssociation& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

ConstCaloHitAssociation& ConstCaloHitAssociation::operator=(const ConstCaloHitAssociation& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

ConstCaloHitAssociation::ConstCaloHitAssociation(CaloHitAssociationObj* obj) : m_obj(obj) {
  if(m_obj != nullptr)
    m_obj->acquire();
}

ConstCaloHitAssociation ConstCaloHitAssociation::clone() const {
  return {new CaloHitAssociationObj(*m_obj)};
}

ConstCaloHitAssociation::~ConstCaloHitAssociation(){
  if ( m_obj != nullptr) m_obj->release();
}

  /// Access the  The reconstruted hit.
  const fcc::ConstCaloHit ConstCaloHitAssociation::rec() const {
    if (m_obj->m_rec == nullptr) {
      return fcc::ConstCaloHit(nullptr);
    }
    return fcc::ConstCaloHit(*(m_obj->m_rec));} /// Access the  The simulated hit.
  const fcc::ConstCaloHit ConstCaloHitAssociation::sim() const {
    if (m_obj->m_sim == nullptr) {
      return fcc::ConstCaloHit(nullptr);
    }
    return fcc::ConstCaloHit(*(m_obj->m_sim));}


bool  ConstCaloHitAssociation::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID ConstCaloHitAssociation::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool ConstCaloHitAssociation::operator==(const CaloHitAssociation& other) const {
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
