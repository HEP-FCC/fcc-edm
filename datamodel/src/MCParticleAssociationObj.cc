#include "MCParticleAssociationObj.h"
#include "MCParticleConst.h"
#include "MCParticleConst.h"


namespace fcc {
MCParticleAssociationObj::MCParticleAssociationObj() :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}, data(),m_Mother(nullptr)
,m_Daughter(nullptr)

{ }

MCParticleAssociationObj::MCParticleAssociationObj(const podio::ObjectID id, MCParticleAssociationData data) :
    ObjBase{id,0}, data(data)
{ }

MCParticleAssociationObj::MCParticleAssociationObj(const MCParticleAssociationObj& other) :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    , data(other.data)
{ }

MCParticleAssociationObj::~MCParticleAssociationObj() {
  if (id.index == podio::ObjectID::untracked) {

  }
    if (m_Mother != nullptr) delete m_Mother;
    if (m_Daughter != nullptr) delete m_Daughter;

}
} // namespace fcc
