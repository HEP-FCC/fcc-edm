#ifndef VertexDATA_H
#define VertexDATA_H

#include "Point.h"

namespace fcc {
/** @class VertexData
 *  Vertex reconstructed from tracks
 *  @author: C. Bernet, B. Hegner
 */

class VertexData {
public:
  float chi2;  ///< chi2 returned by the vertex fit
  unsigned ndf;  ///< Number of degrees of freedom of the vertex fit
  fcc::Point position;  ///< Vertex position in cm
  unsigned bits;  ///< Stored flags
  unsigned int tracks_begin;
  unsigned int tracks_end;
};
} // namespace fcc

#endif
