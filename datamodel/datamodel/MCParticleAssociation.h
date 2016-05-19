#ifndef MCParticleAssociation_H
#define MCParticleAssociation_H
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


#include "MCParticleAssociationConst.h"
#include "MCParticleAssociationObj.h"

namespace fcc {

class MCParticleAssociationCollection;
class MCParticleAssociationCollectionIterator;
class ConstMCParticleAssociation;

class MCParticleAssociation {

  friend MCParticleAssociationCollection;
  friend MCParticleAssociationCollectionIterator;
  friend ConstMCParticleAssociation;

public:

  /// default constructor
  MCParticleAssociation();

  /// constructor from existing MCParticleAssociationObj
  MCParticleAssociation(MCParticleAssociationObj* obj);
  /// copy constructor
  MCParticleAssociation(const MCParticleAssociation& other);
  /// copy-assignment operator
  MCParticleAssociation& operator=(const MCParticleAssociation& other);
  /// support cloning (deep-copy)
  MCParticleAssociation clone() const;
  /// destructor
  ~MCParticleAssociation();

  /// conversion to const object
  operator ConstMCParticleAssociation () const;

public:

  const fcc::ConstMCParticle Mother() const;
  const fcc::ConstMCParticle Daughter() const;

  void Mother(fcc::ConstMCParticle value);
  void Daughter(fcc::ConstMCParticle value);



  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from MCParticleAssociationObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const MCParticleAssociation& other) const {
    return (m_obj==other.m_obj);
  }

  bool operator==(const ConstMCParticleAssociation& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const MCParticleAssociation& p1,
//       const MCParticleAssociation& p2 );
  bool operator<(const MCParticleAssociation& other) const { return m_obj < other.m_obj  ; }

  const podio::ObjectID getObjectID() const;

private:
  MCParticleAssociationObj* m_obj;

};

} // namespace fcc

#endif
