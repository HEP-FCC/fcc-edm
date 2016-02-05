#ifndef ParticleOBJ_H
#define ParticleOBJ_H

// std includes
#include <atomic>
#include <iostream>

// data model specific includes
#include "podio/ObjBase.h"
#include "ParticleData.h"



// forward declarations
class Particle;
class ConstParticle;


namespace fcc {
class ParticleObj : public podio::ObjBase {
public:
  /// constructor
  ParticleObj();
  /// copy constructor (does a deep-copy of relation containers)
  ParticleObj(const ParticleObj&);
  /// constructor from ObjectID and ParticleData
  /// does not initialize the internal relation containers
  ParticleObj(const podio::ObjectID id, ParticleData data);
  virtual ~ParticleObj();

public:
  ParticleData data;


};
} // namespace fcc


#endif
