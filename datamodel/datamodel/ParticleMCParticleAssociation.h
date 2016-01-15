#ifndef ParticleMCParticleAssociation_H
#define ParticleMCParticleAssociation_H
#include "ParticleMCParticleAssociationData.h"

#include <vector>
#include "podio/ObjectID.h"

// Association between a Particle and a MCParticle, used to keep track of the correspondence between MC and reconstructed particles
// author: C. Bernet, B. Hegner

//forward declarations
class Particle;
class ConstParticle;
class MCParticle;
class ConstMCParticle;


#include "ParticleMCParticleAssociationConst.h"
#include "ParticleMCParticleAssociationObj.h"



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

  const ConstParticle Rec() const;
  const ConstMCParticle Sim() const;

  void Rec(ConstParticle value);
  void Sim(ConstMCParticle value);


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

  const podio::ObjectID getObjectID() const;

private:
  ParticleMCParticleAssociationObj* m_obj;

};



#endif
