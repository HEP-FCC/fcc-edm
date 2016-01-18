#ifndef CaloHitAssociation_H
#define CaloHitAssociation_H
#include "CaloHitAssociationData.h"

#include <vector>
#include "podio/ObjectID.h"

// Association between a CaloHit and the corresponding SimCaloHit
// author: C. Bernet, B. Hegner

//forward declarations
class CaloHit;
class ConstCaloHit;
class SimCaloHit;
class ConstSimCaloHit;


#include "CaloHitAssociationConst.h"
#include "CaloHitAssociationObj.h"



class CaloHitAssociationCollection;
class CaloHitAssociationCollectionIterator;
class ConstCaloHitAssociation;

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

  const ConstCaloHit Rec() const;
  const ConstSimCaloHit Sim() const;

  void Rec(ConstCaloHit value);
  void Sim(ConstSimCaloHit value);


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

  const podio::ObjectID getObjectID() const;

private:
  CaloHitAssociationObj* m_obj;

};



#endif
