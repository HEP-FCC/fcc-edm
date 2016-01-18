#ifndef TrackStateDATA_H
#define TrackStateDATA_H

//  Longitudinal impact parameter
// author: C. Bernet, B. Hegner




class TrackStateData {
public:
  float Location; /// Location on the track. (Radius?) 
  float Omega; /// Track curvature in cm. 
  float D0; /// Transverse impact parameter 
  float Z0; /// Longitudinal impact parameter 

};


#endif
