#ifndef ConstParticleClusterAssociation_H
#define ConstParticleClusterAssociation_H
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


#include "ParticleClusterAssociationObj.h"

namespace fcc {

class ParticleClusterAssociationObj;
class ParticleClusterAssociation;
class ParticleClusterAssociationCollection;
class ParticleClusterAssociationCollectionIterator;

class ConstParticleClusterAssociation {

  friend ParticleClusterAssociation;
  friend ParticleClusterAssociationCollection;
  friend ParticleClusterAssociationCollectionIterator;

public:

  /// default constructor
  ConstParticleClusterAssociation();
  
  /// constructor from existing ParticleClusterAssociationObj
  ConstParticleClusterAssociation(ParticleClusterAssociationObj* obj);
  /// copy constructor
  ConstParticleClusterAssociation(const ConstParticleClusterAssociation& other);
  /// copy-assignment operator
  ConstParticleClusterAssociation& operator=(const ConstParticleClusterAssociation& other);
  /// support cloning (deep-copy)
  ConstParticleClusterAssociation clone() const;
  /// destructor
  ~ConstParticleClusterAssociation();


public:

  const fcc::ConstParticle Particle() const;
  const fcc::ConstCaloCluster Cluster() const;



  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from ParticleClusterAssociationObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const ConstParticleClusterAssociation& other) const {
       return (m_obj==other.m_obj);
  }

  bool operator==(const ParticleClusterAssociation& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const ParticleClusterAssociation& p1,
//       const ParticleClusterAssociation& p2 );
  bool operator<(const ConstParticleClusterAssociation& other) const { return m_obj < other.m_obj  ; }

  const podio::ObjectID getObjectID() const;

private:
  ParticleClusterAssociationObj* m_obj;

};
} // namespace fcc

#endif
