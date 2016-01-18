#ifndef VertexTrackAssociation_H
#define VertexTrackAssociation_H
#include "VertexTrackAssociationData.h"

#include <vector>
#include "podio/ObjectID.h"

//  Weight of the track in the vertex.
// author: C. Bernet, B. Hegner

//forward declarations
class Track;
class ConstTrack;
class Vertex;
class ConstVertex;


#include "VertexTrackAssociationConst.h"
#include "VertexTrackAssociationObj.h"



class VertexTrackAssociationCollection;
class VertexTrackAssociationCollectionIterator;
class ConstVertexTrackAssociation;

class VertexTrackAssociation {

  friend VertexTrackAssociationCollection;
  friend VertexTrackAssociationCollectionIterator;
  friend ConstVertexTrackAssociation;

public:

  /// default constructor
  VertexTrackAssociation();
    VertexTrackAssociation(float Weight);

  /// constructor from existing VertexTrackAssociationObj
  VertexTrackAssociation(VertexTrackAssociationObj* obj);
  /// copy constructor
  VertexTrackAssociation(const VertexTrackAssociation& other);
  /// copy-assignment operator
  VertexTrackAssociation& operator=(const VertexTrackAssociation& other);
  /// support cloning (deep-copy)
  VertexTrackAssociation clone() const;
  /// destructor
  ~VertexTrackAssociation();

  /// conversion to const object
  operator ConstVertexTrackAssociation () const;

public:

  const float& Weight() const;
  const ConstTrack Track() const;
  const ConstVertex Vertex() const;

  void Weight(float value);
  void Track(ConstTrack value);
  void Vertex(ConstVertex value);


  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from VertexTrackAssociationObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const VertexTrackAssociation& other) const {
       return (m_obj==other.m_obj);
  }

  bool operator==(const ConstVertexTrackAssociation& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const VertexTrackAssociation& p1,
//       const VertexTrackAssociation& p2 );

  const podio::ObjectID getObjectID() const;

private:
  VertexTrackAssociationObj* m_obj;

};



#endif
