#include "ParticleMCParticleAssociationObj.h"
#include "ParticleConst.h"
#include "MCParticleConst.h"



ParticleMCParticleAssociationObj::ParticleMCParticleAssociationObj() :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    ,data()
    ,m_Rec(nullptr)
,m_Sim(nullptr)

    { }

ParticleMCParticleAssociationObj::ParticleMCParticleAssociationObj(const podio::ObjectID id, ParticleMCParticleAssociationData data) :
    ObjBase{id,0},
    data(data)
    { }

ParticleMCParticleAssociationObj::ParticleMCParticleAssociationObj(const ParticleMCParticleAssociationObj& other) :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    ,data(other.data)
    
    { }

ParticleMCParticleAssociationObj::~ParticleMCParticleAssociationObj() {
  if (id.index == podio::ObjectID::untracked) {
delete m_Rec;
delete m_Sim;

  }
}

