#include "JetTagAssociationObj.h"
#include "JetConst.h"
#include "TagConst.h"


namespace fcc {
JetTagAssociationObj::JetTagAssociationObj() :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}, data(),m_Jet(nullptr)
,m_Tag(nullptr)

{ }

JetTagAssociationObj::JetTagAssociationObj(const podio::ObjectID id, JetTagAssociationData data) :
    ObjBase{id,0}, data(data)
{ }

JetTagAssociationObj::JetTagAssociationObj(const JetTagAssociationObj& other) :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    , data(other.data)
{ }

JetTagAssociationObj::~JetTagAssociationObj() {
  if (id.index == podio::ObjectID::untracked) {

  }
    if (m_Jet != nullptr) delete m_Jet;
    if (m_Tag != nullptr) delete m_Tag;

}
} // namespace fcc
