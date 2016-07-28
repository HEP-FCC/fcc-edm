#ifndef PositionedTrackHitOBJ_H
#define PositionedTrackHitOBJ_H

// std includes
#include <atomic>
#include <iostream>

// data model specific includes
#include "podio/ObjBase.h"
#include "PositionedTrackHitData.h"



// forward declarations
class PositionedTrackHit;
class ConstPositionedTrackHit;


namespace fcc {
class PositionedTrackHitObj : public podio::ObjBase {
public:
  /// constructor
  PositionedTrackHitObj();
  /// copy constructor (does a deep-copy of relation containers)
  PositionedTrackHitObj(const PositionedTrackHitObj&);
  /// constructor from ObjectID and PositionedTrackHitData
  /// does not initialize the internal relation containers
  PositionedTrackHitObj(const podio::ObjectID id, PositionedTrackHitData data);
  virtual ~PositionedTrackHitObj();

public:
  PositionedTrackHitData data;


};
} // namespace fcc


#endif
