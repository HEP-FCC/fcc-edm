#include "SimCaloClusterObj.h"



SimCaloClusterObj::SimCaloClusterObj() :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    ,data()
    
    { }

SimCaloClusterObj::SimCaloClusterObj(const podio::ObjectID id, SimCaloClusterData data) :
    ObjBase{id,0},
    data(data)
    { }

SimCaloClusterObj::SimCaloClusterObj(const SimCaloClusterObj& other) :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    ,data(other.data)
    
    { }

SimCaloClusterObj::~SimCaloClusterObj() {
  if (id.index == podio::ObjectID::untracked) {

  }
}

