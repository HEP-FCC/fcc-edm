#ifndef ConstTrackState_H
#define ConstTrackState_H
#include "TrackStateData.h"
#include <vector>
#include "podio/ObjectID.h"

// Track state at a given point on the track.
// author: C. Bernet, B. Hegner

//forward declarations


#include "TrackStateObj.h"

namespace fcc {

class TrackStateObj;
class TrackState;
class TrackStateCollection;
class TrackStateCollectionIterator;

class ConstTrackState {

  friend TrackState;
  friend TrackStateCollection;
  friend TrackStateCollectionIterator;

public:

  /// default constructor
  ConstTrackState();
  ConstTrackState(float Location,float Omega,float D0,float Z0);

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

  const float& Location() const;
  const float& Omega() const;
  const float& D0() const;
  const float& Z0() const;



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

  const podio::ObjectID getObjectID() const;

private:
  TrackStateObj* m_obj;

};
} // namespace fcc

#endif
