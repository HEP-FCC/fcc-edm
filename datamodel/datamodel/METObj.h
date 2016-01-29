#ifndef METOBJ_H
#define METOBJ_H

// std includes
#include <atomic>
#include <iostream>

// data model specific includes
#include "podio/ObjBase.h"
#include "METData.h"



// forward declarations
class MET;
class ConstMET;


namespace fcc {
class METObj : public podio::ObjBase {
public:
  /// constructor
  METObj();
  /// copy constructor (does a deep-copy of relation containers)
  METObj(const METObj&);
  /// constructor from ObjectID and METData
  /// does not initialize the internal relation containers
  METObj(const podio::ObjectID id, METData data);
  virtual ~METObj();

public:
  METData data;


};
} // namespace fcc


#endif
