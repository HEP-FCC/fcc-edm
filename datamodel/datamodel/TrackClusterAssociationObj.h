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
class ConstTrack;
class ConstTrackCluster;



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
  ConstTrack* m_Track;
  ConstTrackCluster* m_Cluster;


};



#endif
