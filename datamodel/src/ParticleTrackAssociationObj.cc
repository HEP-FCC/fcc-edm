#include "ParticleTrackAssociationObj.h"
#include "ParticleConst.h"
#include "TrackConst.h"


namespace fcc {
ParticleTrackAssociationObj::ParticleTrackAssociationObj() :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    ,data()
    ,m_Particle(nullptr)
,m_Track(nullptr)

    { }

ParticleTrackAssociationObj::ParticleTrackAssociationObj(const podio::ObjectID id, ParticleTrackAssociationData data) :
    ObjBase{id,0},
    data(data)
    { }

ParticleTrackAssociationObj::ParticleTrackAssociationObj(const ParticleTrackAssociationObj& other) :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    ,data(other.data)
    
    { }

ParticleTrackAssociationObj::~ParticleTrackAssociationObj() {
  if (id.index == podio::ObjectID::untracked) {
delete m_Particle;
delete m_Track;

  }
}
} // namespace fcc
