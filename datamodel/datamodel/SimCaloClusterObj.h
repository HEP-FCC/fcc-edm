#ifndef SimCaloClusterOBJ_H
#define SimCaloClusterOBJ_H

// std includes
#include <atomic>
#include <iostream>

// data model specific includes
#include "podio/ObjBase.h"
#include "SimCaloClusterData.h"



// forward declarations
class SimCaloCluster;
class ConstSimCaloCluster;



class SimCaloClusterObj : public podio::ObjBase {
public:
  /// constructor
  SimCaloClusterObj();
  /// copy constructor (does a deep-copy of relation containers)
  SimCaloClusterObj(const SimCaloClusterObj&);
  /// constructor from ObjectID and SimCaloClusterData
  /// does not initialize the internal relation containers
  SimCaloClusterObj(const podio::ObjectID id, SimCaloClusterData data);
  virtual ~SimCaloClusterObj();

public:
  SimCaloClusterData data;


};



#endif
