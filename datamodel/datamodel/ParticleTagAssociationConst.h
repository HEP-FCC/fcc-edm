#ifndef ConstParticleTagAssociation_H
#define ConstParticleTagAssociation_H
#include "ParticleTagAssociationData.h"

#include <vector>
#include "podio/ObjectID.h"

// Association between a Particle and Tag information using a preferred algorithm
// author: C. Helsens

//forward declarations
namespace fcc {
class Particle;
class ConstParticle;
class Tag;
class ConstTag;
}


#include "ParticleTagAssociationObj.h"

namespace fcc {

class ParticleTagAssociationObj;
class ParticleTagAssociation;
class ParticleTagAssociationCollection;
class ParticleTagAssociationCollectionIterator;

class ConstParticleTagAssociation {

  friend ParticleTagAssociation;
  friend ParticleTagAssociationCollection;
  friend ParticleTagAssociationCollectionIterator;

public:

  /// default constructor
  ConstParticleTagAssociation();
  
  /// constructor from existing ParticleTagAssociationObj
  ConstParticleTagAssociation(ParticleTagAssociationObj* obj);
  /// copy constructor
  ConstParticleTagAssociation(const ConstParticleTagAssociation& other);
  /// copy-assignment operator
  ConstParticleTagAssociation& operator=(const ConstParticleTagAssociation& other);
  /// support cloning (deep-copy)
  ConstParticleTagAssociation clone() const;
  /// destructor
  ~ConstParticleTagAssociation();


public:

  const fcc::ConstParticle Particle() const;
  const fcc::ConstTag Tag() const;


  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from ParticleTagAssociationObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const ConstParticleTagAssociation& other) const {
       return (m_obj==other.m_obj);
  }

  bool operator==(const ParticleTagAssociation& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const ParticleTagAssociation& p1,
//       const ParticleTagAssociation& p2 );

  const podio::ObjectID getObjectID() const;

private:
  ParticleTagAssociationObj* m_obj;

};
} // namespace fcc

#endif
