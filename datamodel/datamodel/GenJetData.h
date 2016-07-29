#ifndef GenJetDATA_H
#define GenJetDATA_H

#include "BareJet.h"

namespace fcc {
/** @class GenJetData
 *  Generated jet.
 *  @author: C. Bernet, B. Hegner
 */

class GenJetData {
public:
  fcc::BareJet core;  ///< Basic jet information.
  unsigned int particles_begin;
  unsigned int particles_end;
};
} // namespace fcc

#endif
