#ifndef Vertex_H
#define Vertex_H
#include "Point.h"
#include "VertexData.h"
#include <vector>
#include "podio/ObjectID.h"

// Vertex reconstructed from tracks
// author: C. Bernet, B. Hegner

//forward declarations


#include "VertexConst.h"
#include "VertexObj.h"

namespace fcc {

class VertexCollection;
class VertexCollectionIterator;
class ConstVertex;

class Vertex {

  friend VertexCollection;
  friend VertexCollectionIterator;
  friend ConstVertex;

public:

  /// default constructor
  Vertex();
  Vertex(float Chi2,unsigned Ndf,fcc::Point Position,unsigned Bits);

  /// constructor from existing VertexObj
  Vertex(VertexObj* obj);
  /// copy constructor
  Vertex(const Vertex& other);
  /// copy-assignment operator
  Vertex& operator=(const Vertex& other);
  /// support cloning (deep-copy)
  Vertex clone() const;
  /// destructor
  ~Vertex();

  /// conversion to const object
  operator ConstVertex () const;

public:

  const float& Chi2() const;
  const unsigned& Ndf() const;
  const fcc::Point& Position() const;
  const unsigned& Bits() const;

  void Chi2(float value);

  void Ndf(unsigned value);

  fcc::Point& Position();
  void Position(class fcc::Point value);
  void Bits(unsigned value);




  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from VertexObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const Vertex& other) const {
    return (m_obj==other.m_obj);
  }

  bool operator==(const ConstVertex& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const Vertex& p1,
//       const Vertex& p2 );
  bool operator<(const Vertex& other) const { return m_obj < other.m_obj  ; }

  const podio::ObjectID getObjectID() const;

private:
  VertexObj* m_obj;

};

} // namespace fcc

#endif
