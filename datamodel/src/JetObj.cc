#include "JetObj.h"


namespace fcc {
JetObj::JetObj() :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}, data(), m_particles(new std::vector<::fcc::ConstParticle>())
{ }

JetObj::JetObj(const podio::ObjectID id, JetData data) :
    ObjBase{id,0}, data(data)
{ }

JetObj::JetObj(const JetObj& other) :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    , data(other.data), m_particles(new std::vector<::fcc::ConstParticle>(*(other.m_particles)))
{

}

JetObj::~JetObj() {
  if (id.index == podio::ObjectID::untracked) {
    delete m_particles;

  }

}
} // namespace fcc
