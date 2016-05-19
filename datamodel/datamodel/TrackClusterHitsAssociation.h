#ifndef TrackClusterHitsAssociation_H
#define TrackClusterHitsAssociation_H
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


#include "TrackClusterHitsAssociationConst.h"
#include "TrackClusterHitsAssociationObj.h"

namespace fcc {

class TrackClusterHitsAssociationCollection;
class TrackClusterHitsAssociationCollectionIterator;
class ConstTrackClusterHitsAssociation;

class TrackClusterHitsAssociation {

  friend TrackClusterHitsAssociationCollection;
  friend TrackClusterHitsAssociationCollectionIterator;
  friend ConstTrackClusterHitsAssociation;

public:

  /// default constructor
  TrackClusterHitsAssociation();

  /// constructor from existing TrackClusterHitsAssociationObj
  TrackClusterHitsAssociation(TrackClusterHitsAssociationObj* obj);
  /// copy constructor
  TrackClusterHitsAssociation(const TrackClusterHitsAssociation& other);
  /// copy-assignment operator
  TrackClusterHitsAssociation& operator=(const TrackClusterHitsAssociation& other);
  /// support cloning (deep-copy)
  TrackClusterHitsAssociation clone() const;
  /// destructor
  ~TrackClusterHitsAssociation();

  /// conversion to const object
  operator ConstTrackClusterHitsAssociation () const;

public:

  const fcc::ConstTrackCluster Cluster() const;
  const fcc::ConstTrackHit Hit() const;

  void Cluster(fcc::ConstTrackCluster value);
  void Hit(fcc::ConstTrackHit value);



  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from TrackClusterHitsAssociationObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const TrackClusterHitsAssociation& other) const {
    return (m_obj==other.m_obj);
  }

  bool operator==(const ConstTrackClusterHitsAssociation& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const TrackClusterHitsAssociation& p1,
//       const TrackClusterHitsAssociation& p2 );
  bool operator<(const TrackClusterHitsAssociation& other) const { return m_obj < other.m_obj  ; }

  const podio::ObjectID getObjectID() const;

private:
  TrackClusterHitsAssociationObj* m_obj;

};

} // namespace fcc

#endif
