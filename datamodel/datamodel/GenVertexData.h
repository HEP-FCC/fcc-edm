#ifndef GenVertexDATA_H
#define GenVertexDATA_H

#include "Point.h"

namespace fcc {
/** @class GenVertexData
 *  Generated vertex. MCParticles refer to their start and end vertex.
 *  @author: C. Bernet, B. Hegner
 */

class GenVertexData {
public:
  fcc::Point position;  ///< Vertex position in cm
  float ctau;  ///< Time coordinate in cm
};
} // namespace fcc

#endif
