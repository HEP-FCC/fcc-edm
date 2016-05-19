#ifndef ConstCaloHit_H
#define ConstCaloHit_H
#include "BareHit.h"
#include "CaloHitData.h"
#include <vector>
#include "podio/ObjectID.h"

// A calorimeter hit
// author: C. Bernet, B. Hegner

//forward declarations


#include "CaloHitObj.h"

namespace fcc {

class CaloHitObj;
class CaloHit;
class CaloHitCollection;
class CaloHitCollectionIterator;

class ConstCaloHit {

  friend CaloHit;
  friend CaloHitCollection;
  friend CaloHitCollectionIterator;

public:

  /// default constructor
  ConstCaloHit();
  ConstCaloHit(fcc::BareHit Core);

  /// constructor from existing CaloHitObj
  ConstCaloHit(CaloHitObj* obj);
  /// copy constructor
  ConstCaloHit(const ConstCaloHit& other);
  /// copy-assignment operator
  ConstCaloHit& operator=(const ConstCaloHit& other);
  /// support cloning (deep-copy)
  ConstCaloHit clone() const;
  /// destructor
  ~ConstCaloHit();


public:

  const fcc::BareHit& Core() const;



  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from CaloHitObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const ConstCaloHit& other) const {
       return (m_obj==other.m_obj);
  }

  bool operator==(const CaloHit& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const CaloHit& p1,
//       const CaloHit& p2 );
  bool operator<(const ConstCaloHit& other) const { return m_obj < other.m_obj  ; }

  const podio::ObjectID getObjectID() const;

private:
  CaloHitObj* m_obj;

};
} // namespace fcc

#endif
