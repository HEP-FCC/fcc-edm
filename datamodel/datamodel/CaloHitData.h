#ifndef CaloHitDATA_H
#define CaloHitDATA_H

#include "BareHit.h"

namespace fcc {
/** @class CaloHitData
 *  A calorimeter hit
 *  @author: C. Bernet, B. Hegner
 */

class CaloHitData {
public:
  fcc::BareHit core;  ///< contains basic hit information
};
} // namespace fcc

#endif
