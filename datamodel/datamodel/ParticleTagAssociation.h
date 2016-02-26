#ifndef ParticleTagAssociation_H
#define ParticleTagAssociation_H
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


#include "ParticleTagAssociationConst.h"
#include "ParticleTagAssociationObj.h"

namespace fcc {

class ParticleTagAssociationCollection;
class ParticleTagAssociationCollectionIterator;
class ConstParticleTagAssociation;

class ParticleTagAssociation {

  friend ParticleTagAssociationCollection;
  friend ParticleTagAssociationCollectionIterator;
  friend ConstParticleTagAssociation;

public:

  /// default constructor
  ParticleTagAssociation();
  
  /// constructor from existing ParticleTagAssociationObj
  ParticleTagAssociation(ParticleTagAssociationObj* obj);
  /// copy constructor
  ParticleTagAssociation(const ParticleTagAssociation& other);
  /// copy-assignment operator
  ParticleTagAssociation& operator=(const ParticleTagAssociation& other);
  /// support cloning (deep-copy)
  ParticleTagAssociation clone() const;
  /// destructor
  ~ParticleTagAssociation();

  /// conversion to const object
  operator ConstParticleTagAssociation () const;

public:

  const fcc::ConstParticle Particle() const;
  const fcc::ConstTag Tag() const;

  void Particle(fcc::ConstParticle value);
  void Tag(fcc::ConstTag value);


  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from ParticleTagAssociationObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const ParticleTagAssociation& other) const {
       return (m_obj==other.m_obj);
  }

  bool operator==(const ConstParticleTagAssociation& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const ParticleTagAssociation& p1,
//       const ParticleTagAssociation& p2 );

  const podio::ObjectID getObjectID() const;

private:
  ParticleTagAssociationObj* m_obj;

};

} // namespace fcc

#endif
