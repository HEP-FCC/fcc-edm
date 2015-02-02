#ifndef GenVertex_H 
#define GenVertex_H

// Time coordinate in cm
// author: C. Bernet, B. Hegner

#include "datamodel/Point.h"


class GenVertex {
public:
  Point Position; //Vertex position in cm 
  float Ctau; //Time coordinate in cm 

};

#endif