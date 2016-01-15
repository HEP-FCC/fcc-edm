#ifndef TrackStateOBJ_H
#define TrackStateOBJ_H

// std includes
#include <atomic>
#include <iostream>

// data model specific includes
#include "podio/ObjBase.h"
#include "TrackStateData.h"



// forward declarations
class TrackState;
class ConstTrackState;



class TrackStateObj : public podio::ObjBase {
public:
  /// constructor
  TrackStateObj();
  /// copy constructor (does a deep-copy of relation containers)
  TrackStateObj(const TrackStateObj&);
  /// constructor from ObjectID and TrackStateData
  /// does not initialize the internal relation containers
  TrackStateObj(const podio::ObjectID id, TrackStateData data);
  virtual ~TrackStateObj();

public:
  TrackStateData data;


};



#endif
