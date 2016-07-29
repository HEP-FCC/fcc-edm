#ifndef CaloHitMCParticleAssociationDATA_H
#define CaloHitMCParticleAssociationDATA_H



namespace fcc {
/** @class CaloHitMCParticleAssociationData
 *  Association between a CaloHit and a particle that contributed to the hit.
 *  @author: C. Bernet, B. Hegner
 */

class CaloHitMCParticleAssociationData {
public:
  float fraction;  ///< Fraction of the particle energy used in the hit.
};
} // namespace fcc

#endif
