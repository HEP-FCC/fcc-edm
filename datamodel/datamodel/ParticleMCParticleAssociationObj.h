#ifndef ParticleMCParticleAssociationOBJ_H
#define ParticleMCParticleAssociationOBJ_H

// std includes
#include <atomic>
#include <iostream>

// data model specific includes
#include "podio/ObjBase.h"
#include "ParticleMCParticleAssociationData.h"



// forward declarations
class ParticleMCParticleAssociation;
class ConstParticleMCParticleAssociation;
namespace fcc {class ConstParticle;
class ConstMCParticle;
}


namespace fcc {
class ParticleMCParticleAssociationObj : public podio::ObjBase {
public:
  /// constructor
  ParticleMCParticleAssociationObj();
  /// copy constructor (does a deep-copy of relation containers)
  ParticleMCParticleAssociationObj(const ParticleMCParticleAssociationObj&);
  /// constructor from ObjectID and ParticleMCParticleAssociationData
  /// does not initialize the internal relation containers
  ParticleMCParticleAssociationObj(const podio::ObjectID id, ParticleMCParticleAssociationData data);
  virtual ~ParticleMCParticleAssociationObj();

public:
  ParticleMCParticleAssociationData data;
  ::fcc::ConstParticle* m_rec;
  ::fcc::ConstMCParticle* m_sim;


};
} // namespace fcc


#endif
