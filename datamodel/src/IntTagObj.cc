#include "IntTagObj.h"


namespace fcc {
IntTagObj::IntTagObj() :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    ,data()
    
    { }

IntTagObj::IntTagObj(const podio::ObjectID id, IntTagData data) :
    ObjBase{id,0},
    data(data)
    { }

IntTagObj::IntTagObj(const IntTagObj& other) :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    ,data(other.data)
    
    { }

IntTagObj::~IntTagObj() {
  if (id.index == podio::ObjectID::untracked) {

  }
}
} // namespace fcc
