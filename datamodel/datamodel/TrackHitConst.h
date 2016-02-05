#ifndef ConstTrackHit_H
#define ConstTrackHit_H
#include "TrackHitData.h"
#include "BareHit.h"

#include <vector>
#include "podio/ObjectID.h"

//  contains basic hit information
// author: C. Bernet, B. Hegner

//forward declarations


#include "TrackHitObj.h"

namespace fcc {

class TrackHitObj;
class TrackHit;
class TrackHitCollection;
class TrackHitCollectionIterator;

class ConstTrackHit {

  friend TrackHit;
  friend TrackHitCollection;
  friend TrackHitCollectionIterator;

public:

  /// default constructor
  ConstTrackHit();
  ConstTrackHit(fcc::BareHit Core);

  /// constructor from existing TrackHitObj
  ConstTrackHit(TrackHitObj* obj);
  /// copy constructor
  ConstTrackHit(const ConstTrackHit& other);
  /// copy-assignment operator
  ConstTrackHit& operator=(const ConstTrackHit& other);
  /// support cloning (deep-copy)
  ConstTrackHit clone() const;
  /// destructor
  ~ConstTrackHit();


public:

  const fcc::BareHit& Core() const;


  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from TrackHitObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const ConstTrackHit& other) const {
       return (m_obj==other.m_obj);
  }

  bool operator==(const TrackHit& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const TrackHit& p1,
//       const TrackHit& p2 );

  const podio::ObjectID getObjectID() const;

private:
  TrackHitObj* m_obj;

};
} // namespace fcc

#endif
