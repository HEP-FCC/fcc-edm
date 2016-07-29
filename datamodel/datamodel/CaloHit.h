#ifndef CaloHit_H
#define CaloHit_H
#include "BareHit.h"
#include "CaloHitData.h"
#include <vector>
#include "podio/ObjectID.h"

//forward declarations


#include "CaloHitConst.h"
#include "CaloHitObj.h"

namespace fcc {

class CaloHitCollection;
class CaloHitCollectionIterator;
class ConstCaloHit;

/** @class CaloHit
 *  A calorimeter hit
 *  @author: C. Bernet, B. Hegner
 */
class CaloHit {

  friend CaloHitCollection;
  friend CaloHitCollectionIterator;
  friend ConstCaloHit;

public:

  /// default constructor
  CaloHit();
  CaloHit(fcc::BareHit core);

  /// constructor from existing CaloHitObj
  CaloHit(CaloHitObj* obj);
  /// copy constructor
  CaloHit(const CaloHit& other);
  /// copy-assignment operator
  CaloHit& operator=(const CaloHit& other);
  /// support cloning (deep-copy)
  CaloHit clone() const;
  /// destructor
  ~CaloHit();

  /// conversion to const object
  operator ConstCaloHit () const;

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

  /// Get reference to the  contains basic hit information
  fcc::BareHit& core();
  /// Set the  contains basic hit information
  void core(class fcc::BareHit value);
  /// Set the  member of  contains basic hit information
  void bits(unsigned value);

  /// Set the  member of  contains basic hit information
  void cellId(unsigned long long value);

  /// Set the  member of  contains basic hit information
  void energy(float value);

  /// Set the  member of  contains basic hit information
  void time(float value);




  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from CaloHitObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const CaloHit& other) const {
    return (m_obj==other.m_obj);
  }

  bool operator==(const ConstCaloHit& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const CaloHit& p1,
//       const CaloHit& p2 );
  bool operator<(const CaloHit& other) const { return m_obj < other.m_obj  ; }

  const podio::ObjectID getObjectID() const;

private:
  CaloHitObj* m_obj;

};

} // namespace fcc

#endif
