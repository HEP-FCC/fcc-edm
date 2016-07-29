#ifndef ConstTrackState_H
#define ConstTrackState_H
#include "TrackStateData.h"
#include <vector>
#include "podio/ObjectID.h"

//forward declarations


#include "TrackStateObj.h"

namespace fcc {

class TrackStateObj;
class TrackState;
class TrackStateCollection;
class TrackStateCollectionIterator;

/** @class ConstTrackState
 *  Track state at a given point on the track.
 *  @author: C. Bernet, B. Hegner
 */

class ConstTrackState {

  friend TrackState;
  friend TrackStateCollection;
  friend TrackStateCollectionIterator;

public:

  /// default constructor
  ConstTrackState();
  ConstTrackState(float location,float omega,float d0,float z0);

  /// constructor from existing TrackStateObj
  ConstTrackState(TrackStateObj* obj);
  /// copy constructor
  ConstTrackState(const ConstTrackState& other);
  /// copy-assignment operator
  ConstTrackState& operator=(const ConstTrackState& other);
  /// support cloning (deep-copy)
  ConstTrackState clone() const;
  /// destructor
  ~ConstTrackState();


public:

  /// Access the  Location on the track. (Radius?)
  const float& location() const;
  /// Access the  Track curvature in cm.
  const float& omega() const;
  /// Access the  Transverse impact parameter
  const float& d0() const;
  /// Access the  Longitudinal impact parameter
  const float& z0() const;



  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from TrackStateObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const ConstTrackState& other) const {
       return (m_obj==other.m_obj);
  }

  bool operator==(const TrackState& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const TrackState& p1,
//       const TrackState& p2 );
  bool operator<(const ConstTrackState& other) const { return m_obj < other.m_obj  ; }

  const podio::ObjectID getObjectID() const;

private:
  TrackStateObj* m_obj;

};
} // namespace fcc

#endif
