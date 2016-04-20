#include "JetIntTagAssociationObj.h"
#include "JetConst.h"
#include "IntTagConst.h"


namespace fcc {
JetIntTagAssociationObj::JetIntTagAssociationObj() :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}, data(),m_Jet(nullptr)
,m_Tag(nullptr)

{ }

JetIntTagAssociationObj::JetIntTagAssociationObj(const podio::ObjectID id, JetIntTagAssociationData data) :
    ObjBase{id,0}, data(data)
{ }

JetIntTagAssociationObj::JetIntTagAssociationObj(const JetIntTagAssociationObj& other) :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    , data(other.data)
{ }

JetIntTagAssociationObj::~JetIntTagAssociationObj() {
  if (id.index == podio::ObjectID::untracked) {

  }
    if (m_Jet != nullptr) delete m_Jet;
    if (m_Tag != nullptr) delete m_Tag;

}
} // namespace fcc
