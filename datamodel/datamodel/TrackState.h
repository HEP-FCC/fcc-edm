#ifndef TrackState_H
#define TrackState_H
#include "TrackStateData.h"
#include <vector>
#include "podio/ObjectID.h"

// Track state at a given point on the track.
// author: C. Bernet, B. Hegner

//forward declarations


#include "TrackStateConst.h"
#include "TrackStateObj.h"

namespace fcc {

class TrackStateCollection;
class TrackStateCollectionIterator;
class ConstTrackState;

class TrackState {

  friend TrackStateCollection;
  friend TrackStateCollectionIterator;
  friend ConstTrackState;

public:

  /// default constructor
  TrackState();
  TrackState(float Location,float Omega,float D0,float Z0);

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

  const float& Location() const;
  const float& Omega() const;
  const float& D0() const;
  const float& Z0() const;

  void Location(float value);

  void Omega(float value);

  void D0(float value);

  void Z0(float value);




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
