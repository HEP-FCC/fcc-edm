#ifndef UTILS_VECTOR_H
#define UTILS_VECTOR_H

namespace fcc {
class LorentzVector;
}
class TLorentzVector;

namespace utils {

  /// Converts a fcc::LorentzVector POD to a TLorentzVector
  TLorentzVector lvFromPOD(const fcc::LorentzVector& lv);

  /// Converts a TLorentzVector to a fcc::LorentzVector POD
  fcc::LorentzVector lvToPOD(const TLorentzVector& tlv);

  /// difference eta1-eta2
  float deltaEta(const fcc::LorentzVector& lv1, const fcc::LorentzVector& lv2);

  /// difference phi1-phi2
  float deltaEta(const fcc::LorentzVector& lv1, const fcc::LorentzVector& lv2);

  /// dR2.
  ///
  /// Faster than deltaR because no call to sqrt
  float deltaR2(const fcc::LorentzVector& lv1, const fcc::LorentzVector& lv2);

  /// dR
  float deltaR(const fcc::LorentzVector& lv1, const fcc::LorentzVector& lv2);
}

#endif
