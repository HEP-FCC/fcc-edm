#include "ParticleMCParticleAssociationObj.h"
#include "ParticleConst.h"
#include "MCParticleConst.h"


namespace fcc {
ParticleMCParticleAssociationObj::ParticleMCParticleAssociationObj() :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}, data(), m_rec(nullptr)
, m_sim(nullptr)

{ }

ParticleMCParticleAssociationObj::ParticleMCParticleAssociationObj(const podio::ObjectID id, ParticleMCParticleAssociationData data) :
    ObjBase{id,0}, data(data)
{ }

ParticleMCParticleAssociationObj::ParticleMCParticleAssociationObj(const ParticleMCParticleAssociationObj& other) :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    , data(other.data), m_rec(nullptr), m_sim(nullptr)
{
  if (other.m_rec != nullptr) {
     m_rec = new ::fcc::ConstParticle(*(other.m_rec));
  }
  if (other.m_sim != nullptr) {
     m_sim = new ::fcc::ConstMCParticle(*(other.m_sim));
  }

}

ParticleMCParticleAssociationObj::~ParticleMCParticleAssociationObj() {
  if (id.index == podio::ObjectID::untracked) {

  }
    if (m_rec != nullptr) delete m_rec;
    if (m_sim != nullptr) delete m_sim;

}
} // namespace fcc
