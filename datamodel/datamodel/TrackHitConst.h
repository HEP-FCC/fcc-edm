#ifndef ConstTrackHit_H
#define ConstTrackHit_H
#include "BareHit.h"
#include "TrackHitData.h"
#include <vector>
#include "podio/ObjectID.h"

//forward declarations


#include "TrackHitObj.h"

namespace fcc {

class TrackHitObj;
class TrackHit;
class TrackHitCollection;
class TrackHitCollectionIterator;

/** @class ConstTrackHit
 *  A tracker hit
 *  @author: C. Bernet, B. Hegner
 */

class ConstTrackHit {

  friend TrackHit;
  friend TrackHitCollection;
  friend TrackHitCollectionIterator;

public:

  /// default constructor
  ConstTrackHit();
  ConstTrackHit(fcc::BareHit core);

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

  /// Access the  contains basic hit information
  const fcc::BareHit& core() const;
  /// Access the member of  contains basic hit information
  const unsigned& bits() const;
  /// Access the member of  contains basic hit information
  const unsigned long long& cellId() const;
  /// Access the member of  contains basic hit information
  const float& energy() const;
  /// Access the member of  contains basic hit information
  const float& time() const;



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
  bool operator<(const ConstTrackHit& other) const { return m_obj < other.m_obj  ; }

  const podio::ObjectID getObjectID() const;

private:
  TrackHitObj* m_obj;

};
} // namespace fcc

#endif
