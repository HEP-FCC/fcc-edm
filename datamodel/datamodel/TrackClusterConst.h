#ifndef ConstTrackCluster_H
#define ConstTrackCluster_H
#include "BareCluster.h"
#include "TrackClusterData.h"
#include <vector>
#include "podio/ObjectID.h"

// A track cluster, made of TrackHits
// author: C. Bernet, B. Hegner

//forward declarations


#include "TrackClusterObj.h"

namespace fcc {

class TrackClusterObj;
class TrackCluster;
class TrackClusterCollection;
class TrackClusterCollectionIterator;

class ConstTrackCluster {

  friend TrackCluster;
  friend TrackClusterCollection;
  friend TrackClusterCollectionIterator;

public:

  /// default constructor
  ConstTrackCluster();
  ConstTrackCluster(fcc::BareCluster Core);

  /// constructor from existing TrackClusterObj
  ConstTrackCluster(TrackClusterObj* obj);
  /// copy constructor
  ConstTrackCluster(const ConstTrackCluster& other);
  /// copy-assignment operator
  ConstTrackCluster& operator=(const ConstTrackCluster& other);
  /// support cloning (deep-copy)
  ConstTrackCluster clone() const;
  /// destructor
  ~ConstTrackCluster();


public:

  const fcc::BareCluster& Core() const;



  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from TrackClusterObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const ConstTrackCluster& other) const {
       return (m_obj==other.m_obj);
  }

  bool operator==(const TrackCluster& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const TrackCluster& p1,
//       const TrackCluster& p2 );
  bool operator<(const ConstTrackCluster& other) const { return m_obj < other.m_obj  ; }

  const podio::ObjectID getObjectID() const;

private:
  TrackClusterObj* m_obj;

};
} // namespace fcc

#endif
