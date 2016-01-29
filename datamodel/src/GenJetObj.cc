#include "GenJetObj.h"


namespace fcc {
GenJetObj::GenJetObj() :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    ,data()
    
    { }

GenJetObj::GenJetObj(const podio::ObjectID id, GenJetData data) :
    ObjBase{id,0},
    data(data)
    { }

GenJetObj::GenJetObj(const GenJetObj& other) :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    ,data(other.data)
    
    { }

GenJetObj::~GenJetObj() {
  if (id.index == podio::ObjectID::untracked) {

  }
}
} // namespace fcc
