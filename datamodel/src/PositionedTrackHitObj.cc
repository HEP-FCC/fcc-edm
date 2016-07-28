#include "PositionedTrackHitObj.h"


namespace fcc {
PositionedTrackHitObj::PositionedTrackHitObj() :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}, data()
{ }

PositionedTrackHitObj::PositionedTrackHitObj(const podio::ObjectID id, PositionedTrackHitData data) :
    ObjBase{id,0}, data(data)
{ }

PositionedTrackHitObj::PositionedTrackHitObj(const PositionedTrackHitObj& other) :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    , data(other.data)
{

}

PositionedTrackHitObj::~PositionedTrackHitObj() {
  if (id.index == podio::ObjectID::untracked) {

  }

}
} // namespace fcc
