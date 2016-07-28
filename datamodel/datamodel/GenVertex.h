#ifndef GenVertex_H
#define GenVertex_H
#include "Point.h"
#include "GenVertexData.h"
#include <vector>
#include "podio/ObjectID.h"

//forward declarations


#include "GenVertexConst.h"
#include "GenVertexObj.h"

namespace fcc {

class GenVertexCollection;
class GenVertexCollectionIterator;
class ConstGenVertex;

/** @class GenVertex
 *  Generated vertex. MCParticles refer to their start and end vertex.
 *  @author: C. Bernet, B. Hegner
 */
class GenVertex {

  friend GenVertexCollection;
  friend GenVertexCollectionIterator;
  friend ConstGenVertex;

public:

  /// default constructor
  GenVertex();
  GenVertex(fcc::Point position,float ctau);

  /// constructor from existing GenVertexObj
  GenVertex(GenVertexObj* obj);
  /// copy constructor
  GenVertex(const GenVertex& other);
  /// copy-assignment operator
  GenVertex& operator=(const GenVertex& other);
  /// support cloning (deep-copy)
  GenVertex clone() const;
  /// destructor
  ~GenVertex();

  /// conversion to const object
  operator ConstGenVertex () const;

public:

  /// Access the  Vertex position in cm
  const fcc::Point& position() const;
  /// Access the member of  Vertex position in cm
  const float& x() const;
  /// Access the member of  Vertex position in cm
  const float& y() const;
  /// Access the member of  Vertex position in cm
  const float& z() const;
  /// Access the  Time coordinate in cm
  const float& ctau() const;

  /// Get reference to the  Vertex position in cm
  fcc::Point& position();
  /// Set the  Vertex position in cm
  void position(class fcc::Point value);
  /// Set the  member of  Vertex position in cm
  void x(float value);

  /// Set the  member of  Vertex position in cm
  void y(float value);

  /// Set the  member of  Vertex position in cm
  void z(float value);

  /// Set the  Time coordinate in cm
  void ctau(float value);




  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from GenVertexObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const GenVertex& other) const {
    return (m_obj==other.m_obj);
  }

  bool operator==(const ConstGenVertex& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const GenVertex& p1,
//       const GenVertex& p2 );
  bool operator<(const GenVertex& other) const { return m_obj < other.m_obj  ; }

  const podio::ObjectID getObjectID() const;

private:
  GenVertexObj* m_obj;

};

} // namespace fcc

#endif
