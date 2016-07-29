#include "ParticleObj.h"


namespace fcc {
ParticleObj::ParticleObj() :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}, data(), m_tracks(new std::vector<::fcc::ConstTrack>()), m_clusters(new std::vector<::fcc::ConstCaloCluster>())
{ }

ParticleObj::ParticleObj(const podio::ObjectID id, ParticleData data) :
    ObjBase{id,0}, data(data)
{ }

ParticleObj::ParticleObj(const ParticleObj& other) :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    , data(other.data), m_tracks(new std::vector<::fcc::ConstTrack>(*(other.m_tracks))), m_clusters(new std::vector<::fcc::ConstCaloCluster>(*(other.m_clusters)))
{

}

ParticleObj::~ParticleObj() {
  if (id.index == podio::ObjectID::untracked) {
    delete m_tracks;
    delete m_clusters;

  }

}
} // namespace fcc
