#include "TrackClusterObj.h"


namespace fcc {
TrackClusterObj::TrackClusterObj() :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}, data(), m_hits(new std::vector<::fcc::ConstTrackHit>())
{ }

TrackClusterObj::TrackClusterObj(const podio::ObjectID id, TrackClusterData data) :
    ObjBase{id,0}, data(data)
{ }

TrackClusterObj::TrackClusterObj(const TrackClusterObj& other) :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    , data(other.data), m_hits(new std::vector<::fcc::ConstTrackHit>(*(other.m_hits)))
{

}

TrackClusterObj::~TrackClusterObj() {
  if (id.index == podio::ObjectID::untracked) {
    delete m_hits;

  }

}
} // namespace fcc
