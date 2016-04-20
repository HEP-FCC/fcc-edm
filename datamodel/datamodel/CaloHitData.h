#ifndef CaloHitDATA_H
#define CaloHitDATA_H

// A calorimeter hit
// author: C. Bernet, B. Hegner

#include "BareHit.h"

namespace fcc {
class CaloHitData {
public:
  fcc::BareHit Core;  ///< contains basic hit information
};
} // namespace fcc

#endif
