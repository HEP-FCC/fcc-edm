#include "utilities/ParticleUtils.h"

#include "datamodel/ParticleHandle.h"
#include "datamodel/LorentzVector.h"

#include "VectorUtils.h"

#include "TLorentzVector.h"
#include <set>
#include <iterator>
#include <iostream>

namespace utils {


  std::vector<ParticleHandle> unused(const std::vector<ParticleHandle>& p1s,
				     const std::vector<ParticleHandle>& p2s) {
    std::vector<ParticleHandle> results;
    std::set<ParticleHandle> p2set;
    std::copy( p2s.begin(), p2s.end(),
	       std::inserter( p2set, p2set.end() ) );
    //    std::cout<<"set"<<std::endl;
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


  std::vector<ParticleHandle> inCone(const LorentzVector& lv,
				     const std::vector<ParticleHandle>& ps,
				     float deltaRMax,
				     float exclusion ) {
    float dR2Max = deltaRMax*deltaRMax;
    float exc2 = exclusion*exclusion;
    std::vector<ParticleHandle> results;
    for(const auto& particle : ps) {
      float dR2 = deltaR2(lv, particle.read().Core.P4);
      if( dR2>exc2 && dR2 <= dR2Max ) {
	results.emplace_back(particle);
      }
    }
    return results;
  }


  float sumPt(const std::vector<ParticleHandle>& ps) {
    return sumP4(ps).Vect().Pt();
  }


  float sumP(const std::vector<ParticleHandle>& ps) {
    return sumP4(ps).Vect().Mag();
  }


  TLorentzVector sumP4(const std::vector<ParticleHandle>& ps) {
    TLorentzVector sum; 
    for(const auto& particle : ps) {
      TLorentzVector lv = lvFromPOD( particle.read().Core.P4 );
      sum += lv;
    }    
    return sum;
  }


} // namespace

std::ostream& operator<<(std::ostream& out, const ParticleHandle& ptc) {
  if(not out) return out;
  const BareParticle& pcore = ptc.read().Core; 
  TLorentzVector p4 = utils::lvFromPOD(pcore.P4);
  out<<"particle ID "<<pcore.Type
     <<" e "<<p4.E()
     <<" pt "<<p4.Pt()
     <<" eta "<<p4.Eta()
     <<" phi "<<p4.Phi();
  return out;
}
