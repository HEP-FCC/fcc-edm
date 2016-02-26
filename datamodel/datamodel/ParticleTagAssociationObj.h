#ifndef ParticleTagAssociationOBJ_H
#define ParticleTagAssociationOBJ_H

// std includes
#include <atomic>
#include <iostream>

// data model specific includes
#include "podio/ObjBase.h"
#include "ParticleTagAssociationData.h"



// forward declarations
class ParticleTagAssociation;
class ConstParticleTagAssociation;
namespace fcc {class ConstParticle;
class ConstTag;
}


namespace fcc {
class ParticleTagAssociationObj : public podio::ObjBase {
public:
  /// constructor
  ParticleTagAssociationObj();
  /// copy constructor (does a deep-copy of relation containers)
  ParticleTagAssociationObj(const ParticleTagAssociationObj&);
  /// constructor from ObjectID and ParticleTagAssociationData
  /// does not initialize the internal relation containers
  ParticleTagAssociationObj(const podio::ObjectID id, ParticleTagAssociationData data);
  virtual ~ParticleTagAssociationObj();

public:
  ParticleTagAssociationData data;
  ::fcc::ConstParticle* m_Particle;
  ::fcc::ConstTag* m_Tag;


};
} // namespace fcc


#endif
