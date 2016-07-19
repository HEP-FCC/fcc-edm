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


  bool compareParticles(const fcc::Particle& lhs, const fcc::Particle& rhs) {
    const podio::ObjectID lhsId = lhs.getObjectID();
    const podio::ObjectID rhsId = rhs.getObjectID();
    if (lhsId.collectionID == rhsId.collectionID) {
      return lhsId.index < rhsId.index;
    }
    return lhsId.collectionID < rhsId.collectionID;
  }

  std::vector<fcc::Particle> unused(const fcc::ParticleCollection& p1s,
                                    const std::vector<fcc::Particle>& p2s) {
    std::vector<fcc::Particle> results;
    std::set<fcc::Particle, std::function<bool(const fcc::Particle&, const fcc::Particle&)>> p2set(compareParticles);
    std::copy( p2s.begin(), p2s.end(),
               std::inserter( p2set, p2set.end() ) );
    // std::cout<<"set"<<std::endl;
    // for(const auto& particle : p2set) {
    //  std::cout<<particle.containerID()<<" "<<particle.index()<<std::endl;
    // }
    // std::cout<<"particles"<<std::endl;
    for(const auto& particle : p1s) {
      // std::cout<<particle.containerID()<<" "<<particle.index()<<std::endl;
      if( p2set.find(particle) == p2set.end() ) {
        // std::cout<<"not found"<<std::endl;
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
      float dR2 = deltaR2(lv, particle.Core().P4);
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
      TLorentzVector lv = lvFromPOD( particle.Core().P4 );
      sum += lv;
    }
    return sum;
  }


} // namespace

std::ostream& operator<<(std::ostream& out, const fcc::BareParticle& ptc) {
  if(not out) return out;
  TLorentzVector p4 = utils::lvFromPOD(ptc.P4);
  out<< "particle PDG ID " << ptc.Type
     << " e " << p4.E()
     << " pt " << p4.Pt()
     << " eta " << p4.Eta()
     << " phi " << p4.Phi();
  return out;
}

std::ostream& operator<<(std::ostream& out, const fcc::Particle& ptc) {
  if(not out) return out;
  operator<<(out, ptc.Core());
  return out;
}

std::ostream& operator<<(std::ostream& out, const fcc::MCParticle& ptc) {
  if(not out) return out;
  operator<<(out, ptc.Core());
  out << " startVertex ID: (" << ptc.StartVertex().getObjectID().collectionID;
  out << ", " << ptc.StartVertex().getObjectID().index << ")";
  out << " endVertex ID: (" << ptc.EndVertex().getObjectID().collectionID;
  out << ", " << ptc.StartVertex().getObjectID().index << ")";
  return out;
}
