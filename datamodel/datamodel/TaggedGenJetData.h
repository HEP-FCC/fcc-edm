#ifndef TaggedGenJetDATA_H
#define TaggedGenJetDATA_H



namespace fcc {
/** @class TaggedGenJetData
 *  Association between a GenJet and arbitrary Tag information
 *  @author: C. Bernet, Z. Drasal
 */

class TaggedGenJetData {
public:
  float tag;  ///< Result of the tagging algorithm
};
} // namespace fcc

#endif
