#include "CaloClusterObj.h"


namespace fcc {
CaloClusterObj::CaloClusterObj() :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}, data(), m_hits(new std::vector<::fcc::ConstCaloHit>())
{ }

CaloClusterObj::CaloClusterObj(const podio::ObjectID id, CaloClusterData data) :
    ObjBase{id,0}, data(data)
{ }

CaloClusterObj::CaloClusterObj(const CaloClusterObj& other) :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    , data(other.data), m_hits(new std::vector<::fcc::ConstCaloHit>(*(other.m_hits)))
{

}

CaloClusterObj::~CaloClusterObj() {
  if (id.index == podio::ObjectID::untracked) {
    delete m_hits;

  }

}
} // namespace fcc
