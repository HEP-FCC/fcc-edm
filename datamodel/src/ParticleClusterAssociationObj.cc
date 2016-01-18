#include "ParticleClusterAssociationObj.h"
#include "ParticleConst.h"
#include "CaloClusterConst.h"



ParticleClusterAssociationObj::ParticleClusterAssociationObj() :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    ,data()
    ,m_Particle(nullptr)
,m_Cluster(nullptr)

    { }

ParticleClusterAssociationObj::ParticleClusterAssociationObj(const podio::ObjectID id, ParticleClusterAssociationData data) :
    ObjBase{id,0},
    data(data)
    { }

ParticleClusterAssociationObj::ParticleClusterAssociationObj(const ParticleClusterAssociationObj& other) :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    ,data(other.data)
    
    { }

ParticleClusterAssociationObj::~ParticleClusterAssociationObj() {
  if (id.index == podio::ObjectID::untracked) {
delete m_Particle;
delete m_Cluster;

  }
}

