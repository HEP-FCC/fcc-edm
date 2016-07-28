#ifndef MCParticleDATA_H
#define MCParticleDATA_H

#include "BareParticle.h"

namespace fcc {
/** @class MCParticleData
 *  Monte-Carlo Particle, either generated or simulated.
 *  @author: C. Bernet, B. Hegner
 */

class MCParticleData {
public:
  fcc::BareParticle core;  ///< Basic particle information.
};
} // namespace fcc

#endif
