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
namespace fcc {class ConstJet;
class ConstParticle;
}


namespace fcc {
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
  ::fcc::ConstJet* m_Jet;
  ::fcc::ConstParticle* m_Particle;


};
} // namespace fcc


#endif
