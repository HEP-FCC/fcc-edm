#include "MissingEnergyObj.h"


namespace fcc {
MissingEnergyObj::MissingEnergyObj() :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    ,data()
    
    { }

MissingEnergyObj::MissingEnergyObj(const podio::ObjectID id, MissingEnergyData data) :
    ObjBase{id,0},
    data(data)
    { }

MissingEnergyObj::MissingEnergyObj(const MissingEnergyObj& other) :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    ,data(other.data)
    
    { }

MissingEnergyObj::~MissingEnergyObj() {
  if (id.index == podio::ObjectID::untracked) {

  }
}
} // namespace fcc
