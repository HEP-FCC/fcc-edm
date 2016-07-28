#ifndef CaloHitAssociation_H
#define CaloHitAssociation_H
#include "CaloHitAssociationData.h"
#include <vector>
#include "podio/ObjectID.h"

//forward declarations
namespace fcc {
class CaloHit;
class ConstCaloHit;
class CaloHit;
class ConstCaloHit;
}


#include "CaloHitAssociationConst.h"
#include "CaloHitAssociationObj.h"

namespace fcc {

class CaloHitAssociationCollection;
class CaloHitAssociationCollectionIterator;
class ConstCaloHitAssociation;

/** @class CaloHitAssociation
 *  Association between a CaloHit and the corresponding simulated CaloHit
 *  @author: C. Bernet, B. Hegner
 */
class CaloHitAssociation {

  friend CaloHitAssociationCollection;
  friend CaloHitAssociationCollectionIterator;
  friend ConstCaloHitAssociation;

public:

  /// default constructor
  CaloHitAssociation();

  /// constructor from existing CaloHitAssociationObj
  CaloHitAssociation(CaloHitAssociationObj* obj);
  /// copy constructor
  CaloHitAssociation(const CaloHitAssociation& other);
  /// copy-assignment operator
  CaloHitAssociation& operator=(const CaloHitAssociation& other);
  /// support cloning (deep-copy)
  CaloHitAssociation clone() const;
  /// destructor
  ~CaloHitAssociation();

  /// conversion to const object
  operator ConstCaloHitAssociation () const;

public:

  /// Access the  The reconstruted hit.
  const fcc::ConstCaloHit rec() const;
  /// Access the  The simulated hit.
  const fcc::ConstCaloHit sim() const;

  /// Set the  The reconstruted hit.
  void rec(fcc::ConstCaloHit value);
  /// Set the  The simulated hit.
  void sim(fcc::ConstCaloHit value);



  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from CaloHitAssociationObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const CaloHitAssociation& other) const {
    return (m_obj==other.m_obj);
  }

  bool operator==(const ConstCaloHitAssociation& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const CaloHitAssociation& p1,
//       const CaloHitAssociation& p2 );
  bool operator<(const CaloHitAssociation& other) const { return m_obj < other.m_obj  ; }

  const podio::ObjectID getObjectID() const;

private:
  CaloHitAssociationObj* m_obj;

};

} // namespace fcc

#endif
