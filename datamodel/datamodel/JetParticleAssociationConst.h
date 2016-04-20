#ifndef ConstJetParticleAssociation_H
#define ConstJetParticleAssociation_H
#include "JetParticleAssociationData.h"
#include <vector>
#include "podio/ObjectID.h"

// Association between a Jet and a Particle. Used to keep track of jet constituents
// author: C. Bernet, B. Hegner

//forward declarations
namespace fcc {
class Jet;
class ConstJet;
class Particle;
class ConstParticle;
}


#include "JetParticleAssociationObj.h"

namespace fcc {

class JetParticleAssociationObj;
class JetParticleAssociation;
class JetParticleAssociationCollection;
class JetParticleAssociationCollectionIterator;

class ConstJetParticleAssociation {

  friend JetParticleAssociation;
  friend JetParticleAssociationCollection;
  friend JetParticleAssociationCollectionIterator;

public:

  /// default constructor
  ConstJetParticleAssociation();
  
  /// constructor from existing JetParticleAssociationObj
  ConstJetParticleAssociation(JetParticleAssociationObj* obj);
  /// copy constructor
  ConstJetParticleAssociation(const ConstJetParticleAssociation& other);
  /// copy-assignment operator
  ConstJetParticleAssociation& operator=(const ConstJetParticleAssociation& other);
  /// support cloning (deep-copy)
  ConstJetParticleAssociation clone() const;
  /// destructor
  ~ConstJetParticleAssociation();


public:

  const fcc::ConstJet Jet() const;
  const fcc::ConstParticle Particle() const;



  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from JetParticleAssociationObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const ConstJetParticleAssociation& other) const {
       return (m_obj==other.m_obj);
  }

  bool operator==(const JetParticleAssociation& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const JetParticleAssociation& p1,
//       const JetParticleAssociation& p2 );

  const podio::ObjectID getObjectID() const;

private:
  JetParticleAssociationObj* m_obj;

};
} // namespace fcc

#endif
