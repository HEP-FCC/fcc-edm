#ifndef SimCaloClusterHitAssociationOBJ_H
#define SimCaloClusterHitAssociationOBJ_H

// std includes
#include <atomic>
#include <iostream>

// data model specific includes
#include "podio/ObjBase.h"
#include "SimCaloClusterHitAssociationData.h"



// forward declarations
class SimCaloClusterHitAssociation;
class ConstSimCaloClusterHitAssociation;
namespace fcc {class ConstSimCaloCluster;
class ConstSimCaloHit;
}


namespace fcc {
class SimCaloClusterHitAssociationObj : public podio::ObjBase {
public:
  /// constructor
  SimCaloClusterHitAssociationObj();
  /// copy constructor (does a deep-copy of relation containers)
  SimCaloClusterHitAssociationObj(const SimCaloClusterHitAssociationObj&);
  /// constructor from ObjectID and SimCaloClusterHitAssociationData
  /// does not initialize the internal relation containers
  SimCaloClusterHitAssociationObj(const podio::ObjectID id, SimCaloClusterHitAssociationData data);
  virtual ~SimCaloClusterHitAssociationObj();

public:
  SimCaloClusterHitAssociationData data;
  ::fcc::ConstSimCaloCluster* m_Cluster;
  ::fcc::ConstSimCaloHit* m_Hit;


};
} // namespace fcc


#endif
