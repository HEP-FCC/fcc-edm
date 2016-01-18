#include "utilities/DummyGenerator.h"

#include "podio/EventStore.h"

#include <iostream>
#include <cmath>
#include <cassert>

#include "TLorentzVector.h"
#include "TVector3.h"

#include "datamodel/ParticleCollection.h"
#include "datamodel/JetCollection.h"
#include "datamodel/JetParticleAssociationCollection.h"

#include "VectorUtils.h"

DummyGenerator::DummyGenerator(int npart,
                               podio::EventStore& store) :
  m_njets(2), // not used
  m_engine(0xdeadbeef),
  m_pstar(0., 0.3),
  m_phi(-M_PI, M_PI),
  m_theta(0, M_PI),
  m_npart(npart),
  m_uniform(0.,1.),
  m_ptypeprob{0., 0.65, 0.85, 1.},
  m_store(store),
  m_nprint(-1),
  m_ievt(0),
  m_particles(m_store.create<ParticleCollection>("GenParticle")),
  m_jets(m_store.create<JetCollection>("GenJet")),
  m_jetParticleAssociations(m_store.create<JetParticleAssociationCollection>("GenJetParticle"))
  {

}


void DummyGenerator::generate() {
  generate_jet(200., TVector3(1,0,0.5) );
  generate_jet(200., TVector3(-1,0,0.5) );

  // add 50 particles of underlying event
  for(unsigned i=0; i<50; ++i) {
    bool success = false;
    while (not success) {
      auto result = generate_particle();
      success = result.first;
    }
  }

  // add a muon
  TLorentzVector p4;
  p4.SetPtEtaPhiM(20, 2, 0.3, 0.105);
  generate_particle( &p4, 4);

  m_ievt++;
}


void DummyGenerator::generate_jet(float energy, const TVector3& direction) {
  unsigned npart = m_npart(m_engine);
  if(npart<2) return; // cannot have energy momentum conservation with a single particle
  if (m_ievt<m_nprint)
    std::cout<<"generate jet with nparticles = "
             << npart << std::endl;

  auto jet = Jet(); // m_jets.create();
  TLorentzVector p4star;

  // keeping track of all created particles to boost them later on
  std::vector<Particle> particles;

  for(unsigned i=0; i<npart-1; ++i) {
    bool success = false;
    while(not success) {
      auto result = generate_particle();
      if(not result.first)
        continue;
      else {
        Particle& ptc = result.second;
        p4star += utils::lvFromPOD( ptc.Core().P4 );
        JetParticleAssociation assoc = m_jetParticleAssociations.create();
        assoc.Jet(jet);
        assoc.Particle(ptc);
        particles.push_back(ptc);
        success = true;
      }
    }
  }

  // last particle is created to allow vector momentum conservation in jet com frame
  TLorentzVector opposite(-p4star.Vect(), p4star.E());
  auto result = generate_particle(&opposite);
  Particle& ptc = result.second;
  TLorentzVector final = utils::lvFromPOD( ptc.Core().P4 );
  p4star += final;
  JetParticleAssociation assoc = m_jetParticleAssociations.create();
  assoc.Jet(jet);
  assoc.Particle(ptc);
  particles.push_back(ptc);

  // now boosting all particles to lab frame
  TLorentzVector jetlv;
  float gamma = energy/p4star.M();
  float beta = sqrt(1 - 1/(gamma*gamma));
  TVector3 boost(direction.Unit());
  boost *= static_cast<double>(beta);
  for(Particle& ptc : particles) {
    TLorentzVector lv = utils::lvFromPOD( ptc.Core().P4 );
    lv.Boost( boost );
    // BareParticle core = ptc.Core();
    ptc.Core().P4 = utils::lvToPOD(lv);
    // ptc.setCore(core);
    jetlv += lv;
  }
  // BareJet core = jet.Core();
  jet.Core().P4 = utils::lvToPOD(jetlv);
  // std::cout<<"jet "
  //       <<jet.Core().P4.Eta<<" "
  //       <<jet.Core().P4.Phi<<" "
  //       <<jet.Core().P4.Pt<<" "
  //       <<jet.Core().P4.Mass
  //       <<std::endl;

  // jet.setCore( core );
  m_jets.push_back(jet);
}

std::pair<bool, Particle> DummyGenerator::generate_particle(const TLorentzVector* lv, int itype) {

  // particle type and mass
  if (itype == -1) {
    float ftype = m_uniform(m_engine);
    for(unsigned i=0; i<m_ptypeprob.size(); ++i) {
      if(ftype<=m_ptypeprob[i]) {
        itype = i;
        break;
      }
    }
  }
  float mass = 0.;
  switch(itype) {
  case 1:
    mass = 0.135; break;
  case 3:
    mass = 0.497; break;
  case 4:
    mass = 0.105; break;
  default: break;
  }

  LorentzVector lvpod;
  if( lv == nullptr ) {
    float phistar = m_phi(m_engine);
    float thetastar = m_theta(m_engine);
    float costheta = cos(thetastar);
    float sintheta = sin(thetastar);
    float cosphi = cos(phistar);
    float sinphi = sin(phistar);
    // float etastar = -log ( tan(thetastar/2.) );
    // if(fabs(etastar)>5.)
    //  return std::pair<bool, Particle>(false, Particle());
    // float ptstar = -1;
    // while(ptstar<0.1 || ptstar>1) { // truncated gaussian to avoid numerical issues
    // ptstar = m_pstar(m_engine);
    // }

    float pstar = m_pstar(m_engine);

    // lvpod.Phi  = phi;
    // lvpod.Eta  = eta;
    // lvpod.Mass = mass;
    // lvpod.Pt   = pt;
    lvpod.Mass = mass;
    lvpod.Px = pstar * sintheta * cosphi;
    lvpod.Py = pstar * sintheta * sinphi;
    lvpod.Pz = pstar * costheta;
  }
  else{
    float pmag = lv->Vect().Mag();
    float energy = sqrt(pmag*pmag + mass*mass);
    TLorentzVector p4( lv->Px(), lv->Py(), lv->Pz(), energy);
    lvpod = utils::lvToPOD(p4);
  }
  int id = itype;

  Particle ptc = m_particles.create();
  // BareParticle core = ptc.Core();
  ptc.Core().Type = id;
  ptc.Core().P4 = lvpod;
  // ptc.setCore(core);

  if(m_ievt<m_nprint) {
    TLorentzVector lv = utils::lvFromPOD(ptc.Core().P4);
    std::cout<<"\tparticle "<<ptc.Core().Type<<" "<<lv.Eta()<<" "<<lv.Phi()<<" "<<lv.Pt()<<" "<<lv.E()<<std::endl;
  }

  return std::pair<bool, Particle>(true, ptc);
}
