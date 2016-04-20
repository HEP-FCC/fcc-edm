#ifndef ConstVertex_H
#define ConstVertex_H
#include "Point.h"
#include "VertexData.h"
#include <vector>
#include "podio/ObjectID.h"

// Vertex reconstructed from tracks
// author: C. Bernet, B. Hegner

//forward declarations


#include "VertexObj.h"

namespace fcc {

class VertexObj;
class Vertex;
class VertexCollection;
class VertexCollectionIterator;

class ConstVertex {

  friend Vertex;
  friend VertexCollection;
  friend VertexCollectionIterator;

public:

  /// default constructor
  ConstVertex();
  ConstVertex(float Chi2,unsigned Ndf,fcc::Point Position,unsigned Bits);

  /// constructor from existing VertexObj
  ConstVertex(VertexObj* obj);
  /// copy constructor
  ConstVertex(const ConstVertex& other);
  /// copy-assignment operator
  ConstVertex& operator=(const ConstVertex& other);
  /// support cloning (deep-copy)
  ConstVertex clone() const;
  /// destructor
  ~ConstVertex();


public:

  const float& Chi2() const;
  const unsigned& Ndf() const;
  const fcc::Point& Position() const;
  const unsigned& Bits() const;



  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from VertexObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const ConstVertex& other) const {
       return (m_obj==other.m_obj);
  }

  bool operator==(const Vertex& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const Vertex& p1,
//       const Vertex& p2 );

  const podio::ObjectID getObjectID() const;

private:
  VertexObj* m_obj;

};
} // namespace fcc

#endif
