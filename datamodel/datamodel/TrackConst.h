#ifndef ConstTrack_H
#define ConstTrack_H
#include "TrackData.h"
#include <vector>
#include "TrackCluster.h"
#include "TrackState.h"
#include <vector>
#include "podio/ObjectID.h"

//forward declarations


#include "TrackObj.h"

namespace fcc {

class TrackObj;
class Track;
class TrackCollection;
class TrackCollectionIterator;

/** @class ConstTrack
 *  Track reconstructed from clusters in the inner tracker
 *  @author: C. Bernet, B. Hegner
 */

class ConstTrack {

  friend Track;
  friend TrackCollection;
  friend TrackCollectionIterator;

public:

  /// default constructor
  ConstTrack();
  ConstTrack(float chi2,unsigned ndf,unsigned bits);

  /// constructor from existing TrackObj
  ConstTrack(TrackObj* obj);
  /// copy constructor
  ConstTrack(const ConstTrack& other);
  /// copy-assignment operator
  ConstTrack& operator=(const ConstTrack& other);
  /// support cloning (deep-copy)
  ConstTrack clone() const;
  /// destructor
  ~ConstTrack();


public:

  /// Access the  chi2 returned by the track fit
  const float& chi2() const;
  /// Access the  Number of degrees of freedom of the track fit
  const unsigned& ndf() const;
  /// Access the  Stores flags
  const unsigned& bits() const;

  unsigned int clusters_size() const;
  fcc::ConstTrackCluster clusters(unsigned int) const;
  std::vector<fcc::ConstTrackCluster>::const_iterator clusters_begin() const;
  std::vector<fcc::ConstTrackCluster>::const_iterator clusters_end() const;
  unsigned int states_size() const;
  fcc::ConstTrackState states(unsigned int) const;
  std::vector<fcc::ConstTrackState>::const_iterator states_begin() const;
  std::vector<fcc::ConstTrackState>::const_iterator states_end() const;


  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from TrackObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const ConstTrack& other) const {
       return (m_obj==other.m_obj);
  }

  bool operator==(const Track& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const Track& p1,
//       const Track& p2 );
  bool operator<(const ConstTrack& other) const { return m_obj < other.m_obj  ; }

  const podio::ObjectID getObjectID() const;

private:
  TrackObj* m_obj;

};
} // namespace fcc

#endif
