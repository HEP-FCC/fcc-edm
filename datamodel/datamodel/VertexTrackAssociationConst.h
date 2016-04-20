#ifndef ConstVertexTrackAssociation_H
#define ConstVertexTrackAssociation_H
#include "VertexTrackAssociationData.h"
#include <vector>
#include "podio/ObjectID.h"

// Association between a track and a vertex, with a weight
// author: C. Bernet, B. Hegner

//forward declarations
namespace fcc {
class Track;
class ConstTrack;
class Vertex;
class ConstVertex;
}


#include "VertexTrackAssociationObj.h"

namespace fcc {

class VertexTrackAssociationObj;
class VertexTrackAssociation;
class VertexTrackAssociationCollection;
class VertexTrackAssociationCollectionIterator;

class ConstVertexTrackAssociation {

  friend VertexTrackAssociation;
  friend VertexTrackAssociationCollection;
  friend VertexTrackAssociationCollectionIterator;

public:

  /// default constructor
  ConstVertexTrackAssociation();
  ConstVertexTrackAssociation(float Weight);

  /// constructor from existing VertexTrackAssociationObj
  ConstVertexTrackAssociation(VertexTrackAssociationObj* obj);
  /// copy constructor
  ConstVertexTrackAssociation(const ConstVertexTrackAssociation& other);
  /// copy-assignment operator
  ConstVertexTrackAssociation& operator=(const ConstVertexTrackAssociation& other);
  /// support cloning (deep-copy)
  ConstVertexTrackAssociation clone() const;
  /// destructor
  ~ConstVertexTrackAssociation();


public:

  const float& Weight() const;
  const fcc::ConstTrack Track() const;
  const fcc::ConstVertex Vertex() const;



  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from VertexTrackAssociationObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const ConstVertexTrackAssociation& other) const {
       return (m_obj==other.m_obj);
  }

  bool operator==(const VertexTrackAssociation& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const VertexTrackAssociation& p1,
//       const VertexTrackAssociation& p2 );

  const podio::ObjectID getObjectID() const;

private:
  VertexTrackAssociationObj* m_obj;

};
} // namespace fcc

#endif
