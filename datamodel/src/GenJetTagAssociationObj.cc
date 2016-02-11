#include "GenJetTagAssociationObj.h"
#include "GenJetConst.h"
#include "TagConst.h"


namespace fcc {
GenJetTagAssociationObj::GenJetTagAssociationObj() :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    ,data()
    ,m_Jet(nullptr)
,m_Tag(nullptr)

    { }

GenJetTagAssociationObj::GenJetTagAssociationObj(const podio::ObjectID id, GenJetTagAssociationData data) :
    ObjBase{id,0},
    data(data)
    { }

GenJetTagAssociationObj::GenJetTagAssociationObj(const GenJetTagAssociationObj& other) :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    ,data(other.data)
    
    { }

GenJetTagAssociationObj::~GenJetTagAssociationObj() {
  if (id.index == podio::ObjectID::untracked) {
delete m_Jet;
delete m_Tag;

  }
}
} // namespace fcc
