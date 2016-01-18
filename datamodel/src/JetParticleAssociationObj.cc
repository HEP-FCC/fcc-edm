#include "JetParticleAssociationObj.h"
#include "JetConst.h"
#include "ParticleConst.h"



JetParticleAssociationObj::JetParticleAssociationObj() :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    ,data()
    ,m_Jet(nullptr)
,m_Particle(nullptr)

    { }

JetParticleAssociationObj::JetParticleAssociationObj(const podio::ObjectID id, JetParticleAssociationData data) :
    ObjBase{id,0},
    data(data)
    { }

JetParticleAssociationObj::JetParticleAssociationObj(const JetParticleAssociationObj& other) :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    ,data(other.data)
    
    { }

JetParticleAssociationObj::~JetParticleAssociationObj() {
  if (id.index == podio::ObjectID::untracked) {
delete m_Jet;
delete m_Particle;

  }
}

