#ifndef CaloHitOBJ_H
#define CaloHitOBJ_H

// std includes
#include <atomic>
#include <iostream>

// data model specific includes
#include "podio/ObjBase.h"
#include "CaloHitData.h"



// forward declarations
class CaloHit;
class ConstCaloHit;


namespace fcc {
class CaloHitObj : public podio::ObjBase {
public:
  /// constructor
  CaloHitObj();
  /// copy constructor (does a deep-copy of relation containers)
  CaloHitObj(const CaloHitObj&);
  /// constructor from ObjectID and CaloHitData
  /// does not initialize the internal relation containers
  CaloHitObj(const podio::ObjectID id, CaloHitData data);
  virtual ~CaloHitObj();

public:
  CaloHitData data;


};
} // namespace fcc


#endif
