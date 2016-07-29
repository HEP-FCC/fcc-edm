#ifndef ConstVertex_H
#define ConstVertex_H
#include "Point.h"
#include "VertexData.h"
#include <vector>
#include "WeightedTrack.h"
#include <vector>
#include "podio/ObjectID.h"

//forward declarations


#include "VertexObj.h"

namespace fcc {

class VertexObj;
class Vertex;
class VertexCollection;
class VertexCollectionIterator;

/** @class ConstVertex
 *  Vertex reconstructed from tracks
 *  @author: C. Bernet, B. Hegner
 */

class ConstVertex {

  friend Vertex;
  friend VertexCollection;
  friend VertexCollectionIterator;

public:

  /// default constructor
  ConstVertex();
  ConstVertex(float chi2,unsigned ndf,fcc::Point position,unsigned bits);

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

  /// Access the  chi2 returned by the vertex fit
  const float& chi2() const;
  /// Access the  Number of degrees of freedom of the vertex fit
  const unsigned& ndf() const;
  /// Access the  Vertex position in cm
  const fcc::Point& position() const;
  /// Access the member of  Vertex position in cm
  const float& x() const;
  /// Access the member of  Vertex position in cm
  const float& y() const;
  /// Access the member of  Vertex position in cm
  const float& z() const;
  /// Access the  Stored flags
  const unsigned& bits() const;

  unsigned int tracks_size() const;
  fcc::ConstWeightedTrack tracks(unsigned int) const;
  std::vector<fcc::ConstWeightedTrack>::const_iterator tracks_begin() const;
  std::vector<fcc::ConstWeightedTrack>::const_iterator tracks_end() const;


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
  bool operator<(const ConstVertex& other) const { return m_obj < other.m_obj  ; }

  const podio::ObjectID getObjectID() const;

private:
  VertexObj* m_obj;

};
} // namespace fcc

#endif
