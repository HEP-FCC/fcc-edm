#ifndef UTILS_JET_H
#define UTILS_JET_H

#include <vector>

namespace fcc {
class Particle;
class Jet;
class JetParticleAssociationCollection;
}

namespace utils {

  std::vector<fcc::Particle> associatedParticles( const fcc::Jet& jet,
                                             	  const fcc::JetParticleAssociationCollection& associations );
}

#endif
