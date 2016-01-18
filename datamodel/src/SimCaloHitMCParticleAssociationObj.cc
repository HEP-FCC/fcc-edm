#include "SimCaloHitMCParticleAssociationObj.h"
#include "SimCaloHitConst.h"
#include "MCParticleConst.h"



SimCaloHitMCParticleAssociationObj::SimCaloHitMCParticleAssociationObj() :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    ,data()
    ,m_Hit(nullptr)
,m_Particle(nullptr)

    { }

SimCaloHitMCParticleAssociationObj::SimCaloHitMCParticleAssociationObj(const podio::ObjectID id, SimCaloHitMCParticleAssociationData data) :
    ObjBase{id,0},
    data(data)
    { }

SimCaloHitMCParticleAssociationObj::SimCaloHitMCParticleAssociationObj(const SimCaloHitMCParticleAssociationObj& other) :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    ,data(other.data)
    
    { }

SimCaloHitMCParticleAssociationObj::~SimCaloHitMCParticleAssociationObj() {
  if (id.index == podio::ObjectID::untracked) {
delete m_Hit;
delete m_Particle;

  }
}

