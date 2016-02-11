#include "TagObj.h"


namespace fcc {
TagObj::TagObj() :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    ,data()
    
    { }

TagObj::TagObj(const podio::ObjectID id, TagData data) :
    ObjBase{id,0},
    data(data)
    { }

TagObj::TagObj(const TagObj& other) :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    ,data(other.data)
    
    { }

TagObj::~TagObj() {
  if (id.index == podio::ObjectID::untracked) {

  }
}
} // namespace fcc
