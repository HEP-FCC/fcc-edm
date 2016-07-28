#ifndef PositionedCaloHitOBJ_H
#define PositionedCaloHitOBJ_H

// std includes
#include <atomic>
#include <iostream>

// data model specific includes
#include "podio/ObjBase.h"
#include "PositionedCaloHitData.h"



// forward declarations
class PositionedCaloHit;
class ConstPositionedCaloHit;


namespace fcc {
class PositionedCaloHitObj : public podio::ObjBase {
public:
  /// constructor
  PositionedCaloHitObj();
  /// copy constructor (does a deep-copy of relation containers)
  PositionedCaloHitObj(const PositionedCaloHitObj&);
  /// constructor from ObjectID and PositionedCaloHitData
  /// does not initialize the internal relation containers
  PositionedCaloHitObj(const podio::ObjectID id, PositionedCaloHitData data);
  virtual ~PositionedCaloHitObj();

public:
  PositionedCaloHitData data;


};
} // namespace fcc


#endif
