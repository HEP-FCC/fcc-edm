#include "utilities/JetUtils.h"

#include "datamodel/Particle.h"
#include "datamodel/Jet.h"
#include "datamodel/JetParticleAssociationCollection.h"
#include <iostream>

namespace utils {

  std::vector<fcc::Particle> associatedParticles( const fcc::Jet& jet,
                                                  const fcc::JetParticleAssociationCollection& associations ) {

    std::vector<fcc::Particle> result;
    if(not jet.isAvailable()) {
      std::cerr<<"Jet handle is not available"<<std::endl;
      return result;
      // COLIN should throw an exception
    }
    for(const auto& assoc : associations){
      if( assoc.Jet() == jet ) {
        result.emplace_back(assoc.Particle().Core());
      }
    }
    return result;
  }

} // namespace
