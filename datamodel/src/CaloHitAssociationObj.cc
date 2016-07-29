#include "CaloHitAssociationObj.h"
#include "CaloHitConst.h"
#include "CaloHitConst.h"


namespace fcc {
CaloHitAssociationObj::CaloHitAssociationObj() :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}, data(), m_rec(nullptr)
, m_sim(nullptr)

{ }

CaloHitAssociationObj::CaloHitAssociationObj(const podio::ObjectID id, CaloHitAssociationData data) :
    ObjBase{id,0}, data(data)
{ }

CaloHitAssociationObj::CaloHitAssociationObj(const CaloHitAssociationObj& other) :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    , data(other.data), m_rec(nullptr), m_sim(nullptr)
{
  if (other.m_rec != nullptr) {
     m_rec = new ::fcc::ConstCaloHit(*(other.m_rec));
  }
  if (other.m_sim != nullptr) {
     m_sim = new ::fcc::ConstCaloHit(*(other.m_sim));
  }

}

CaloHitAssociationObj::~CaloHitAssociationObj() {
  if (id.index == podio::ObjectID::untracked) {

  }
    if (m_rec != nullptr) delete m_rec;
    if (m_sim != nullptr) delete m_sim;

}
} // namespace fcc
