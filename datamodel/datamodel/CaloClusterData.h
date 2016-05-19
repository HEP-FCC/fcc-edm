#ifndef CaloClusterDATA_H
#define CaloClusterDATA_H

// A calo cluster, made of CaloHits
// author: C. Bernet, B. Hegner

#include "BareCluster.h"

namespace fcc {
class CaloClusterData {
public:
  fcc::BareCluster Core;  ///< contains basic cluster information
};
} // namespace fcc

#endif
