#include "SimCaloHitObj.h"


namespace fcc {
SimCaloHitObj::SimCaloHitObj() :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}, data()
{ }

SimCaloHitObj::SimCaloHitObj(const podio::ObjectID id, SimCaloHitData data) :
    ObjBase{id,0}, data(data)
{ }

SimCaloHitObj::SimCaloHitObj(const SimCaloHitObj& other) :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    , data(other.data)
{ }

SimCaloHitObj::~SimCaloHitObj() {
  if (id.index == podio::ObjectID::untracked) {

  }

}
} // namespace fcc
