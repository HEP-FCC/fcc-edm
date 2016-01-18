#ifndef CaloClusterOBJ_H
#define CaloClusterOBJ_H

// std includes
#include <atomic>
#include <iostream>

// data model specific includes
#include "podio/ObjBase.h"
#include "CaloClusterData.h"



// forward declarations
class CaloCluster;
class ConstCaloCluster;



class CaloClusterObj : public podio::ObjBase {
public:
  /// constructor
  CaloClusterObj();
  /// copy constructor (does a deep-copy of relation containers)
  CaloClusterObj(const CaloClusterObj&);
  /// constructor from ObjectID and CaloClusterData
  /// does not initialize the internal relation containers
  CaloClusterObj(const podio::ObjectID id, CaloClusterData data);
  virtual ~CaloClusterObj();

public:
  CaloClusterData data;


};



#endif
