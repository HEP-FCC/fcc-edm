#ifndef TrackDATA_H
#define TrackDATA_H



namespace fcc {
/** @class TrackData
 *  Track reconstructed from clusters in the inner tracker
 *  @author: C. Bernet, B. Hegner
 */

class TrackData {
public:
  float chi2;  ///< chi2 returned by the track fit
  unsigned ndf;  ///< Number of degrees of freedom of the track fit
  unsigned bits;  ///< Stores flags
  unsigned int clusters_begin;
  unsigned int clusters_end;
  unsigned int states_begin;
  unsigned int states_end;
};
} // namespace fcc

#endif
