#ifndef SimCaloHitOBJ_H
#define SimCaloHitOBJ_H

// std includes
#include <atomic>
#include <iostream>

// data model specific includes
#include "podio/ObjBase.h"
#include "SimCaloHitData.h"



// forward declarations
class SimCaloHit;
class ConstSimCaloHit;



class SimCaloHitObj : public podio::ObjBase {
public:
  /// constructor
  SimCaloHitObj();
  /// copy constructor (does a deep-copy of relation containers)
  SimCaloHitObj(const SimCaloHitObj&);
  /// constructor from ObjectID and SimCaloHitData
  /// does not initialize the internal relation containers
  SimCaloHitObj(const podio::ObjectID id, SimCaloHitData data);
  virtual ~SimCaloHitObj();

public:
  SimCaloHitData data;


};



#endif
