#ifndef TrackHit_H
#define TrackHit_H
#include "BareHit.h"
#include "TrackHitData.h"
#include <vector>
#include "podio/ObjectID.h"

//forward declarations


#include "TrackHitConst.h"
#include "TrackHitObj.h"

namespace fcc {

class TrackHitCollection;
class TrackHitCollectionIterator;
class ConstTrackHit;

/** @class TrackHit
 *  A tracker hit
 *  @author: C. Bernet, B. Hegner
 */
class TrackHit {

  friend TrackHitCollection;
  friend TrackHitCollectionIterator;
  friend ConstTrackHit;

public:

  /// default constructor
  TrackHit();
  TrackHit(fcc::BareHit core);

  /// constructor from existing TrackHitObj
  TrackHit(TrackHitObj* obj);
  /// copy constructor
  TrackHit(const TrackHit& other);
  /// copy-assignment operator
  TrackHit& operator=(const TrackHit& other);
  /// support cloning (deep-copy)
  TrackHit clone() const;
  /// destructor
  ~TrackHit();

  /// conversion to const object
  operator ConstTrackHit () const;

public:

  /// Access the  contains basic hit information
  const fcc::BareHit& core() const;
  /// Access the member of  contains basic hit information
  const unsigned& bits() const;
  /// Access the member of  contains basic hit information
  const ulonglong& cellId() const;
  /// Access the member of  contains basic hit information
  const float& energy() const;
  /// Access the member of  contains basic hit information
  const float& time() const;

  /// Get reference to the  contains basic hit information
  fcc::BareHit& core();
  /// Set the  contains basic hit information
  void core(class fcc::BareHit value);
  /// Set the  member of  contains basic hit information
  void bits(unsigned value);

  /// Set the  member of  contains basic hit information
  void cellId(ulonglong value);

  /// Set the  member of  contains basic hit information
  void energy(float value);

  /// Set the  member of  contains basic hit information
  void time(float value);




  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from TrackHitObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const TrackHit& other) const {
    return (m_obj==other.m_obj);
  }

  bool operator==(const ConstTrackHit& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const TrackHit& p1,
//       const TrackHit& p2 );
  bool operator<(const TrackHit& other) const { return m_obj < other.m_obj  ; }

  const podio::ObjectID getObjectID() const;

private:
  TrackHitObj* m_obj;

};

} // namespace fcc

#endif
