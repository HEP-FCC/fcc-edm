#ifndef BareParticle_H
#define BareParticle_H
#include "LorentzVector.h"
#include "Point.h"


namespace fcc {
class BareParticle {
public:
  unsigned Bits;
  int Charge;
 ::fcc::LorentzVector P4;
  unsigned Status;
  int Type;
 ::fcc::Point Vertex;


};
} // namespace fcc
#endif
