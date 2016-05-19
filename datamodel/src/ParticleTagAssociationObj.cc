#include "ParticleTagAssociationObj.h"
#include "ParticleConst.h"
#include "TagConst.h"


namespace fcc {
ParticleTagAssociationObj::ParticleTagAssociationObj() :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}, data(),m_Particle(nullptr)
,m_Tag(nullptr)

{ }

ParticleTagAssociationObj::ParticleTagAssociationObj(const podio::ObjectID id, ParticleTagAssociationData data) :
    ObjBase{id,0}, data(data)
{ }

ParticleTagAssociationObj::ParticleTagAssociationObj(const ParticleTagAssociationObj& other) :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    , data(other.data)
{ }

ParticleTagAssociationObj::~ParticleTagAssociationObj() {
  if (id.index == podio::ObjectID::untracked) {

  }
    if (m_Particle != nullptr) delete m_Particle;
    if (m_Tag != nullptr) delete m_Tag;

}
} // namespace fcc
