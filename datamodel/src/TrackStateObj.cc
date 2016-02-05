#include "TrackStateObj.h"


namespace fcc {
TrackStateObj::TrackStateObj() :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    ,data()
    
    { }

TrackStateObj::TrackStateObj(const podio::ObjectID id, TrackStateData data) :
    ObjBase{id,0},
    data(data)
    { }

TrackStateObj::TrackStateObj(const TrackStateObj& other) :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    ,data(other.data)
    
    { }

TrackStateObj::~TrackStateObj() {
  if (id.index == podio::ObjectID::untracked) {

  }
}
} // namespace fcc
