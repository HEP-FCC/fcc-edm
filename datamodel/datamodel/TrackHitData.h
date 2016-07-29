#ifndef TrackHitDATA_H
#define TrackHitDATA_H

#include "BareHit.h"

namespace fcc {
/** @class TrackHitData
 *  A tracker hit
 *  @author: C. Bernet, B. Hegner
 */

class TrackHitData {
public:
  fcc::BareHit core;  ///< contains basic hit information
};
} // namespace fcc

#endif
