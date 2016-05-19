#ifndef TrackClusterDATA_H
#define TrackClusterDATA_H

// A track cluster, made of TrackHits
// author: C. Bernet, B. Hegner

#include "BareCluster.h"

namespace fcc {
class TrackClusterData {
public:
  fcc::BareCluster Core;  ///< contains basic cluster information
};
} // namespace fcc

#endif
