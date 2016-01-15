#ifndef MCParticleAssociationOBJ_H
#define MCParticleAssociationOBJ_H

// std includes
#include <atomic>
#include <iostream>

// data model specific includes
#include "podio/ObjBase.h"
#include "MCParticleAssociationData.h"



// forward declarations
class MCParticleAssociation;
class ConstMCParticleAssociation;
class ConstMCParticle;
class ConstMCParticle;



class MCParticleAssociationObj : public podio::ObjBase {
public:
  /// constructor
  MCParticleAssociationObj();
  /// copy constructor (does a deep-copy of relation containers)
  MCParticleAssociationObj(const MCParticleAssociationObj&);
  /// constructor from ObjectID and MCParticleAssociationData
  /// does not initialize the internal relation containers
  MCParticleAssociationObj(const podio::ObjectID id, MCParticleAssociationData data);
  virtual ~MCParticleAssociationObj();

public:
  MCParticleAssociationData data;
  ConstMCParticle* m_Mother;
  ConstMCParticle* m_Daughter;


};



#endif
