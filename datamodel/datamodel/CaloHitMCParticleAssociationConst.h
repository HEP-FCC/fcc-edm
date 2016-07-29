#ifndef ConstCaloHitMCParticleAssociation_H
#define ConstCaloHitMCParticleAssociation_H
#include "CaloHitMCParticleAssociationData.h"
#include <vector>
#include "podio/ObjectID.h"

//forward declarations
namespace fcc {
class CaloHit;
class ConstCaloHit;
class MCParticle;
class ConstMCParticle;
}


#include "CaloHitMCParticleAssociationObj.h"

namespace fcc {

class CaloHitMCParticleAssociationObj;
class CaloHitMCParticleAssociation;
class CaloHitMCParticleAssociationCollection;
class CaloHitMCParticleAssociationCollectionIterator;

/** @class ConstCaloHitMCParticleAssociation
 *  Association between a CaloHit and a particle that contributed to the hit.
 *  @author: C. Bernet, B. Hegner
 */

class ConstCaloHitMCParticleAssociation {

  friend CaloHitMCParticleAssociation;
  friend CaloHitMCParticleAssociationCollection;
  friend CaloHitMCParticleAssociationCollectionIterator;

public:

  /// default constructor
  ConstCaloHitMCParticleAssociation();
  ConstCaloHitMCParticleAssociation(float fraction);

  /// constructor from existing CaloHitMCParticleAssociationObj
  ConstCaloHitMCParticleAssociation(CaloHitMCParticleAssociationObj* obj);
  /// copy constructor
  ConstCaloHitMCParticleAssociation(const ConstCaloHitMCParticleAssociation& other);
  /// copy-assignment operator
  ConstCaloHitMCParticleAssociation& operator=(const ConstCaloHitMCParticleAssociation& other);
  /// support cloning (deep-copy)
  ConstCaloHitMCParticleAssociation clone() const;
  /// destructor
  ~ConstCaloHitMCParticleAssociation();


public:

  /// Access the  Fraction of the particle energy used in the hit.
  const float& fraction() const;
  /// Access the  the hit
  const fcc::ConstCaloHit hit() const;
  /// Access the  the particle
  const fcc::ConstMCParticle particle() const;



  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from CaloHitMCParticleAssociationObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const ConstCaloHitMCParticleAssociation& other) const {
       return (m_obj==other.m_obj);
  }

  bool operator==(const CaloHitMCParticleAssociation& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const CaloHitMCParticleAssociation& p1,
//       const CaloHitMCParticleAssociation& p2 );
  bool operator<(const ConstCaloHitMCParticleAssociation& other) const { return m_obj < other.m_obj  ; }

  const podio::ObjectID getObjectID() const;

private:
  CaloHitMCParticleAssociationObj* m_obj;

};
} // namespace fcc

#endif
