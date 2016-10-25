#include "VectorUtils.h"

#include "TLorentzVector.h"
#include "datamodel/LorentzVector.h"

#include <cmath>

namespace utils {

  TLorentzVector lvFromPOD(const fcc::LorentzVector& lv) {
    TLorentzVector tlv; // COLIN need to fill it
    tlv.SetXYZM( lv.px, lv.py, lv.pz, lv.mass);
    return tlv;
  }

  fcc::LorentzVector lvToPOD(const TLorentzVector& tlv) {
    fcc::LorentzVector lv; // COLIN need to fill it
    lv.px = tlv.Px();
    lv.py = tlv.Py();
    lv.pz = tlv.Pz();
    lv.mass = tlv.M();
    return lv;
  }

  float deltaEta(const fcc::LorentzVector& lv1, const fcc::LorentzVector& lv2) {
    TLorentzVector tlv1 = lvFromPOD(lv1);
    TLorentzVector tlv2 = lvFromPOD(lv2);
    return tlv1.Eta() - tlv2.Eta();
  }

  float deltaPhi(const fcc::LorentzVector& lv1, const fcc::LorentzVector& lv2) {
    TLorentzVector tlv1 = lvFromPOD(lv1);
    TLorentzVector tlv2 = lvFromPOD(lv2);
    double result = tlv1.Phi() - tlv2.Phi();
    while (result > M_PI) result -= 2*M_PI;
    while (result <= -M_PI) result += 2*M_PI;
    return result;
  }

  float deltaR2(const fcc::LorentzVector& lv1, const fcc::LorentzVector& lv2) {
    float dphi = deltaPhi(lv1, lv2);
    float deta = deltaEta(lv1, lv2);
    return dphi*dphi + deta*deta;
  }

  float deltaR(const fcc::LorentzVector& lv1, const fcc::LorentzVector& lv2) {
    return sqrt( deltaR2(lv1, lv2) );
  }







} // namespace
