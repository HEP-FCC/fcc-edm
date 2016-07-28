#include "TaggedGenJetObj.h"
#include "GenJetConst.h"


namespace fcc {
TaggedGenJetObj::TaggedGenJetObj() :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}, data(), m_jet(nullptr)

{ }

TaggedGenJetObj::TaggedGenJetObj(const podio::ObjectID id, TaggedGenJetData data) :
    ObjBase{id,0}, data(data)
{ }

TaggedGenJetObj::TaggedGenJetObj(const TaggedGenJetObj& other) :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    , data(other.data), m_jet(nullptr)
{
  if (other.m_jet != nullptr) {
     m_jet = new ::fcc::ConstGenJet(*(other.m_jet));
  }

}

TaggedGenJetObj::~TaggedGenJetObj() {
  if (id.index == podio::ObjectID::untracked) {

  }
    if (m_jet != nullptr) delete m_jet;

}
} // namespace fcc
