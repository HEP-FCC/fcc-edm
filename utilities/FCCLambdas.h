
#ifndef  FCC_UTILITYLAMBDAS_H
#define  FCC_UTILITYLAMBDAS_H

#include <cmath>
#include <vector>

class TLorentzVector;

namespace fcc {
  class Point;
  class LorentzVector;

  class MCParticleData;
}

/// good luck charm against segfaults
fcc::MCParticleData __magicParticle();

std::vector<float> pt (std::vector<fcc::MCParticleData> in);


std::vector<float> eta(std::vector<fcc::MCParticleData> in);

std::vector<TLorentzVector> tlv(std::vector<fcc::LorentzVector> in);

std::vector<float> r (std::vector<fcc::Point> in); 

std::vector<float> r (std::vector<fcc::Point> in); 


#endif
