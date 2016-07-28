#ifndef METDATA_H
#define METDATA_H



namespace fcc {
/** @class METData
 *  Naive MET type
 *  @author: C. Bernet, B. Hegner
 */

class METData {
public:
  float magnitude;  ///< Magnitude (could be the pT or the ET of the MET vector)
  float phi;  ///< Azimuthal angle
  float scalarSum;  ///< Corresponding sum pT or sum ET
};
} // namespace fcc

#endif
