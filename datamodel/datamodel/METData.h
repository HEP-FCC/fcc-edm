#ifndef METDATA_H
#define METDATA_H

//  Corresponding sum pT or sum ET
// author: C. Bernet, B. Hegner



namespace fcc {
class METData {
public:
  float Magnitude; /// Magnitude (could be the pT or the ET of the MET vector) 
  float Phi; /// Azimuthal angle 
  float ScalarSum; /// Corresponding sum pT or sum ET 

};
} // namespace fcc

#endif
