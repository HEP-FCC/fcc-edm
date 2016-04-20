#ifndef ConstParticleMCParticleAssociation_H
#define ConstParticleMCParticleAssociation_H
#include "ParticleMCParticleAssociationData.h"
#include <vector>
#include "podio/ObjectID.h"

// Association between a Particle and a MCParticle, used to keep track of the correspondence between MC and reconstructed particles
// author: C. Bernet, B. Hegner

//forward declarations
namespace fcc {
class Particle;
class ConstParticle;
class MCParticle;
class ConstMCParticle;
}


#include "ParticleMCParticleAssociationObj.h"

namespace fcc {

class ParticleMCParticleAssociationObj;
class ParticleMCParticleAssociation;
class ParticleMCParticleAssociationCollection;
class ParticleMCParticleAssociationCollectionIterator;

class ConstParticleMCParticleAssociation {

  friend ParticleMCParticleAssociation;
  friend ParticleMCParticleAssociationCollection;
  friend ParticleMCParticleAssociationCollectionIterator;

public:

  /// default constructor
  ConstParticleMCParticleAssociation();
  
  /// constructor from existing ParticleMCParticleAssociationObj
  ConstParticleMCParticleAssociation(ParticleMCParticleAssociationObj* obj);
  /// copy constructor
  ConstParticleMCParticleAssociation(const ConstParticleMCParticleAssociation& other);
  /// copy-assignment operator
  ConstParticleMCParticleAssociation& operator=(const ConstParticleMCParticleAssociation& other);
  /// support cloning (deep-copy)
  ConstParticleMCParticleAssociation clone() const;
  /// destructor
  ~ConstParticleMCParticleAssociation();


public:

  const fcc::ConstParticle Rec() const;
  const fcc::ConstMCParticle Sim() const;



  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from ParticleMCParticleAssociationObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const ConstParticleMCParticleAssociation& other) const {
       return (m_obj==other.m_obj);
  }

  bool operator==(const ParticleMCParticleAssociation& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const ParticleMCParticleAssociation& p1,
//       const ParticleMCParticleAssociation& p2 );

  const podio::ObjectID getObjectID() const;

private:
  ParticleMCParticleAssociationObj* m_obj;

};
} // namespace fcc

#endif
