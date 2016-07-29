#include "TaggedJetObj.h"
#include "JetConst.h"


namespace fcc {
TaggedJetObj::TaggedJetObj() :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}, data(), m_jet(nullptr)

{ }

TaggedJetObj::TaggedJetObj(const podio::ObjectID id, TaggedJetData data) :
    ObjBase{id,0}, data(data)
{ }

TaggedJetObj::TaggedJetObj(const TaggedJetObj& other) :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    , data(other.data), m_jet(nullptr)
{
  if (other.m_jet != nullptr) {
     m_jet = new ::fcc::ConstJet(*(other.m_jet));
  }

}

TaggedJetObj::~TaggedJetObj() {
  if (id.index == podio::ObjectID::untracked) {

  }
    if (m_jet != nullptr) delete m_jet;

}
} // namespace fcc
