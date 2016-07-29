#ifndef TaggedJetDATA_H
#define TaggedJetDATA_H



namespace fcc {
/** @class TaggedJetData
 *  Association between a Jet and arbitrary Tag information
 *  @author: C. Bernet, Z. Drasal, J. Lingemann
 */

class TaggedJetData {
public:
  float tag;  ///< Result of the tagging algorithm
};
} // namespace fcc

#endif
