#ifndef TrackClusterHitsAssociationOBJ_H
#define TrackClusterHitsAssociationOBJ_H

// std includes
#include <atomic>
#include <iostream>

// data model specific includes
#include "podio/ObjBase.h"
#include "TrackClusterHitsAssociationData.h"



// forward declarations
class TrackClusterHitsAssociation;
class ConstTrackClusterHitsAssociation;
namespace fcc {class ConstTrackCluster;
class ConstTrackHit;
}


namespace fcc {
class TrackClusterHitsAssociationObj : public podio::ObjBase {
public:
  /// constructor
  TrackClusterHitsAssociationObj();
  /// copy constructor (does a deep-copy of relation containers)
  TrackClusterHitsAssociationObj(const TrackClusterHitsAssociationObj&);
  /// constructor from ObjectID and TrackClusterHitsAssociationData
  /// does not initialize the internal relation containers
  TrackClusterHitsAssociationObj(const podio::ObjectID id, TrackClusterHitsAssociationData data);
  virtual ~TrackClusterHitsAssociationObj();

public:
  TrackClusterHitsAssociationData data;
  ::fcc::ConstTrackCluster* m_Cluster;
  ::fcc::ConstTrackHit* m_Hit;


};
} // namespace fcc


#endif
