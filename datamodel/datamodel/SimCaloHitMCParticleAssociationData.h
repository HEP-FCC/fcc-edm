#ifndef SimCaloHitMCParticleAssociationDATA_H
#define SimCaloHitMCParticleAssociationDATA_H

// Association between a SimCaloHit and a particle that contributed to the hit.
// author: C. Bernet, B. Hegner



namespace fcc {
class SimCaloHitMCParticleAssociationData {
public:
  float Fraction;  ///< Fraction of the particle energy used in the hit.
};
} // namespace fcc

#endif
