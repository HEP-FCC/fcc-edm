#ifndef PositionedTrackHit_H
#define PositionedTrackHit_H
#include "Point.h"
#include "BareHit.h"
#include "PositionedTrackHitData.h"
#include <vector>
#include "podio/ObjectID.h"

//forward declarations


#include "PositionedTrackHitConst.h"
#include "PositionedTrackHitObj.h"

namespace fcc {

class PositionedTrackHitCollection;
class PositionedTrackHitCollectionIterator;
class ConstPositionedTrackHit;

/** @class PositionedTrackHit
 *  A track hit and with its global position
 *  @author: J. Lingemann, B. Hegner
 */
class PositionedTrackHit {

  friend PositionedTrackHitCollection;
  friend PositionedTrackHitCollectionIterator;
  friend ConstPositionedTrackHit;

public:

  /// default constructor
  PositionedTrackHit();
  PositionedTrackHit(fcc::Point position,fcc::BareHit core);

  /// constructor from existing PositionedTrackHitObj
  PositionedTrackHit(PositionedTrackHitObj* obj);
  /// copy constructor
  PositionedTrackHit(const PositionedTrackHit& other);
  /// copy-assignment operator
  PositionedTrackHit& operator=(const PositionedTrackHit& other);
  /// support cloning (deep-copy)
  PositionedTrackHit clone() const;
  /// destructor
  ~PositionedTrackHit();

  /// conversion to const object
  operator ConstPositionedTrackHit () const;

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
  const ulonglong& cellId() const;
  /// Access the member of  The hit
  const float& energy() const;
  /// Access the member of  The hit
  const float& time() const;

  /// Get reference to the  The global position
  fcc::Point& position();
  /// Set the  The global position
  void position(class fcc::Point value);
  /// Set the  member of  The global position
  void x(float value);

  /// Set the  member of  The global position
  void y(float value);

  /// Set the  member of  The global position
  void z(float value);

  /// Get reference to the  The hit
  fcc::BareHit& core();
  /// Set the  The hit
  void core(class fcc::BareHit value);
  /// Set the  member of  The hit
  void bits(unsigned value);

  /// Set the  member of  The hit
  void cellId(ulonglong value);

  /// Set the  member of  The hit
  void energy(float value);

  /// Set the  member of  The hit
  void time(float value);




  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from PositionedTrackHitObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const PositionedTrackHit& other) const {
    return (m_obj==other.m_obj);
  }

  bool operator==(const ConstPositionedTrackHit& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const PositionedTrackHit& p1,
//       const PositionedTrackHit& p2 );
  bool operator<(const PositionedTrackHit& other) const { return m_obj < other.m_obj  ; }

  const podio::ObjectID getObjectID() const;

private:
  PositionedTrackHitObj* m_obj;

};

} // namespace fcc

#endif
