#include "MCParticleObj.h"
#include "GenVertexConst.h"
#include "GenVertexConst.h"


namespace fcc {
MCParticleObj::MCParticleObj() :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}, data(), m_startVertex(nullptr)
, m_endVertex(nullptr)

{ }

MCParticleObj::MCParticleObj(const podio::ObjectID id, MCParticleData data) :
    ObjBase{id,0}, data(data)
{ }

MCParticleObj::MCParticleObj(const MCParticleObj& other) :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    , data(other.data), m_startVertex(nullptr), m_endVertex(nullptr)
{
  if (other.m_startVertex != nullptr) {
     m_startVertex = new ::fcc::ConstGenVertex(*(other.m_startVertex));
  }
  if (other.m_endVertex != nullptr) {
     m_endVertex = new ::fcc::ConstGenVertex(*(other.m_endVertex));
  }

}

MCParticleObj::~MCParticleObj() {
  if (id.index == podio::ObjectID::untracked) {

  }
    if (m_startVertex != nullptr) delete m_startVertex;
    if (m_endVertex != nullptr) delete m_endVertex;

}
} // namespace fcc
