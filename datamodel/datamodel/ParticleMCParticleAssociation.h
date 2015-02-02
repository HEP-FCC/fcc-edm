#ifndef ParticleMCParticleAssociation_H 
#define ParticleMCParticleAssociation_H

// Reference to the Monte-Carlo particle
// author: C. Bernet, B. Hegner

#include "datamodel/ParticleHandle.h"
#include "datamodel/MCParticleHandle.h"


class ParticleMCParticleAssociation {
public:
  ParticleHandle Rec; //Reference to the reconstructed particle 
  MCParticleHandle Sim; //Reference to the Monte-Carlo particle 

};

#endif