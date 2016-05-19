#ifndef TrackStateDATA_H
#define TrackStateDATA_H

// Track state at a given point on the track.
// author: C. Bernet, B. Hegner



namespace fcc {
class TrackStateData {
public:
  float Location;  ///< Location on the track. (Radius?)
  float Omega;  ///< Track curvature in cm.
  float D0;  ///< Transverse impact parameter
  float Z0;  ///< Longitudinal impact parameter
};
} // namespace fcc

#endif
