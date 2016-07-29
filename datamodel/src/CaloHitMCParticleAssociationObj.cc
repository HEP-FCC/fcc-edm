#include "CaloHitMCParticleAssociationObj.h"
#include "CaloHitConst.h"
#include "MCParticleConst.h"


namespace fcc {
CaloHitMCParticleAssociationObj::CaloHitMCParticleAssociationObj() :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}, data(), m_hit(nullptr)
, m_particle(nullptr)

{ }

CaloHitMCParticleAssociationObj::CaloHitMCParticleAssociationObj(const podio::ObjectID id, CaloHitMCParticleAssociationData data) :
    ObjBase{id,0}, data(data)
{ }

CaloHitMCParticleAssociationObj::CaloHitMCParticleAssociationObj(const CaloHitMCParticleAssociationObj& other) :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    , data(other.data), m_hit(nullptr), m_particle(nullptr)
{
  if (other.m_hit != nullptr) {
     m_hit = new ::fcc::ConstCaloHit(*(other.m_hit));
  }
  if (other.m_particle != nullptr) {
     m_particle = new ::fcc::ConstMCParticle(*(other.m_particle));
  }

}

CaloHitMCParticleAssociationObj::~CaloHitMCParticleAssociationObj() {
  if (id.index == podio::ObjectID::untracked) {

  }
    if (m_hit != nullptr) delete m_hit;
    if (m_particle != nullptr) delete m_particle;

}
} // namespace fcc
