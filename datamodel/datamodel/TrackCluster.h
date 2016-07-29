#ifndef TrackCluster_H
#define TrackCluster_H
#include "BareCluster.h"
#include "TrackClusterData.h"
#include <vector>
#include "TrackHit.h"
#include <vector>
#include "podio/ObjectID.h"

//forward declarations


#include "TrackClusterConst.h"
#include "TrackClusterObj.h"

namespace fcc {

class TrackClusterCollection;
class TrackClusterCollectionIterator;
class ConstTrackCluster;

/** @class TrackCluster
 *  A track cluster, made of TrackHits
 *  @author: C. Bernet, B. Hegner, J. Lingemann
 */
class TrackCluster {

  friend TrackClusterCollection;
  friend TrackClusterCollectionIterator;
  friend ConstTrackCluster;

public:

  /// default constructor
  TrackCluster();
  TrackCluster(fcc::BareCluster core);

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

  /// Get reference to the  contains basic cluster information
  fcc::BareCluster& core();
  /// Set the  contains basic cluster information
  void core(class fcc::BareCluster value);
  /// Set the  member of  contains basic cluster information
  void bits(unsigned value);

  /// Set the  member of  contains basic cluster information
  void energy(float value);

  /// Get reference to the member of  contains basic cluster information
  ::fcc::Point& position();
  /// Set the  member of  contains basic cluster information
  void position(class ::fcc::Point value);
  /// Set the  member of  contains basic cluster information
  void time(float value);


  void addhits(fcc::ConstTrackHit);
  unsigned int hits_size() const;
  fcc::ConstTrackHit hits(unsigned int) const;
  std::vector<fcc::ConstTrackHit>::const_iterator hits_begin() const;
  std::vector<fcc::ConstTrackHit>::const_iterator hits_end() const;



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
