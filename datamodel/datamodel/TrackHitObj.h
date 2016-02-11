#ifndef TrackHitOBJ_H
#define TrackHitOBJ_H

// std includes
#include <atomic>
#include <iostream>

// data model specific includes
#include "podio/ObjBase.h"
#include "TrackHitData.h"



// forward declarations
class TrackHit;
class ConstTrackHit;


namespace fcc {
class TrackHitObj : public podio::ObjBase {
public:
  /// constructor
  TrackHitObj();
  /// copy constructor (does a deep-copy of relation containers)
  TrackHitObj(const TrackHitObj&);
  /// constructor from ObjectID and TrackHitData
  /// does not initialize the internal relation containers
  TrackHitObj(const podio::ObjectID id, TrackHitData data);
  virtual ~TrackHitObj();

public:
  TrackHitData data;


};
} // namespace fcc


#endif
