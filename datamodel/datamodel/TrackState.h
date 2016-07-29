#ifndef TrackState_H
#define TrackState_H
#include "TrackStateData.h"
#include <vector>
#include "podio/ObjectID.h"

//forward declarations


#include "TrackStateConst.h"
#include "TrackStateObj.h"

namespace fcc {

class TrackStateCollection;
class TrackStateCollectionIterator;
class ConstTrackState;

/** @class TrackState
 *  Track state at a given point on the track.
 *  @author: C. Bernet, B. Hegner
 */
class TrackState {

  friend TrackStateCollection;
  friend TrackStateCollectionIterator;
  friend ConstTrackState;

public:

  /// default constructor
  TrackState();
  TrackState(float location,float omega,float d0,float z0);

  /// constructor from existing TrackStateObj
  TrackState(TrackStateObj* obj);
  /// copy constructor
  TrackState(const TrackState& other);
  /// copy-assignment operator
  TrackState& operator=(const TrackState& other);
  /// support cloning (deep-copy)
  TrackState clone() const;
  /// destructor
  ~TrackState();

  /// conversion to const object
  operator ConstTrackState () const;

public:

  /// Access the  Location on the track. (Radius?)
  const float& location() const;
  /// Access the  Track curvature in cm.
  const float& omega() const;
  /// Access the  Transverse impact parameter
  const float& d0() const;
  /// Access the  Longitudinal impact parameter
  const float& z0() const;

  /// Set the  Location on the track. (Radius?)
  void location(float value);

  /// Set the  Track curvature in cm.
  void omega(float value);

  /// Set the  Transverse impact parameter
  void d0(float value);

  /// Set the  Longitudinal impact parameter
  void z0(float value);




  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from TrackStateObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const TrackState& other) const {
    return (m_obj==other.m_obj);
  }

  bool operator==(const ConstTrackState& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const TrackState& p1,
//       const TrackState& p2 );
  bool operator<(const TrackState& other) const { return m_obj < other.m_obj  ; }

  const podio::ObjectID getObjectID() const;

private:
  TrackStateObj* m_obj;

};

} // namespace fcc

#endif
