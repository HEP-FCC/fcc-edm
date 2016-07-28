#ifndef CaloClusterDATA_H
#define CaloClusterDATA_H

#include "BareCluster.h"

namespace fcc {
/** @class CaloClusterData
 *  A calo cluster, made of CaloHits
 *  @author: C. Bernet, B. Hegner
 */

class CaloClusterData {
public:
  fcc::BareCluster core;  ///< contains basic cluster information
  unsigned int hits_begin;
  unsigned int hits_end;
};
} // namespace fcc

#endif
