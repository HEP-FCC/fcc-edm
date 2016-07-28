#ifndef JetDATA_H
#define JetDATA_H

#include "BareJet.h"

namespace fcc {
/** @class JetData
 *  Reconstructed jet.
 *  @author: C. Bernet, B. Hegner
 */

class JetData {
public:
  fcc::BareJet core;  ///< Basic jet information.
  unsigned int particles_begin;
  unsigned int particles_end;
};
} // namespace fcc

#endif
