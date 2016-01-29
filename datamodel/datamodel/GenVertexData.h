#ifndef GenVertexDATA_H
#define GenVertexDATA_H

//  Time coordinate in cm
// author: C. Bernet, B. Hegner

#include "Point.h"


namespace fcc {
class GenVertexData {
public:
  fcc::Point Position; /// Vertex position in cm 
  float Ctau; /// Time coordinate in cm 

};
} // namespace fcc

#endif
