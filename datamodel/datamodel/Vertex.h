#ifndef Vertex_H
#define Vertex_H
#include "Point.h"
#include "VertexData.h"
#include <vector>
#include "WeightedTrack.h"
#include <vector>
#include "podio/ObjectID.h"

//forward declarations


#include "VertexConst.h"
#include "VertexObj.h"

namespace fcc {

class VertexCollection;
class VertexCollectionIterator;
class ConstVertex;

/** @class Vertex
 *  Vertex reconstructed from tracks
 *  @author: C. Bernet, B. Hegner
 */
class Vertex {

  friend VertexCollection;
  friend VertexCollectionIterator;
  friend ConstVertex;

public:

  /// default constructor
  Vertex();
  Vertex(float chi2,unsigned ndf,fcc::Point position,unsigned bits);

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

  /// Set the  chi2 returned by the vertex fit
  void chi2(float value);

  /// Set the  Number of degrees of freedom of the vertex fit
  void ndf(unsigned value);

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

  /// Set the  Stored flags
  void bits(unsigned value);


  void addtracks(fcc::ConstWeightedTrack);
  unsigned int tracks_size() const;
  fcc::ConstWeightedTrack tracks(unsigned int) const;
  std::vector<fcc::ConstWeightedTrack>::const_iterator tracks_begin() const;
  std::vector<fcc::ConstWeightedTrack>::const_iterator tracks_end() const;



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
