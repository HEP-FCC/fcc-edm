#include "TrackClusterHitsAssociationObj.h"
#include "TrackClusterConst.h"
#include "TrackHitConst.h"


namespace fcc {
TrackClusterHitsAssociationObj::TrackClusterHitsAssociationObj() :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}, data(),m_Cluster(nullptr)
,m_Hit(nullptr)

{ }

TrackClusterHitsAssociationObj::TrackClusterHitsAssociationObj(const podio::ObjectID id, TrackClusterHitsAssociationData data) :
    ObjBase{id,0}, data(data)
{ }

TrackClusterHitsAssociationObj::TrackClusterHitsAssociationObj(const TrackClusterHitsAssociationObj& other) :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    , data(other.data)
{ }

TrackClusterHitsAssociationObj::~TrackClusterHitsAssociationObj() {
  if (id.index == podio::ObjectID::untracked) {

  }
    if (m_Cluster != nullptr) delete m_Cluster;
    if (m_Hit != nullptr) delete m_Hit;

}
} // namespace fcc
