#include "VertexTrackAssociationObj.h"
#include "TrackConst.h"
#include "VertexConst.h"


namespace fcc {
VertexTrackAssociationObj::VertexTrackAssociationObj() :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    ,data()
    ,m_Track(nullptr)
,m_Vertex(nullptr)

    { }

VertexTrackAssociationObj::VertexTrackAssociationObj(const podio::ObjectID id, VertexTrackAssociationData data) :
    ObjBase{id,0},
    data(data)
    { }

VertexTrackAssociationObj::VertexTrackAssociationObj(const VertexTrackAssociationObj& other) :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    ,data(other.data)
    
    { }

VertexTrackAssociationObj::~VertexTrackAssociationObj() {
  if (id.index == podio::ObjectID::untracked) {
delete m_Track;
delete m_Vertex;

  }
}
} // namespace fcc
