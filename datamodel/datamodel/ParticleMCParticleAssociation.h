#ifndef ParticleMCParticleAssociation_H
#define ParticleMCParticleAssociation_H
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


#include "ParticleMCParticleAssociationConst.h"
#include "ParticleMCParticleAssociationObj.h"

namespace fcc {

class ParticleMCParticleAssociationCollection;
class ParticleMCParticleAssociationCollectionIterator;
class ConstParticleMCParticleAssociation;

class ParticleMCParticleAssociation {

  friend ParticleMCParticleAssociationCollection;
  friend ParticleMCParticleAssociationCollectionIterator;
  friend ConstParticleMCParticleAssociation;

public:

  /// default constructor
  ParticleMCParticleAssociation();

  /// constructor from existing ParticleMCParticleAssociationObj
  ParticleMCParticleAssociation(ParticleMCParticleAssociationObj* obj);
  /// copy constructor
  ParticleMCParticleAssociation(const ParticleMCParticleAssociation& other);
  /// copy-assignment operator
  ParticleMCParticleAssociation& operator=(const ParticleMCParticleAssociation& other);
  /// support cloning (deep-copy)
  ParticleMCParticleAssociation clone() const;
  /// destructor
  ~ParticleMCParticleAssociation();

  /// conversion to const object
  operator ConstParticleMCParticleAssociation () const;

public:

  const fcc::ConstParticle Rec() const;
  const fcc::ConstMCParticle Sim() const;

  void Rec(fcc::ConstParticle value);
  void Sim(fcc::ConstMCParticle value);



  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from ParticleMCParticleAssociationObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const ParticleMCParticleAssociation& other) const {
    return (m_obj==other.m_obj);
  }

  bool operator==(const ConstParticleMCParticleAssociation& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const ParticleMCParticleAssociation& p1,
//       const ParticleMCParticleAssociation& p2 );
  bool operator<(const ParticleMCParticleAssociation& other) const { return m_obj < other.m_obj  ; }

  const podio::ObjectID getObjectID() const;

private:
  ParticleMCParticleAssociationObj* m_obj;

};

} // namespace fcc

#endif
