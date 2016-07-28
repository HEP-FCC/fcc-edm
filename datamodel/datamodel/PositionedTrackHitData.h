#ifndef PositionedTrackHitDATA_H
#define PositionedTrackHitDATA_H

#include "Point.h"
#include "BareHit.h"

namespace fcc {
/** @class PositionedTrackHitData
 *  A track hit and with its global position
 *  @author: J. Lingemann, B. Hegner
 */

class PositionedTrackHitData {
public:
  fcc::Point position;  ///< The global position
  fcc::BareHit core;  ///< The hit
};
} // namespace fcc

#endif
