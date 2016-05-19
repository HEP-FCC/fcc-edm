#ifndef ConstGenVertex_H
#define ConstGenVertex_H
#include "Point.h"
#include "GenVertexData.h"
#include <vector>
#include "podio/ObjectID.h"

// Generated vertex. MCParticles refer to their start and end vertex.
// author: C. Bernet, B. Hegner

//forward declarations


#include "GenVertexObj.h"

namespace fcc {

class GenVertexObj;
class GenVertex;
class GenVertexCollection;
class GenVertexCollectionIterator;

class ConstGenVertex {

  friend GenVertex;
  friend GenVertexCollection;
  friend GenVertexCollectionIterator;

public:

  /// default constructor
  ConstGenVertex();
  ConstGenVertex(fcc::Point Position,float Ctau);

  /// constructor from existing GenVertexObj
  ConstGenVertex(GenVertexObj* obj);
  /// copy constructor
  ConstGenVertex(const ConstGenVertex& other);
  /// copy-assignment operator
  ConstGenVertex& operator=(const ConstGenVertex& other);
  /// support cloning (deep-copy)
  ConstGenVertex clone() const;
  /// destructor
  ~ConstGenVertex();


public:

  const fcc::Point& Position() const;
  const float& Ctau() const;



  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from GenVertexObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const ConstGenVertex& other) const {
       return (m_obj==other.m_obj);
  }

  bool operator==(const GenVertex& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const GenVertex& p1,
//       const GenVertex& p2 );
  bool operator<(const ConstGenVertex& other) const { return m_obj < other.m_obj  ; }

  const podio::ObjectID getObjectID() const;

private:
  GenVertexObj* m_obj;

};
} // namespace fcc

#endif
