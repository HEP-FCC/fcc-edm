#include "METObj.h"



METObj::METObj() :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    ,data()
    
    { }

METObj::METObj(const podio::ObjectID id, METData data) :
    ObjBase{id,0},
    data(data)
    { }

METObj::METObj(const METObj& other) :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    ,data(other.data)
    
    { }

METObj::~METObj() {
  if (id.index == podio::ObjectID::untracked) {

  }
}

