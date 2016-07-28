#include "TaggedParticleObj.h"
#include "ParticleConst.h"


namespace fcc {
TaggedParticleObj::TaggedParticleObj() :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}, data(), m_particle(nullptr)

{ }

TaggedParticleObj::TaggedParticleObj(const podio::ObjectID id, TaggedParticleData data) :
    ObjBase{id,0}, data(data)
{ }

TaggedParticleObj::TaggedParticleObj(const TaggedParticleObj& other) :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    , data(other.data), m_particle(nullptr)
{
  if (other.m_particle != nullptr) {
     m_particle = new ::fcc::ConstParticle(*(other.m_particle));
  }

}

TaggedParticleObj::~TaggedParticleObj() {
  if (id.index == podio::ObjectID::untracked) {

  }
    if (m_particle != nullptr) delete m_particle;

}
} // namespace fcc
