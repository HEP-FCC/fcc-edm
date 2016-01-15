#include "CaloClusterObj.h"



CaloClusterObj::CaloClusterObj() :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    ,data()
    
    { }

CaloClusterObj::CaloClusterObj(const podio::ObjectID id, CaloClusterData data) :
    ObjBase{id,0},
    data(data)
    { }

CaloClusterObj::CaloClusterObj(const CaloClusterObj& other) :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    ,data(other.data)
    
    { }

CaloClusterObj::~CaloClusterObj() {
  if (id.index == podio::ObjectID::untracked) {

  }
}

