#ifndef UTILS_JET_H
#define UTILS_JET_H

#include <vector>

class Particle;
class Jet;
class JetParticleAssociationCollection;

namespace utils {

  std::vector<Particle> associatedParticles( const Jet& jet,
                                             const JetParticleAssociationCollection& associations );
}

#endif
