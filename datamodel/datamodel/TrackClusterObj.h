#ifndef TrackClusterOBJ_H
#define TrackClusterOBJ_H

// std includes
#include <atomic>
#include <iostream>

// data model specific includes
#include "podio/ObjBase.h"
#include "TrackClusterData.h"



// forward declarations
class TrackCluster;
class ConstTrackCluster;



class TrackClusterObj : public podio::ObjBase {
public:
  /// constructor
  TrackClusterObj();
  /// copy constructor (does a deep-copy of relation containers)
  TrackClusterObj(const TrackClusterObj&);
  /// constructor from ObjectID and TrackClusterData
  /// does not initialize the internal relation containers
  TrackClusterObj(const podio::ObjectID id, TrackClusterData data);
  virtual ~TrackClusterObj();

public:
  TrackClusterData data;


};



#endif
