#include "MCParticleObj.h"
#include "GenVertexConst.h"
#include "GenVertexConst.h"


namespace fcc {
MCParticleObj::MCParticleObj() :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}, data(),m_StartVertex(nullptr)
,m_EndVertex(nullptr)

{ }

MCParticleObj::MCParticleObj(const podio::ObjectID id, MCParticleData data) :
    ObjBase{id,0}, data(data)
{ }

MCParticleObj::MCParticleObj(const MCParticleObj& other) :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    , data(other.data)
{ }

MCParticleObj::~MCParticleObj() {
  if (id.index == podio::ObjectID::untracked) {

  }
    if (m_StartVertex != nullptr) delete m_StartVertex;
    if (m_EndVertex != nullptr) delete m_EndVertex;

}
} // namespace fcc
