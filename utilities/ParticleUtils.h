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
class ConstParticle;
class MCParticle;
struct BareParticle;
class ParticleCollection;
class LorentzVector;
}

namespace utils {
  // Seeing as this may not be correct for particles outside of collections,
  // we decided to implement this as non-member function for now...
  bool compareParticles(const fcc::ConstParticle& lhs, const fcc::ConstParticle& rhs);

  /// returns the ParticleHandles that are in p1s but not in p2s.
  ///
  /// This algorithm preserves ordering and possible duplications in p1s.
  std::vector<fcc::ConstParticle> unused(const fcc::ParticleCollection& p1s,
                                         const std::vector<fcc::ConstParticle>& p2s);

  /// returns the ParticleHandles from ps that are in a cone around lv.
  std::vector<fcc::ConstParticle> inCone(const fcc::LorentzVector& lv,
                                         const fcc::ParticleCollection& ps,
                                         float deltaRMax,
                                         float exclusion=1e-5);

  /// returns the scalar sum pT of the particles in ps
  float sumPt(const std::vector<fcc::ConstParticle>& ps);

  /// returns the scalar sum p of the particles in ps
  float sumP(const std::vector<fcc::ConstParticle>& ps);

  /// returns the sum of the p4 of the particles in ps
  TLorentzVector sumP4(const std::vector<fcc::ConstParticle>& ps);

}

std::ostream& operator<<(std::ostream& out, const fcc::BareParticle& ptc);
std::ostream& operator<<(std::ostream& out, const fcc::Particle& ptc);
std::ostream& operator<<(std::ostream& out, const fcc::ConstParticle& ptc);
std::ostream& operator<<(std::ostream& out, const fcc::MCParticle& ptc);
#endif
