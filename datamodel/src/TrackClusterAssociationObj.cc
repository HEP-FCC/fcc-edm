#include "TrackClusterAssociationObj.h"
#include "TrackConst.h"
#include "TrackClusterConst.h"


namespace fcc {
TrackClusterAssociationObj::TrackClusterAssociationObj() :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    ,data()
    ,m_Track(nullptr)
,m_Cluster(nullptr)

    { }

TrackClusterAssociationObj::TrackClusterAssociationObj(const podio::ObjectID id, TrackClusterAssociationData data) :
    ObjBase{id,0},
    data(data)
    { }

TrackClusterAssociationObj::TrackClusterAssociationObj(const TrackClusterAssociationObj& other) :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    ,data(other.data)
    
    { }

TrackClusterAssociationObj::~TrackClusterAssociationObj() {
  if (id.index == podio::ObjectID::untracked) {
delete m_Track;
delete m_Cluster;

  }
}
} // namespace fcc
