#ifndef ParticleClusterAssociationOBJ_H
#define ParticleClusterAssociationOBJ_H

// std includes
#include <atomic>
#include <iostream>

// data model specific includes
#include "podio/ObjBase.h"
#include "ParticleClusterAssociationData.h"



// forward declarations
class ParticleClusterAssociation;
class ConstParticleClusterAssociation;
class ConstParticle;
class ConstCaloCluster;



class ParticleClusterAssociationObj : public podio::ObjBase {
public:
  /// constructor
  ParticleClusterAssociationObj();
  /// copy constructor (does a deep-copy of relation containers)
  ParticleClusterAssociationObj(const ParticleClusterAssociationObj&);
  /// constructor from ObjectID and ParticleClusterAssociationData
  /// does not initialize the internal relation containers
  ParticleClusterAssociationObj(const podio::ObjectID id, ParticleClusterAssociationData data);
  virtual ~ParticleClusterAssociationObj();

public:
  ParticleClusterAssociationData data;
  ConstParticle* m_Particle;
  ConstCaloCluster* m_Cluster;


};



#endif
