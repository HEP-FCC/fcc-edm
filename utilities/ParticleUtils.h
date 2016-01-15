#ifndef UTILS_PARTICLE_H
#define UTILS_PARTICLE_H

#include <vector>
#include <iostream>

#include "TLorentzVector.h"

class Particle;
class ParticleCollection;
class LorentzVector;

namespace utils {
  // Seeing as this may not be correct for particles outside of collections,
  // we decided to implement this as non-member function for now...
  bool compareParticles(const Particle& lhs, const Particle& rhs);

  /// returns the ParticleHandles that are in p1s but not in p2s.
  ///
  /// This algorithm preserves ordering and possible duplications in p1s.
  std::vector<Particle> unused(const ParticleCollection& p1s,
                               const std::vector<Particle>& p2s);

  /// returns the ParticleHandles from ps that are in a cone around lv.
  std::vector<Particle> inCone(const LorentzVector& lv,
                               const ParticleCollection& ps,
                               float deltaRMax,
                               float exclusion=1e-5);

  /// returns the scalar sum pT of the particles in ps
  float sumPt(const std::vector<Particle>& ps);

  /// returns the scalar sum p of the particles in ps
  float sumP(const std::vector<Particle>& ps);

  /// returns the sum of the p4 of the particles in ps
  TLorentzVector sumP4(const std::vector<Particle>& ps);

}

std::ostream& operator<<(std::ostream& out, const Particle& ptc);

#endif
