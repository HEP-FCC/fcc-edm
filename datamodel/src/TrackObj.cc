#include "TrackObj.h"



TrackObj::TrackObj() :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    ,data()
    
    { }

TrackObj::TrackObj(const podio::ObjectID id, TrackData data) :
    ObjBase{id,0},
    data(data)
    { }

TrackObj::TrackObj(const TrackObj& other) :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    ,data(other.data)
    
    { }

TrackObj::~TrackObj() {
  if (id.index == podio::ObjectID::untracked) {

  }
}

