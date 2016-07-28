#ifndef CaloHitMCParticleAssociationOBJ_H
#define CaloHitMCParticleAssociationOBJ_H

// std includes
#include <atomic>
#include <iostream>

// data model specific includes
#include "podio/ObjBase.h"
#include "CaloHitMCParticleAssociationData.h"



// forward declarations
class CaloHitMCParticleAssociation;
class ConstCaloHitMCParticleAssociation;
namespace fcc {class ConstCaloHit;
class ConstMCParticle;
}


namespace fcc {
class CaloHitMCParticleAssociationObj : public podio::ObjBase {
public:
  /// constructor
  CaloHitMCParticleAssociationObj();
  /// copy constructor (does a deep-copy of relation containers)
  CaloHitMCParticleAssociationObj(const CaloHitMCParticleAssociationObj&);
  /// constructor from ObjectID and CaloHitMCParticleAssociationData
  /// does not initialize the internal relation containers
  CaloHitMCParticleAssociationObj(const podio::ObjectID id, CaloHitMCParticleAssociationData data);
  virtual ~CaloHitMCParticleAssociationObj();

public:
  CaloHitMCParticleAssociationData data;
  ::fcc::ConstCaloHit* m_hit;
  ::fcc::ConstMCParticle* m_particle;


};
} // namespace fcc


#endif
