#ifndef TrackStateDATA_H
#define TrackStateDATA_H



namespace fcc {
/** @class TrackStateData
 *  Track state at a given point on the track.
 *  @author: C. Bernet, B. Hegner
 */

class TrackStateData {
public:
  float location;  ///< Location on the track. (Radius?)
  float omega;  ///< Track curvature in cm.
  float d0;  ///< Transverse impact parameter
  float z0;  ///< Longitudinal impact parameter
};
} // namespace fcc

#endif
