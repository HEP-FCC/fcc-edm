#ifndef TrackCluster_H
#define TrackCluster_H
#include "BareCluster.h"
#include "TrackClusterData.h"
#include <vector>
#include "podio/ObjectID.h"

// A track cluster, made of TrackHits
// author: C. Bernet, B. Hegner

//forward declarations


#include "TrackClusterConst.h"
#include "TrackClusterObj.h"

namespace fcc {

class TrackClusterCollection;
class TrackClusterCollectionIterator;
class ConstTrackCluster;

class TrackCluster {

  friend TrackClusterCollection;
  friend TrackClusterCollectionIterator;
  friend ConstTrackCluster;

public:

  /// default constructor
  TrackCluster();
  TrackCluster(fcc::BareCluster Core);

  /// constructor from existing TrackClusterObj
  TrackCluster(TrackClusterObj* obj);
  /// copy constructor
  TrackCluster(const TrackCluster& other);
  /// copy-assignment operator
  TrackCluster& operator=(const TrackCluster& other);
  /// support cloning (deep-copy)
  TrackCluster clone() const;
  /// destructor
  ~TrackCluster();

  /// conversion to const object
  operator ConstTrackCluster () const;

public:

  const fcc::BareCluster& Core() const;

  fcc::BareCluster& Core();
  void Core(class fcc::BareCluster value);



  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from TrackClusterObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const TrackCluster& other) const {
    return (m_obj==other.m_obj);
  }

  bool operator==(const ConstTrackCluster& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const TrackCluster& p1,
//       const TrackCluster& p2 );
  bool operator<(const TrackCluster& other) const { return m_obj < other.m_obj  ; }

  const podio::ObjectID getObjectID() const;

private:
  TrackClusterObj* m_obj;

};

} // namespace fcc

#endif
