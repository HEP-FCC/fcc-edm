#ifndef ConstPositionedCaloHit_H
#define ConstPositionedCaloHit_H
#include "Point.h"
#include "BareHit.h"
#include "PositionedCaloHitData.h"
#include <vector>
#include "podio/ObjectID.h"

//forward declarations


#include "PositionedCaloHitObj.h"

namespace fcc {

class PositionedCaloHitObj;
class PositionedCaloHit;
class PositionedCaloHitCollection;
class PositionedCaloHitCollectionIterator;

/** @class ConstPositionedCaloHit
 *  A calorimeter hit with its global position
 *  @author: J. Lingemann, B. Hegner
 */

class ConstPositionedCaloHit {

  friend PositionedCaloHit;
  friend PositionedCaloHitCollection;
  friend PositionedCaloHitCollectionIterator;

public:

  /// default constructor
  ConstPositionedCaloHit();
  ConstPositionedCaloHit(fcc::Point position,fcc::BareHit core);

  /// constructor from existing PositionedCaloHitObj
  ConstPositionedCaloHit(PositionedCaloHitObj* obj);
  /// copy constructor
  ConstPositionedCaloHit(const ConstPositionedCaloHit& other);
  /// copy-assignment operator
  ConstPositionedCaloHit& operator=(const ConstPositionedCaloHit& other);
  /// support cloning (deep-copy)
  ConstPositionedCaloHit clone() const;
  /// destructor
  ~ConstPositionedCaloHit();


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



  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from PositionedCaloHitObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const ConstPositionedCaloHit& other) const {
       return (m_obj==other.m_obj);
  }

  bool operator==(const PositionedCaloHit& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const PositionedCaloHit& p1,
//       const PositionedCaloHit& p2 );
  bool operator<(const ConstPositionedCaloHit& other) const { return m_obj < other.m_obj  ; }

  const podio::ObjectID getObjectID() const;

private:
  PositionedCaloHitObj* m_obj;

};
} // namespace fcc

#endif
