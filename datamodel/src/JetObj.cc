#include "JetObj.h"


namespace fcc {
JetObj::JetObj() :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}, data()
{ }

JetObj::JetObj(const podio::ObjectID id, JetData data) :
    ObjBase{id,0}, data(data)
{ }

JetObj::JetObj(const JetObj& other) :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    , data(other.data)
{ }

JetObj::~JetObj() {
  if (id.index == podio::ObjectID::untracked) {

  }

}
} // namespace fcc
