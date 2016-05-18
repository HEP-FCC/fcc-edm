#ifndef ConstCaloHitAssociation_H
#define ConstCaloHitAssociation_H
#include "CaloHitAssociationData.h"
#include <vector>
#include "podio/ObjectID.h"

// Association between a CaloHit and the corresponding SimCaloHit
// author: C. Bernet, B. Hegner

//forward declarations
namespace fcc {
class CaloHit;
class ConstCaloHit;
class SimCaloHit;
class ConstSimCaloHit;
}


#include "CaloHitAssociationObj.h"

namespace fcc {

class CaloHitAssociationObj;
class CaloHitAssociation;
class CaloHitAssociationCollection;
class CaloHitAssociationCollectionIterator;

class ConstCaloHitAssociation {

  friend CaloHitAssociation;
  friend CaloHitAssociationCollection;
  friend CaloHitAssociationCollectionIterator;

public:

  /// default constructor
  ConstCaloHitAssociation();
  
  /// constructor from existing CaloHitAssociationObj
  ConstCaloHitAssociation(CaloHitAssociationObj* obj);
  /// copy constructor
  ConstCaloHitAssociation(const ConstCaloHitAssociation& other);
  /// copy-assignment operator
  ConstCaloHitAssociation& operator=(const ConstCaloHitAssociation& other);
  /// support cloning (deep-copy)
  ConstCaloHitAssociation clone() const;
  /// destructor
  ~ConstCaloHitAssociation();


public:

  const fcc::ConstCaloHit Rec() const;
  const fcc::ConstSimCaloHit Sim() const;



  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from CaloHitAssociationObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const ConstCaloHitAssociation& other) const {
       return (m_obj==other.m_obj);
  }

  bool operator==(const CaloHitAssociation& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const CaloHitAssociation& p1,
//       const CaloHitAssociation& p2 );
  bool operator<(const ConstCaloHitAssociation& other) const { return m_obj < other.m_obj  ; }

  const podio::ObjectID getObjectID() const;

private:
  CaloHitAssociationObj* m_obj;

};
} // namespace fcc

#endif
