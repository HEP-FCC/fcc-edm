#ifndef BareParticle_H
#define BareParticle_H
#include "LorentzVector.h"
#include "Point.h"



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
