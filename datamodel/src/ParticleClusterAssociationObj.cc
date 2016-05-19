#include "ParticleClusterAssociationObj.h"
#include "ParticleConst.h"
#include "CaloClusterConst.h"


namespace fcc {
ParticleClusterAssociationObj::ParticleClusterAssociationObj() :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}, data(),m_Particle(nullptr)
,m_Cluster(nullptr)

{ }

ParticleClusterAssociationObj::ParticleClusterAssociationObj(const podio::ObjectID id, ParticleClusterAssociationData data) :
    ObjBase{id,0}, data(data)
{ }

ParticleClusterAssociationObj::ParticleClusterAssociationObj(const ParticleClusterAssociationObj& other) :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    , data(other.data)
{ }

ParticleClusterAssociationObj::~ParticleClusterAssociationObj() {
  if (id.index == podio::ObjectID::untracked) {

  }
    if (m_Particle != nullptr) delete m_Particle;
    if (m_Cluster != nullptr) delete m_Cluster;

}
} // namespace fcc
