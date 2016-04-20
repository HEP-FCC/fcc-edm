#ifndef ParticleClusterAssociation_H
#define ParticleClusterAssociation_H
#include "ParticleClusterAssociationData.h"
#include <vector>
#include "podio/ObjectID.h"

// Association between a Particle and a Cluster.
// author: C. Bernet, B. Hegner

//forward declarations
namespace fcc {
class Particle;
class ConstParticle;
class CaloCluster;
class ConstCaloCluster;
}


#include "ParticleClusterAssociationConst.h"
#include "ParticleClusterAssociationObj.h"

namespace fcc {

class ParticleClusterAssociationCollection;
class ParticleClusterAssociationCollectionIterator;
class ConstParticleClusterAssociation;

class ParticleClusterAssociation {

  friend ParticleClusterAssociationCollection;
  friend ParticleClusterAssociationCollectionIterator;
  friend ConstParticleClusterAssociation;

public:

  /// default constructor
  ParticleClusterAssociation();

  /// constructor from existing ParticleClusterAssociationObj
  ParticleClusterAssociation(ParticleClusterAssociationObj* obj);
  /// copy constructor
  ParticleClusterAssociation(const ParticleClusterAssociation& other);
  /// copy-assignment operator
  ParticleClusterAssociation& operator=(const ParticleClusterAssociation& other);
  /// support cloning (deep-copy)
  ParticleClusterAssociation clone() const;
  /// destructor
  ~ParticleClusterAssociation();

  /// conversion to const object
  operator ConstParticleClusterAssociation () const;

public:

  const fcc::ConstParticle Particle() const;
  const fcc::ConstCaloCluster Cluster() const;

  void Particle(fcc::ConstParticle value);
  void Cluster(fcc::ConstCaloCluster value);



  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from ParticleClusterAssociationObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const ParticleClusterAssociation& other) const {
    return (m_obj==other.m_obj);
  }

  bool operator==(const ConstParticleClusterAssociation& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const ParticleClusterAssociation& p1,
//       const ParticleClusterAssociation& p2 );

  const podio::ObjectID getObjectID() const;

private:
  ParticleClusterAssociationObj* m_obj;

};

} // namespace fcc

#endif
