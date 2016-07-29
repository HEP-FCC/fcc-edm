#ifndef Track_H
#define Track_H
#include "TrackData.h"
#include <vector>
#include "TrackCluster.h"
#include "TrackState.h"
#include <vector>
#include "podio/ObjectID.h"

//forward declarations


#include "TrackConst.h"
#include "TrackObj.h"

namespace fcc {

class TrackCollection;
class TrackCollectionIterator;
class ConstTrack;

/** @class Track
 *  Track reconstructed from clusters in the inner tracker
 *  @author: C. Bernet, B. Hegner
 */
class Track {

  friend TrackCollection;
  friend TrackCollectionIterator;
  friend ConstTrack;

public:

  /// default constructor
  Track();
  Track(float chi2,unsigned ndf,unsigned bits);

  /// constructor from existing TrackObj
  Track(TrackObj* obj);
  /// copy constructor
  Track(const Track& other);
  /// copy-assignment operator
  Track& operator=(const Track& other);
  /// support cloning (deep-copy)
  Track clone() const;
  /// destructor
  ~Track();

  /// conversion to const object
  operator ConstTrack () const;

public:

  /// Access the  chi2 returned by the track fit
  const float& chi2() const;
  /// Access the  Number of degrees of freedom of the track fit
  const unsigned& ndf() const;
  /// Access the  Stores flags
  const unsigned& bits() const;

  /// Set the  chi2 returned by the track fit
  void chi2(float value);

  /// Set the  Number of degrees of freedom of the track fit
  void ndf(unsigned value);

  /// Set the  Stores flags
  void bits(unsigned value);


  void addclusters(fcc::ConstTrackCluster);
  unsigned int clusters_size() const;
  fcc::ConstTrackCluster clusters(unsigned int) const;
  std::vector<fcc::ConstTrackCluster>::const_iterator clusters_begin() const;
  std::vector<fcc::ConstTrackCluster>::const_iterator clusters_end() const;

  void addstates(fcc::ConstTrackState);
  unsigned int states_size() const;
  fcc::ConstTrackState states(unsigned int) const;
  std::vector<fcc::ConstTrackState>::const_iterator states_begin() const;
  std::vector<fcc::ConstTrackState>::const_iterator states_end() const;



  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from TrackObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const Track& other) const {
    return (m_obj==other.m_obj);
  }

  bool operator==(const ConstTrack& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const Track& p1,
//       const Track& p2 );
  bool operator<(const Track& other) const { return m_obj < other.m_obj  ; }

  const podio::ObjectID getObjectID() const;

private:
  TrackObj* m_obj;

};

} // namespace fcc

#endif
