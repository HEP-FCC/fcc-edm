#ifndef TrackOBJ_H
#define TrackOBJ_H

// std includes
#include <atomic>
#include <iostream>

// data model specific includes
#include "podio/ObjBase.h"
#include "TrackData.h"

#include <vector>
#include "TrackCluster.h"
#include "TrackState.h"


// forward declarations
class Track;
class ConstTrack;


namespace fcc {
class TrackObj : public podio::ObjBase {
public:
  /// constructor
  TrackObj();
  /// copy constructor (does a deep-copy of relation containers)
  TrackObj(const TrackObj&);
  /// constructor from ObjectID and TrackData
  /// does not initialize the internal relation containers
  TrackObj(const podio::ObjectID id, TrackData data);
  virtual ~TrackObj();

public:
  TrackData data;
  std::vector<::fcc::ConstTrackCluster>* m_clusters;
  std::vector<::fcc::ConstTrackState>* m_states;


};
} // namespace fcc


#endif
