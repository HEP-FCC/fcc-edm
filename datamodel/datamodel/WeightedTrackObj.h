#ifndef WeightedTrackOBJ_H
#define WeightedTrackOBJ_H

// std includes
#include <atomic>
#include <iostream>

// data model specific includes
#include "podio/ObjBase.h"
#include "WeightedTrackData.h"



// forward declarations
class WeightedTrack;
class ConstWeightedTrack;
namespace fcc {class ConstTrack;
}


namespace fcc {
class WeightedTrackObj : public podio::ObjBase {
public:
  /// constructor
  WeightedTrackObj();
  /// copy constructor (does a deep-copy of relation containers)
  WeightedTrackObj(const WeightedTrackObj&);
  /// constructor from ObjectID and WeightedTrackData
  /// does not initialize the internal relation containers
  WeightedTrackObj(const podio::ObjectID id, WeightedTrackData data);
  virtual ~WeightedTrackObj();

public:
  WeightedTrackData data;
  ::fcc::ConstTrack* m_track;


};
} // namespace fcc


#endif
