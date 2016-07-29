#ifndef ConstPositionedTrackHit_H
#define ConstPositionedTrackHit_H
#include "Point.h"
#include "BareHit.h"
#include "PositionedTrackHitData.h"
#include <vector>
#include "podio/ObjectID.h"

//forward declarations


#include "PositionedTrackHitObj.h"

namespace fcc {

class PositionedTrackHitObj;
class PositionedTrackHit;
class PositionedTrackHitCollection;
class PositionedTrackHitCollectionIterator;

/** @class ConstPositionedTrackHit
 *  A track hit and with its global position
 *  @author: J. Lingemann, B. Hegner
 */

class ConstPositionedTrackHit {

  friend PositionedTrackHit;
  friend PositionedTrackHitCollection;
  friend PositionedTrackHitCollectionIterator;

public:

  /// default constructor
  ConstPositionedTrackHit();
  ConstPositionedTrackHit(fcc::Point position,fcc::BareHit core);

  /// constructor from existing PositionedTrackHitObj
  ConstPositionedTrackHit(PositionedTrackHitObj* obj);
  /// copy constructor
  ConstPositionedTrackHit(const ConstPositionedTrackHit& other);
  /// copy-assignment operator
  ConstPositionedTrackHit& operator=(const ConstPositionedTrackHit& other);
  /// support cloning (deep-copy)
  ConstPositionedTrackHit clone() const;
  /// destructor
  ~ConstPositionedTrackHit();


public:

  /// Access the  The global position
  const fcc::Point& position() const;
  /// Access the member of  The global position
  const float& x() const;
  /// Access the member of  The global position
  const float& y() const;
  /// Access the member of  The global position
  const float& z() const;
  /// Access the  The hit
  const fcc::BareHit& core() const;
  /// Access the member of  The hit
  const unsigned& bits() const;
  /// Access the member of  The hit
  const unsigned long long& cellId() const;
  /// Access the member of  The hit
  const float& energy() const;
  /// Access the member of  The hit
  const float& time() const;



  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from PositionedTrackHitObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const ConstPositionedTrackHit& other) const {
       return (m_obj==other.m_obj);
  }

  bool operator==(const PositionedTrackHit& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const PositionedTrackHit& p1,
//       const PositionedTrackHit& p2 );
  bool operator<(const ConstPositionedTrackHit& other) const { return m_obj < other.m_obj  ; }

  const podio::ObjectID getObjectID() const;

private:
  PositionedTrackHitObj* m_obj;

};
} // namespace fcc

#endif
