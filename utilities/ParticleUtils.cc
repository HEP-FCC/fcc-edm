// local
#include "ParticleUtils.h"
#include "VectorUtils.h"

// podio
#include "podio/ObjectID.h"

// datamodel
#include "datamodel/Particle.h"
#include "datamodel/MCParticle.h"
#include "datamodel/BareParticle.h"
#include "datamodel/GenVertex.h"
#include "datamodel/ParticleCollection.h"
#include "datamodel/LorentzVector.h"

// ROOT
#include "TLorentzVector.h"

// STL
#include <set>
#include <functional>
#include <iterator>
#include <iostream>

namespace utils {


  bool compareParticles(const fcc::ConstParticle& lhs, const fcc::ConstParticle& rhs) {
    const podio::ObjectID lhsId = lhs.getObjectID();
    const podio::ObjectID rhsId = rhs.getObjectID();
    if (lhsId.collectionID == rhsId.collectionID) {
      return lhsId.index < rhsId.index;
    }
    return lhsId.collectionID < rhsId.collectionID;
  }

  std::vector<fcc::Particle> unused(const fcc::ParticleCollection& p1s,
                                    const std::vector<fcc::ConstParticle>& p2s) {
    std::vector<fcc::Particle> results;
    std::set<fcc::ConstParticle, std::function<bool(const fcc::ConstParticle&, const fcc::ConstParticle&)>> p2set(compareParticles);
    std::copy( p2s.begin(), p2s.end(),
               std::inserter( p2set, p2set.end() ) );
    for(const auto& particle : p1s) {
      if( p2set.find(particle) == p2set.end() ) {
        results.push_back(particle);
      }
    }
    return results;
  }


  std::vector<fcc::Particle> inCone( const fcc::LorentzVector& lv,
                                     const fcc::ParticleCollection& ps,
                                     float deltaRMax,
                                     float exclusion ) {
    float dR2Max = deltaRMax*deltaRMax;
    float exc2 = exclusion*exclusion;
    std::vector<fcc::Particle> results;
    for(const auto& particle : ps) {
      float dR2 = deltaR2(lv, particle.p4());
      if( dR2>exc2 && dR2 <= dR2Max ) {
        results.emplace_back(particle);
      }
    }
    return results;
  }


  float sumPt(const std::vector<fcc::Particle>& ps) {
    return sumP4(ps).Vect().Pt();
  }


  float sumP(const std::vector<fcc::Particle>& ps) {
    return sumP4(ps).Vect().Mag();
  }


  TLorentzVector sumP4(const std::vector<fcc::Particle>& ps) {
    TLorentzVector sum;
    for(const auto& particle : ps) {
      TLorentzVector lv = lvFromPOD( particle.p4() );
      sum += lv;
    }
    return sum;
  }



std::string to_string(const fcc::BareParticle& ptc) {
  
  TLorentzVector p4 = utils::lvFromPOD(ptc.p4);
  return "particle PDG ID " +  std::to_string(ptc.pdgId)
     + " e " + std::to_string(p4.E())
     + " pt " + std::to_string(p4.Pt())
     + " eta " + std::to_string(p4.Eta())
     + " phi " + std::to_string(p4.Phi());
}

std::string to_string(const fcc::Particle& ptc) {
  return utils::to_string(ptc.core());
}

std::string to_string(const fcc::MCParticle& ptc) {
  return utils::to_string(ptc.core()) +
   " startVertex ID: (" + std::to_string(ptc.startVertex().getObjectID().collectionID) +
  + ", " + std::to_string(ptc.startVertex().getObjectID().index) + ")" +
  " endVertex ID: (" + std::to_string(ptc.endVertex().getObjectID().collectionID) +
   ", " + std::to_string(ptc.endVertex().getObjectID().index) + ")";
}
} // namespace
