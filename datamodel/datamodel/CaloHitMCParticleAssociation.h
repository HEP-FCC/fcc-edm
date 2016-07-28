#ifndef CaloHitMCParticleAssociation_H
#define CaloHitMCParticleAssociation_H
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


#include "CaloHitMCParticleAssociationConst.h"
#include "CaloHitMCParticleAssociationObj.h"

namespace fcc {

class CaloHitMCParticleAssociationCollection;
class CaloHitMCParticleAssociationCollectionIterator;
class ConstCaloHitMCParticleAssociation;

/** @class CaloHitMCParticleAssociation
 *  Association between a CaloHit and a particle that contributed to the hit.
 *  @author: C. Bernet, B. Hegner
 */
class CaloHitMCParticleAssociation {

  friend CaloHitMCParticleAssociationCollection;
  friend CaloHitMCParticleAssociationCollectionIterator;
  friend ConstCaloHitMCParticleAssociation;

public:

  /// default constructor
  CaloHitMCParticleAssociation();
  CaloHitMCParticleAssociation(float fraction);

  /// constructor from existing CaloHitMCParticleAssociationObj
  CaloHitMCParticleAssociation(CaloHitMCParticleAssociationObj* obj);
  /// copy constructor
  CaloHitMCParticleAssociation(const CaloHitMCParticleAssociation& other);
  /// copy-assignment operator
  CaloHitMCParticleAssociation& operator=(const CaloHitMCParticleAssociation& other);
  /// support cloning (deep-copy)
  CaloHitMCParticleAssociation clone() const;
  /// destructor
  ~CaloHitMCParticleAssociation();

  /// conversion to const object
  operator ConstCaloHitMCParticleAssociation () const;

public:

  /// Access the  Fraction of the particle energy used in the hit.
  const float& fraction() const;
  /// Access the  the hit
  const fcc::ConstCaloHit hit() const;
  /// Access the  the particle
  const fcc::ConstMCParticle particle() const;

  /// Set the  Fraction of the particle energy used in the hit.
  void fraction(float value);

  /// Set the  the hit
  void hit(fcc::ConstCaloHit value);
  /// Set the  the particle
  void particle(fcc::ConstMCParticle value);



  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from CaloHitMCParticleAssociationObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const CaloHitMCParticleAssociation& other) const {
    return (m_obj==other.m_obj);
  }

  bool operator==(const ConstCaloHitMCParticleAssociation& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const CaloHitMCParticleAssociation& p1,
//       const CaloHitMCParticleAssociation& p2 );
  bool operator<(const CaloHitMCParticleAssociation& other) const { return m_obj < other.m_obj  ; }

  const podio::ObjectID getObjectID() const;

private:
  CaloHitMCParticleAssociationObj* m_obj;

};

} // namespace fcc

#endif
