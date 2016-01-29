#ifndef ParticleTrackAssociationOBJ_H
#define ParticleTrackAssociationOBJ_H

// std includes
#include <atomic>
#include <iostream>

// data model specific includes
#include "podio/ObjBase.h"
#include "ParticleTrackAssociationData.h"



// forward declarations
class ParticleTrackAssociation;
class ConstParticleTrackAssociation;
namespace fcc {class ConstParticle;
class ConstTrack;
}


namespace fcc {
class ParticleTrackAssociationObj : public podio::ObjBase {
public:
  /// constructor
  ParticleTrackAssociationObj();
  /// copy constructor (does a deep-copy of relation containers)
  ParticleTrackAssociationObj(const ParticleTrackAssociationObj&);
  /// constructor from ObjectID and ParticleTrackAssociationData
  /// does not initialize the internal relation containers
  ParticleTrackAssociationObj(const podio::ObjectID id, ParticleTrackAssociationData data);
  virtual ~ParticleTrackAssociationObj();

public:
  ParticleTrackAssociationData data;
  ::fcc::ConstParticle* m_Particle;
  ::fcc::ConstTrack* m_Track;


};
} // namespace fcc


#endif
