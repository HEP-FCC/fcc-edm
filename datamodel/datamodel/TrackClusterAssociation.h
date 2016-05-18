#ifndef TrackClusterAssociation_H
#define TrackClusterAssociation_H
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


#include "TrackClusterAssociationConst.h"
#include "TrackClusterAssociationObj.h"

namespace fcc {

class TrackClusterAssociationCollection;
class TrackClusterAssociationCollectionIterator;
class ConstTrackClusterAssociation;

class TrackClusterAssociation {

  friend TrackClusterAssociationCollection;
  friend TrackClusterAssociationCollectionIterator;
  friend ConstTrackClusterAssociation;

public:

  /// default constructor
  TrackClusterAssociation();

  /// constructor from existing TrackClusterAssociationObj
  TrackClusterAssociation(TrackClusterAssociationObj* obj);
  /// copy constructor
  TrackClusterAssociation(const TrackClusterAssociation& other);
  /// copy-assignment operator
  TrackClusterAssociation& operator=(const TrackClusterAssociation& other);
  /// support cloning (deep-copy)
  TrackClusterAssociation clone() const;
  /// destructor
  ~TrackClusterAssociation();

  /// conversion to const object
  operator ConstTrackClusterAssociation () const;

public:

  const fcc::ConstTrack Track() const;
  const fcc::ConstTrackCluster Cluster() const;

  void Track(fcc::ConstTrack value);
  void Cluster(fcc::ConstTrackCluster value);



  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from TrackClusterAssociationObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const TrackClusterAssociation& other) const {
    return (m_obj==other.m_obj);
  }

  bool operator==(const ConstTrackClusterAssociation& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const TrackClusterAssociation& p1,
//       const TrackClusterAssociation& p2 );
  bool operator<(const TrackClusterAssociation& other) const { return m_obj < other.m_obj  ; }

  const podio::ObjectID getObjectID() const;

private:
  TrackClusterAssociationObj* m_obj;

};

} // namespace fcc

#endif
