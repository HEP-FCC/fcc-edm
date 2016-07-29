#include "TrackObj.h"


namespace fcc {
TrackObj::TrackObj() :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}, data(), m_clusters(new std::vector<::fcc::ConstTrackCluster>()), m_states(new std::vector<::fcc::ConstTrackState>())
{ }

TrackObj::TrackObj(const podio::ObjectID id, TrackData data) :
    ObjBase{id,0}, data(data)
{ }

TrackObj::TrackObj(const TrackObj& other) :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    , data(other.data), m_clusters(new std::vector<::fcc::ConstTrackCluster>(*(other.m_clusters))), m_states(new std::vector<::fcc::ConstTrackState>(*(other.m_states)))
{

}

TrackObj::~TrackObj() {
  if (id.index == podio::ObjectID::untracked) {
    delete m_clusters;
    delete m_states;

  }

}
} // namespace fcc
