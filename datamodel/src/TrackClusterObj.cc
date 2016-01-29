#include "TrackClusterObj.h"


namespace fcc {
TrackClusterObj::TrackClusterObj() :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    ,data()
    
    { }

TrackClusterObj::TrackClusterObj(const podio::ObjectID id, TrackClusterData data) :
    ObjBase{id,0},
    data(data)
    { }

TrackClusterObj::TrackClusterObj(const TrackClusterObj& other) :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    ,data(other.data)
    
    { }

TrackClusterObj::~TrackClusterObj() {
  if (id.index == podio::ObjectID::untracked) {

  }
}
} // namespace fcc
