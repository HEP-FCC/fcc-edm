#ifndef BareParticle_H 
#define BareParticle_H

#include "datamodel/LorentzVector.h"
#include "datamodel/Point.h"


class BareParticle {
public:
  unsigned Status;
  int Charge;
  int Type;
  LorentzVector P4;
  Point Vertex;
  unsigned Bits;

};

#endif