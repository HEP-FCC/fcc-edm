#ifndef PositionedCaloHit_H
#define PositionedCaloHit_H
#include "Point.h"
#include "BareHit.h"
#include "PositionedCaloHitData.h"
#include <vector>
#include "podio/ObjectID.h"

//forward declarations


#include "PositionedCaloHitConst.h"
#include "PositionedCaloHitObj.h"

namespace fcc {

class PositionedCaloHitCollection;
class PositionedCaloHitCollectionIterator;
class ConstPositionedCaloHit;

/** @class PositionedCaloHit
 *  A calorimeter hit with its global position
 *  @author: J. Lingemann, B. Hegner
 */
class PositionedCaloHit {

  friend PositionedCaloHitCollection;
  friend PositionedCaloHitCollectionIterator;
  friend ConstPositionedCaloHit;

public:

  /// default constructor
  PositionedCaloHit();
  PositionedCaloHit(fcc::Point position,fcc::BareHit core);

  /// constructor from existing PositionedCaloHitObj
  PositionedCaloHit(PositionedCaloHitObj* obj);
  /// copy constructor
  PositionedCaloHit(const PositionedCaloHit& other);
  /// copy-assignment operator
  PositionedCaloHit& operator=(const PositionedCaloHit& other);
  /// support cloning (deep-copy)
  PositionedCaloHit clone() const;
  /// destructor
  ~PositionedCaloHit();

  /// conversion to const object
  operator ConstPositionedCaloHit () const;

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
  /// disconnect from PositionedCaloHitObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const PositionedCaloHit& other) const {
    return (m_obj==other.m_obj);
  }

  bool operator==(const ConstPositionedCaloHit& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const PositionedCaloHit& p1,
//       const PositionedCaloHit& p2 );
  bool operator<(const PositionedCaloHit& other) const { return m_obj < other.m_obj  ; }

  const podio::ObjectID getObjectID() const;

private:
  PositionedCaloHitObj* m_obj;

};

} // namespace fcc

#endif
