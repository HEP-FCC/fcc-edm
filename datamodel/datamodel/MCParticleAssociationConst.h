#ifndef ConstMCParticleAssociation_H
#define ConstMCParticleAssociation_H
#include "MCParticleAssociationData.h"

#include <vector>
#include "podio/ObjectID.h"

// Directed association between two MCParticles, for parentship.
// author: C. Bernet, B. Hegner

//forward declarations
namespace fcc {
class MCParticle;
class ConstMCParticle;
class MCParticle;
class ConstMCParticle;
}


#include "MCParticleAssociationObj.h"

namespace fcc {

class MCParticleAssociationObj;
class MCParticleAssociation;
class MCParticleAssociationCollection;
class MCParticleAssociationCollectionIterator;

class ConstMCParticleAssociation {

  friend MCParticleAssociation;
  friend MCParticleAssociationCollection;
  friend MCParticleAssociationCollectionIterator;

public:

  /// default constructor
  ConstMCParticleAssociation();
  
  /// constructor from existing MCParticleAssociationObj
  ConstMCParticleAssociation(MCParticleAssociationObj* obj);
  /// copy constructor
  ConstMCParticleAssociation(const ConstMCParticleAssociation& other);
  /// copy-assignment operator
  ConstMCParticleAssociation& operator=(const ConstMCParticleAssociation& other);
  /// support cloning (deep-copy)
  ConstMCParticleAssociation clone() const;
  /// destructor
  ~ConstMCParticleAssociation();


public:

  const fcc::ConstMCParticle Mother() const;
  const fcc::ConstMCParticle Daughter() const;


  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from MCParticleAssociationObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const ConstMCParticleAssociation& other) const {
       return (m_obj==other.m_obj);
  }

  bool operator==(const MCParticleAssociation& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const MCParticleAssociation& p1,
//       const MCParticleAssociation& p2 );

  const podio::ObjectID getObjectID() const;

private:
  MCParticleAssociationObj* m_obj;

};
} // namespace fcc

#endif
