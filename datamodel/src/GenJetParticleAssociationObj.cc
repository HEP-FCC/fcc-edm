#include "GenJetParticleAssociationObj.h"
#include "GenJetConst.h"
#include "MCParticleConst.h"


namespace fcc {
GenJetParticleAssociationObj::GenJetParticleAssociationObj() :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    ,data()
    ,m_Jet(nullptr)
,m_Particle(nullptr)

    { }

GenJetParticleAssociationObj::GenJetParticleAssociationObj(const podio::ObjectID id, GenJetParticleAssociationData data) :
    ObjBase{id,0},
    data(data)
    { }

GenJetParticleAssociationObj::GenJetParticleAssociationObj(const GenJetParticleAssociationObj& other) :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    ,data(other.data)
    
    { }

GenJetParticleAssociationObj::~GenJetParticleAssociationObj() {
  if (id.index == podio::ObjectID::untracked) {
delete m_Jet;
delete m_Particle;

  }
}
} // namespace fcc
