#include "PositionedCaloHitObj.h"


namespace fcc {
PositionedCaloHitObj::PositionedCaloHitObj() :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}, data()
{ }

PositionedCaloHitObj::PositionedCaloHitObj(const podio::ObjectID id, PositionedCaloHitData data) :
    ObjBase{id,0}, data(data)
{ }

PositionedCaloHitObj::PositionedCaloHitObj(const PositionedCaloHitObj& other) :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    , data(other.data)
{

}

PositionedCaloHitObj::~PositionedCaloHitObj() {
  if (id.index == podio::ObjectID::untracked) {

  }

}
} // namespace fcc
