#ifndef CaloHitAssociationOBJ_H
#define CaloHitAssociationOBJ_H

// std includes
#include <atomic>
#include <iostream>

// data model specific includes
#include "podio/ObjBase.h"
#include "CaloHitAssociationData.h"



// forward declarations
class CaloHitAssociation;
class ConstCaloHitAssociation;
namespace fcc {class ConstCaloHit;
class ConstCaloHit;
}


namespace fcc {
class CaloHitAssociationObj : public podio::ObjBase {
public:
  /// constructor
  CaloHitAssociationObj();
  /// copy constructor (does a deep-copy of relation containers)
  CaloHitAssociationObj(const CaloHitAssociationObj&);
  /// constructor from ObjectID and CaloHitAssociationData
  /// does not initialize the internal relation containers
  CaloHitAssociationObj(const podio::ObjectID id, CaloHitAssociationData data);
  virtual ~CaloHitAssociationObj();

public:
  CaloHitAssociationData data;
  ::fcc::ConstCaloHit* m_rec;
  ::fcc::ConstCaloHit* m_sim;


};
} // namespace fcc


#endif
