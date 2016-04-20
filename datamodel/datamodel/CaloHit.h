#ifndef CaloHit_H
#define CaloHit_H
#include "BareHit.h"
#include "CaloHitData.h"
#include <vector>
#include "podio/ObjectID.h"

// A calorimeter hit
// author: C. Bernet, B. Hegner

//forward declarations


#include "CaloHitConst.h"
#include "CaloHitObj.h"

namespace fcc {

class CaloHitCollection;
class CaloHitCollectionIterator;
class ConstCaloHit;

class CaloHit {

  friend CaloHitCollection;
  friend CaloHitCollectionIterator;
  friend ConstCaloHit;

public:

  /// default constructor
  CaloHit();
  CaloHit(fcc::BareHit Core);

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

  const fcc::BareHit& Core() const;

  fcc::BareHit& Core();
  void Core(class fcc::BareHit value);



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

  const podio::ObjectID getObjectID() const;

private:
  CaloHitObj* m_obj;

};

} // namespace fcc

#endif
