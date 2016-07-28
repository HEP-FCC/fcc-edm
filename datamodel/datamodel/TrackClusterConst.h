#ifndef ConstTrackCluster_H
#define ConstTrackCluster_H
#include "BareCluster.h"
#include "TrackClusterData.h"
#include <vector>
#include "TrackHit.h"
#include <vector>
#include "podio/ObjectID.h"

//forward declarations


#include "TrackClusterObj.h"

namespace fcc {

class TrackClusterObj;
class TrackCluster;
class TrackClusterCollection;
class TrackClusterCollectionIterator;

/** @class ConstTrackCluster
 *  A track cluster, made of TrackHits
 *  @author: C. Bernet, B. Hegner, J. Lingemann
 */

class ConstTrackCluster {

  friend TrackCluster;
  friend TrackClusterCollection;
  friend TrackClusterCollectionIterator;

public:

  /// default constructor
  ConstTrackCluster();
  ConstTrackCluster(fcc::BareCluster core);

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

  /// Access the  contains basic cluster information
  const fcc::BareCluster& core() const;
  /// Access the member of  contains basic cluster information
  const unsigned& bits() const;
  /// Access the member of  contains basic cluster information
  const float& energy() const;
  /// Access the member of  contains basic cluster information
  const ::fcc::Point& position() const;
  /// Access the member of  contains basic cluster information
  const float& time() const;

  unsigned int hits_size() const;
  fcc::ConstTrackHit hits(unsigned int) const;
  std::vector<fcc::ConstTrackHit>::const_iterator hits_begin() const;
  std::vector<fcc::ConstTrackHit>::const_iterator hits_end() const;


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
