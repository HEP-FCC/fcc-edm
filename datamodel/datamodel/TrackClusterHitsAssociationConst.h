#ifndef ConstTrackClusterHitsAssociation_H
#define ConstTrackClusterHitsAssociation_H
#include "TrackClusterHitsAssociationData.h"
#include <vector>
#include "podio/ObjectID.h"

// Association between a track cluster and a track hit
// author: C. Bernet, B. Hegner

//forward declarations
namespace fcc {
class TrackCluster;
class ConstTrackCluster;
class TrackHit;
class ConstTrackHit;
}


#include "TrackClusterHitsAssociationObj.h"

namespace fcc {

class TrackClusterHitsAssociationObj;
class TrackClusterHitsAssociation;
class TrackClusterHitsAssociationCollection;
class TrackClusterHitsAssociationCollectionIterator;

class ConstTrackClusterHitsAssociation {

  friend TrackClusterHitsAssociation;
  friend TrackClusterHitsAssociationCollection;
  friend TrackClusterHitsAssociationCollectionIterator;

public:

  /// default constructor
  ConstTrackClusterHitsAssociation();
  
  /// constructor from existing TrackClusterHitsAssociationObj
  ConstTrackClusterHitsAssociation(TrackClusterHitsAssociationObj* obj);
  /// copy constructor
  ConstTrackClusterHitsAssociation(const ConstTrackClusterHitsAssociation& other);
  /// copy-assignment operator
  ConstTrackClusterHitsAssociation& operator=(const ConstTrackClusterHitsAssociation& other);
  /// support cloning (deep-copy)
  ConstTrackClusterHitsAssociation clone() const;
  /// destructor
  ~ConstTrackClusterHitsAssociation();


public:

  const fcc::ConstTrackCluster Cluster() const;
  const fcc::ConstTrackHit Hit() const;



  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from TrackClusterHitsAssociationObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const ConstTrackClusterHitsAssociation& other) const {
       return (m_obj==other.m_obj);
  }

  bool operator==(const TrackClusterHitsAssociation& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const TrackClusterHitsAssociation& p1,
//       const TrackClusterHitsAssociation& p2 );
  bool operator<(const ConstTrackClusterHitsAssociation& other) const { return m_obj < other.m_obj  ; }

  const podio::ObjectID getObjectID() const;

private:
  TrackClusterHitsAssociationObj* m_obj;

};
} // namespace fcc

#endif
