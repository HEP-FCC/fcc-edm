#ifndef TrackClusterDATA_H
#define TrackClusterDATA_H

#include "BareCluster.h"

namespace fcc {
/** @class TrackClusterData
 *  A track cluster, made of TrackHits
 *  @author: C. Bernet, B. Hegner, J. Lingemann
 */

class TrackClusterData {
public:
  fcc::BareCluster core;  ///< contains basic cluster information
  unsigned int hits_begin;
  unsigned int hits_end;
};
} // namespace fcc

#endif
