#ifndef ConstSimCaloHitMCParticleAssociation_H
#define ConstSimCaloHitMCParticleAssociation_H
#include "SimCaloHitMCParticleAssociationData.h"
#include <vector>
#include "podio/ObjectID.h"

// Association between a SimCaloHit and a particle that contributed to the hit.
// author: C. Bernet, B. Hegner

//forward declarations
namespace fcc {
class SimCaloHit;
class ConstSimCaloHit;
class MCParticle;
class ConstMCParticle;
}


#include "SimCaloHitMCParticleAssociationObj.h"

namespace fcc {

class SimCaloHitMCParticleAssociationObj;
class SimCaloHitMCParticleAssociation;
class SimCaloHitMCParticleAssociationCollection;
class SimCaloHitMCParticleAssociationCollectionIterator;

class ConstSimCaloHitMCParticleAssociation {

  friend SimCaloHitMCParticleAssociation;
  friend SimCaloHitMCParticleAssociationCollection;
  friend SimCaloHitMCParticleAssociationCollectionIterator;

public:

  /// default constructor
  ConstSimCaloHitMCParticleAssociation();
  ConstSimCaloHitMCParticleAssociation(float Fraction);

  /// constructor from existing SimCaloHitMCParticleAssociationObj
  ConstSimCaloHitMCParticleAssociation(SimCaloHitMCParticleAssociationObj* obj);
  /// copy constructor
  ConstSimCaloHitMCParticleAssociation(const ConstSimCaloHitMCParticleAssociation& other);
  /// copy-assignment operator
  ConstSimCaloHitMCParticleAssociation& operator=(const ConstSimCaloHitMCParticleAssociation& other);
  /// support cloning (deep-copy)
  ConstSimCaloHitMCParticleAssociation clone() const;
  /// destructor
  ~ConstSimCaloHitMCParticleAssociation();


public:

  const float& Fraction() const;
  const fcc::ConstSimCaloHit Hit() const;
  const fcc::ConstMCParticle Particle() const;



  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from SimCaloHitMCParticleAssociationObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const ConstSimCaloHitMCParticleAssociation& other) const {
       return (m_obj==other.m_obj);
  }

  bool operator==(const SimCaloHitMCParticleAssociation& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const SimCaloHitMCParticleAssociation& p1,
//       const SimCaloHitMCParticleAssociation& p2 );

  const podio::ObjectID getObjectID() const;

private:
  SimCaloHitMCParticleAssociationObj* m_obj;

};
} // namespace fcc

#endif
