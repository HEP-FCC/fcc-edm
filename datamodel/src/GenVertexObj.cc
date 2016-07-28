#include "GenVertexObj.h"


namespace fcc {
GenVertexObj::GenVertexObj() :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}, data()
{ }

GenVertexObj::GenVertexObj(const podio::ObjectID id, GenVertexData data) :
    ObjBase{id,0}, data(data)
{ }

GenVertexObj::GenVertexObj(const GenVertexObj& other) :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    , data(other.data)
{

}

GenVertexObj::~GenVertexObj() {
  if (id.index == podio::ObjectID::untracked) {

  }

}
} // namespace fcc
