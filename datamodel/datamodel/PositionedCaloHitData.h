#ifndef PositionedCaloHitDATA_H
#define PositionedCaloHitDATA_H

#include "Point.h"
#include "BareHit.h"

namespace fcc {
/** @class PositionedCaloHitData
 *  A calorimeter hit with its global position
 *  @author: J. Lingemann, B. Hegner
 */

class PositionedCaloHitData {
public:
  fcc::Point position;  ///< The global position
  fcc::BareHit core;  ///< The hit
};
} // namespace fcc

#endif
