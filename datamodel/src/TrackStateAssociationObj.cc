#include "TrackStateAssociationObj.h"
#include "TrackConst.h"
#include "TrackStateConst.h"


namespace fcc {
TrackStateAssociationObj::TrackStateAssociationObj() :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    ,data()
    ,m_Track(nullptr)
,m_State(nullptr)

    { }

TrackStateAssociationObj::TrackStateAssociationObj(const podio::ObjectID id, TrackStateAssociationData data) :
    ObjBase{id,0},
    data(data)
    { }

TrackStateAssociationObj::TrackStateAssociationObj(const TrackStateAssociationObj& other) :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    ,data(other.data)
    
    { }

TrackStateAssociationObj::~TrackStateAssociationObj() {
  if (id.index == podio::ObjectID::untracked) {
delete m_Track;
delete m_State;

  }
}
} // namespace fcc
