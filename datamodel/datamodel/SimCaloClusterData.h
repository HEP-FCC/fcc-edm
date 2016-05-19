#ifndef SimCaloClusterDATA_H
#define SimCaloClusterDATA_H

// A simulated calo cluster, made of SimCaloHits
// author: C. Bernet, B. Hegner

#include "BareCluster.h"

namespace fcc {
class SimCaloClusterData {
public:
  fcc::BareCluster Core;  ///< contains basic cluster information.
};
} // namespace fcc

#endif
