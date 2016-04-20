#ifndef ConstTrackClusterAssociation_H
#define ConstTrackClusterAssociation_H
#include "TrackClusterAssociationData.h"
#include <vector>
#include "podio/ObjectID.h"

// Association between a track and a track cluster
// author: C. Bernet, B. Hegner

//forward declarations
namespace fcc {
class Track;
class ConstTrack;
class TrackCluster;
class ConstTrackCluster;
}


#include "TrackClusterAssociationObj.h"

namespace fcc {

class TrackClusterAssociationObj;
class TrackClusterAssociation;
class TrackClusterAssociationCollection;
class TrackClusterAssociationCollectionIterator;

class ConstTrackClusterAssociation {

  friend TrackClusterAssociation;
  friend TrackClusterAssociationCollection;
  friend TrackClusterAssociationCollectionIterator;

public:

  /// default constructor
  ConstTrackClusterAssociation();
  
  /// constructor from existing TrackClusterAssociationObj
  ConstTrackClusterAssociation(TrackClusterAssociationObj* obj);
  /// copy constructor
  ConstTrackClusterAssociation(const ConstTrackClusterAssociation& other);
  /// copy-assignment operator
  ConstTrackClusterAssociation& operator=(const ConstTrackClusterAssociation& other);
  /// support cloning (deep-copy)
  ConstTrackClusterAssociation clone() const;
  /// destructor
  ~ConstTrackClusterAssociation();


public:

  const fcc::ConstTrack Track() const;
  const fcc::ConstTrackCluster Cluster() const;



  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from TrackClusterAssociationObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const ConstTrackClusterAssociation& other) const {
       return (m_obj==other.m_obj);
  }

  bool operator==(const TrackClusterAssociation& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const TrackClusterAssociation& p1,
//       const TrackClusterAssociation& p2 );

  const podio::ObjectID getObjectID() const;

private:
  TrackClusterAssociationObj* m_obj;

};
} // namespace fcc

#endif
