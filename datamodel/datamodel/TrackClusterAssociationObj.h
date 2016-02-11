#ifndef TrackClusterAssociationOBJ_H
#define TrackClusterAssociationOBJ_H

// std includes
#include <atomic>
#include <iostream>

// data model specific includes
#include "podio/ObjBase.h"
#include "TrackClusterAssociationData.h"



// forward declarations
class TrackClusterAssociation;
class ConstTrackClusterAssociation;
namespace fcc {class ConstTrack;
class ConstTrackCluster;
}


namespace fcc {
class TrackClusterAssociationObj : public podio::ObjBase {
public:
  /// constructor
  TrackClusterAssociationObj();
  /// copy constructor (does a deep-copy of relation containers)
  TrackClusterAssociationObj(const TrackClusterAssociationObj&);
  /// constructor from ObjectID and TrackClusterAssociationData
  /// does not initialize the internal relation containers
  TrackClusterAssociationObj(const podio::ObjectID id, TrackClusterAssociationData data);
  virtual ~TrackClusterAssociationObj();

public:
  TrackClusterAssociationData data;
  ::fcc::ConstTrack* m_Track;
  ::fcc::ConstTrackCluster* m_Cluster;


};
} // namespace fcc


#endif
