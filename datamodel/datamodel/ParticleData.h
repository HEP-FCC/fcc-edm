#ifndef ParticleDATA_H
#define ParticleDATA_H

#include "BareParticle.h"

namespace fcc {
/** @class ParticleData
 *  Reconstructed particle
 *  @author: C. Bernet, B. Hegner
 */

class ParticleData {
public:
  fcc::BareParticle core;  ///< Contains basic particle information.
  unsigned int tracks_begin;
  unsigned int tracks_end;
  unsigned int clusters_begin;
  unsigned int clusters_end;
};
} // namespace fcc

#endif
