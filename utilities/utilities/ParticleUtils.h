#ifndef UTILS_PARTICLE_H
#define UTILS_PARTICLE_H

// STL
#include <vector>
#include <iostream>
// ROOT
#include "TLorentzVector.h"

// forward declarations:
namespace fcc {
class Particle;
class ParticleCollection;
class LorentzVector;
}

namespace utils {
  // Seeing as this may not be correct for particles outside of collections,
  // we decided to implement this as non-member function for now...
  bool compareParticles(const fcc::Particle& lhs, const fcc::Particle& rhs);

  /// returns the ParticleHandles that are in p1s but not in p2s.
  ///
  /// This algorithm preserves ordering and possible duplications in p1s.
  std::vector<fcc::Particle> unused(const fcc::ParticleCollection& p1s,
                                    const std::vector<fcc::Particle>& p2s);

  /// returns the ParticleHandles from ps that are in a cone around lv.
  std::vector<fcc::Particle> inCone(const fcc::LorentzVector& lv,
                                    const fcc::ParticleCollection& ps,
                                    float deltaRMax,
                                    float exclusion=1e-5);

  /// returns the scalar sum pT of the particles in ps
  float sumPt(const std::vector<fcc::Particle>& ps);

  /// returns the scalar sum p of the particles in ps
  float sumP(const std::vector<fcc::Particle>& ps);

  /// returns the sum of the p4 of the particles in ps
  TLorentzVector sumP4(const std::vector<fcc::Particle>& ps);

}

std::ostream& operator<<(std::ostream& out, const fcc::Particle& ptc);

#endif
