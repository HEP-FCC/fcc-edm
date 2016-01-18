#ifndef VertexOBJ_H
#define VertexOBJ_H

// std includes
#include <atomic>
#include <iostream>

// data model specific includes
#include "podio/ObjBase.h"
#include "VertexData.h"



// forward declarations
class Vertex;
class ConstVertex;



class VertexObj : public podio::ObjBase {
public:
  /// constructor
  VertexObj();
  /// copy constructor (does a deep-copy of relation containers)
  VertexObj(const VertexObj&);
  /// constructor from ObjectID and VertexData
  /// does not initialize the internal relation containers
  VertexObj(const podio::ObjectID id, VertexData data);
  virtual ~VertexObj();

public:
  VertexData data;


};



#endif
