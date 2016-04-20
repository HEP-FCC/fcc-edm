#include "CaloHitObj.h"


namespace fcc {
CaloHitObj::CaloHitObj() :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}, data()
{ }

CaloHitObj::CaloHitObj(const podio::ObjectID id, CaloHitData data) :
    ObjBase{id,0}, data(data)
{ }

CaloHitObj::CaloHitObj(const CaloHitObj& other) :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    , data(other.data)
{ }

CaloHitObj::~CaloHitObj() {
  if (id.index == podio::ObjectID::untracked) {

  }

}
} // namespace fcc
