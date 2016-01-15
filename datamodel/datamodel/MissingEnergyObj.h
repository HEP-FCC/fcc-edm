#ifndef MissingEnergyOBJ_H
#define MissingEnergyOBJ_H

// std includes
#include <atomic>
#include <iostream>

// data model specific includes
#include "podio/ObjBase.h"
#include "MissingEnergyData.h"



// forward declarations
class MissingEnergy;
class ConstMissingEnergy;



class MissingEnergyObj : public podio::ObjBase {
public:
  /// constructor
  MissingEnergyObj();
  /// copy constructor (does a deep-copy of relation containers)
  MissingEnergyObj(const MissingEnergyObj&);
  /// constructor from ObjectID and MissingEnergyData
  /// does not initialize the internal relation containers
  MissingEnergyObj(const podio::ObjectID id, MissingEnergyData data);
  virtual ~MissingEnergyObj();

public:
  MissingEnergyData data;


};



#endif
