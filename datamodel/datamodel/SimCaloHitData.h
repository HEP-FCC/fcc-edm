#ifndef SimCaloHitDATA_H
#define SimCaloHitDATA_H

// A simulated calorimeter hit
// author: C. Bernet, B. Hegner

#include "BareHit.h"

namespace fcc {
class SimCaloHitData {
public:
  fcc::BareHit Core;  ///< contains basic hit information
};
} // namespace fcc

#endif
