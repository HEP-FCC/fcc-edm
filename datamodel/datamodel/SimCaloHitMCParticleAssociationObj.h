#ifndef SimCaloHitMCParticleAssociationOBJ_H
#define SimCaloHitMCParticleAssociationOBJ_H

// std includes
#include <atomic>
#include <iostream>

// data model specific includes
#include "podio/ObjBase.h"
#include "SimCaloHitMCParticleAssociationData.h"



// forward declarations
class SimCaloHitMCParticleAssociation;
class ConstSimCaloHitMCParticleAssociation;
class ConstSimCaloHit;
class ConstMCParticle;



class SimCaloHitMCParticleAssociationObj : public podio::ObjBase {
public:
  /// constructor
  SimCaloHitMCParticleAssociationObj();
  /// copy constructor (does a deep-copy of relation containers)
  SimCaloHitMCParticleAssociationObj(const SimCaloHitMCParticleAssociationObj&);
  /// constructor from ObjectID and SimCaloHitMCParticleAssociationData
  /// does not initialize the internal relation containers
  SimCaloHitMCParticleAssociationObj(const podio::ObjectID id, SimCaloHitMCParticleAssociationData data);
  virtual ~SimCaloHitMCParticleAssociationObj();

public:
  SimCaloHitMCParticleAssociationData data;
  ConstSimCaloHit* m_Hit;
  ConstMCParticle* m_Particle;


};



#endif
