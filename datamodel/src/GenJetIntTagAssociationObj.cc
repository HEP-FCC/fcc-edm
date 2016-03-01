#include "GenJetIntTagAssociationObj.h"
#include "GenJetConst.h"
#include "IntTagConst.h"


namespace fcc {
GenJetIntTagAssociationObj::GenJetIntTagAssociationObj() :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    ,data()
    ,m_Jet(nullptr)
,m_Tag(nullptr)

    { }

GenJetIntTagAssociationObj::GenJetIntTagAssociationObj(const podio::ObjectID id, GenJetIntTagAssociationData data) :
    ObjBase{id,0},
    data(data)
    { }

GenJetIntTagAssociationObj::GenJetIntTagAssociationObj(const GenJetIntTagAssociationObj& other) :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    ,data(other.data)
    
    { }

GenJetIntTagAssociationObj::~GenJetIntTagAssociationObj() {
  if (id.index == podio::ObjectID::untracked) {
delete m_Jet;
delete m_Tag;

  }
}
} // namespace fcc
