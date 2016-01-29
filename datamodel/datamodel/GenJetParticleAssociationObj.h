#ifndef GenJetParticleAssociationOBJ_H
#define GenJetParticleAssociationOBJ_H

// std includes
#include <atomic>
#include <iostream>

// data model specific includes
#include "podio/ObjBase.h"
#include "GenJetParticleAssociationData.h"



// forward declarations
class GenJetParticleAssociation;
class ConstGenJetParticleAssociation;
namespace fcc {class ConstGenJet;
class ConstMCParticle;
}


namespace fcc {
class GenJetParticleAssociationObj : public podio::ObjBase {
public:
  /// constructor
  GenJetParticleAssociationObj();
  /// copy constructor (does a deep-copy of relation containers)
  GenJetParticleAssociationObj(const GenJetParticleAssociationObj&);
  /// constructor from ObjectID and GenJetParticleAssociationData
  /// does not initialize the internal relation containers
  GenJetParticleAssociationObj(const podio::ObjectID id, GenJetParticleAssociationData data);
  virtual ~GenJetParticleAssociationObj();

public:
  GenJetParticleAssociationData data;
  ::fcc::ConstGenJet* m_Jet;
  ::fcc::ConstMCParticle* m_Particle;


};
} // namespace fcc


#endif
