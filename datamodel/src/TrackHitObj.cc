#include "TrackHitObj.h"


namespace fcc {
TrackHitObj::TrackHitObj() :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    ,data()
    
    { }

TrackHitObj::TrackHitObj(const podio::ObjectID id, TrackHitData data) :
    ObjBase{id,0},
    data(data)
    { }

TrackHitObj::TrackHitObj(const TrackHitObj& other) :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    ,data(other.data)
    
    { }

TrackHitObj::~TrackHitObj() {
  if (id.index == podio::ObjectID::untracked) {

  }
}
} // namespace fcc
