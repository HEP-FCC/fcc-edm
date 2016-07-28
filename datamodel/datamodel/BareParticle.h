#ifndef BareParticle_H
#define BareParticle_H
#include "LorentzVector.h"
#include "Point.h"


#include <iostream>

namespace fcc {
class BareParticle {
public:
  unsigned bits;
  int charge;
 ::fcc::LorentzVector p4;
  unsigned status;
  int type;
 ::fcc::Point vertex;


};



} // namespace fcc

#endif
