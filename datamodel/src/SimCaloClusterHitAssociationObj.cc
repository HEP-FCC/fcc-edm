#include "SimCaloClusterHitAssociationObj.h"
#include "SimCaloClusterConst.h"
#include "SimCaloHitConst.h"


namespace fcc {
SimCaloClusterHitAssociationObj::SimCaloClusterHitAssociationObj() :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}, data(),m_Cluster(nullptr)
,m_Hit(nullptr)

{ }

SimCaloClusterHitAssociationObj::SimCaloClusterHitAssociationObj(const podio::ObjectID id, SimCaloClusterHitAssociationData data) :
    ObjBase{id,0}, data(data)
{ }

SimCaloClusterHitAssociationObj::SimCaloClusterHitAssociationObj(const SimCaloClusterHitAssociationObj& other) :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    , data(other.data)
{ }

SimCaloClusterHitAssociationObj::~SimCaloClusterHitAssociationObj() {
  if (id.index == podio::ObjectID::untracked) {

  }
    if (m_Cluster != nullptr) delete m_Cluster;
    if (m_Hit != nullptr) delete m_Hit;

}
} // namespace fcc
