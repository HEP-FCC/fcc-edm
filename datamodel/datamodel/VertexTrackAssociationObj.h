#ifndef VertexTrackAssociationOBJ_H
#define VertexTrackAssociationOBJ_H

// std includes
#include <atomic>
#include <iostream>

// data model specific includes
#include "podio/ObjBase.h"
#include "VertexTrackAssociationData.h"



// forward declarations
class VertexTrackAssociation;
class ConstVertexTrackAssociation;
namespace fcc {class ConstTrack;
class ConstVertex;
}


namespace fcc {
class VertexTrackAssociationObj : public podio::ObjBase {
public:
  /// constructor
  VertexTrackAssociationObj();
  /// copy constructor (does a deep-copy of relation containers)
  VertexTrackAssociationObj(const VertexTrackAssociationObj&);
  /// constructor from ObjectID and VertexTrackAssociationData
  /// does not initialize the internal relation containers
  VertexTrackAssociationObj(const podio::ObjectID id, VertexTrackAssociationData data);
  virtual ~VertexTrackAssociationObj();

public:
  VertexTrackAssociationData data;
  ::fcc::ConstTrack* m_Track;
  ::fcc::ConstVertex* m_Vertex;


};
} // namespace fcc


#endif
