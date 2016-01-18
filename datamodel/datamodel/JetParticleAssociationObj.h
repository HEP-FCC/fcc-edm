#ifndef JetParticleAssociationOBJ_H
#define JetParticleAssociationOBJ_H

// std includes
#include <atomic>
#include <iostream>

// data model specific includes
#include "podio/ObjBase.h"
#include "JetParticleAssociationData.h"



// forward declarations
class JetParticleAssociation;
class ConstJetParticleAssociation;
class ConstJet;
class ConstParticle;



class JetParticleAssociationObj : public podio::ObjBase {
public:
  /// constructor
  JetParticleAssociationObj();
  /// copy constructor (does a deep-copy of relation containers)
  JetParticleAssociationObj(const JetParticleAssociationObj&);
  /// constructor from ObjectID and JetParticleAssociationData
  /// does not initialize the internal relation containers
  JetParticleAssociationObj(const podio::ObjectID id, JetParticleAssociationData data);
  virtual ~JetParticleAssociationObj();

public:
  JetParticleAssociationData data;
  ConstJet* m_Jet;
  ConstParticle* m_Particle;


};



#endif
