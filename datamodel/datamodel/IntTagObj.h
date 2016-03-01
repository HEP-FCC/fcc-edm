#ifndef IntTagOBJ_H
#define IntTagOBJ_H

// std includes
#include <atomic>
#include <iostream>

// data model specific includes
#include "podio/ObjBase.h"
#include "IntTagData.h"



// forward declarations
class IntTag;
class ConstIntTag;


namespace fcc {
class IntTagObj : public podio::ObjBase {
public:
  /// constructor
  IntTagObj();
  /// copy constructor (does a deep-copy of relation containers)
  IntTagObj(const IntTagObj&);
  /// constructor from ObjectID and IntTagData
  /// does not initialize the internal relation containers
  IntTagObj(const podio::ObjectID id, IntTagData data);
  virtual ~IntTagObj();

public:
  IntTagData data;


};
} // namespace fcc


#endif
