#ifndef TaggedParticleOBJ_H
#define TaggedParticleOBJ_H

// std includes
#include <atomic>
#include <iostream>

// data model specific includes
#include "podio/ObjBase.h"
#include "TaggedParticleData.h"



// forward declarations
class TaggedParticle;
class ConstTaggedParticle;
namespace fcc {class ConstParticle;
}


namespace fcc {
class TaggedParticleObj : public podio::ObjBase {
public:
  /// constructor
  TaggedParticleObj();
  /// copy constructor (does a deep-copy of relation containers)
  TaggedParticleObj(const TaggedParticleObj&);
  /// constructor from ObjectID and TaggedParticleData
  /// does not initialize the internal relation containers
  TaggedParticleObj(const podio::ObjectID id, TaggedParticleData data);
  virtual ~TaggedParticleObj();

public:
  TaggedParticleData data;
  ::fcc::ConstParticle* m_particle;


};
} // namespace fcc


#endif
