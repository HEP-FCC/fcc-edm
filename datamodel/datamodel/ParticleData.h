#ifndef ParticleDATA_H
#define ParticleDATA_H

// Reconstructed particle
// author: C. Bernet, B. Hegner

#include "BareParticle.h"

namespace fcc {
class ParticleData {
public:
  fcc::BareParticle Core;  ///< Contains basic particle information.
};
} // namespace fcc

#endif
