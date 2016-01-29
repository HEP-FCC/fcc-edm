#ifndef GenVertexOBJ_H
#define GenVertexOBJ_H

// std includes
#include <atomic>
#include <iostream>

// data model specific includes
#include "podio/ObjBase.h"
#include "GenVertexData.h"



// forward declarations
class GenVertex;
class ConstGenVertex;


namespace fcc {
class GenVertexObj : public podio::ObjBase {
public:
  /// constructor
  GenVertexObj();
  /// copy constructor (does a deep-copy of relation containers)
  GenVertexObj(const GenVertexObj&);
  /// constructor from ObjectID and GenVertexData
  /// does not initialize the internal relation containers
  GenVertexObj(const podio::ObjectID id, GenVertexData data);
  virtual ~GenVertexObj();

public:
  GenVertexData data;


};
} // namespace fcc


#endif
