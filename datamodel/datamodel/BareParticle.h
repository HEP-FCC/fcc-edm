#ifndef BareParticle_H
#define BareParticle_H
#include "LorentzVector.h"
#include "Point.h"


namespace fcc {
class BareParticle {
public:
  unsigned Status;
  int Charge;
  int Type;
 ::fcc::LorentzVector P4;
 ::fcc::Point Vertex;
  unsigned Bits;

};
} // namespace fcc
#endif
