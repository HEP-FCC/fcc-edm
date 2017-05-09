#include "utilities/DummyGenerator.h"

#include "podio/EventStore.h"
#include "podio/ROOTWriter.h"

#include <iostream>
#include <cmath>
#include <cassert>

#include "TLorentzVector.h"
#include "TVector3.h"

#include "datamodel/ParticleCollection.h"
#include "datamodel/JetCollection.h"

#include "VectorUtils.h"

DummyGenerator::DummyGenerator(int npart,
                               podio::EventStore& store,
                               podio::ROOTWriter& writer) :
  m_njets(2), // not used
  m_engine(0xdeadbeef),
  m_pstar(0., 0.3),
  m_phi(-M_PI, M_PI),
  m_theta(0, M_PI),
  m_npart(npart),
  m_uniform(0.,1.),
  m_ptypeprob{0., 0.65, 0.85, 1.},
  m_nprint(-1),
  m_ievt(0),
  m_particles(store.create<fcc::ParticleCollection>("GenParticle")),
  m_jets(store.create<fcc::JetCollection>("GenJet"))
  {
  writer.registerForWrite("GenParticle");
  writer.registerForWrite("GenJet");
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

  auto jet = fcc::Jet(); // m_jets.create();
  TLorentzVector p4star;

  // keeping track of all created particles to boost them later on
  std::vector<fcc::Particle> particles;

  for(unsigned i=0; i<npart-1; ++i) {
    bool success = false;
    while(not success) {
      auto result = generate_particle();
      if(not result.first)
        continue;
      else {
        jet.addparticles(result.second);
        fcc::Particle& ptc = result.second;
        p4star += utils::lvFromPOD( result.second.p4() );
        particles.push_back(ptc);
        success = true;
      }
    }
  }

  // last particle is created to allow vector momentum conservation in jet com frame
  TLorentzVector opposite(-p4star.Vect(), p4star.E());
  auto result = generate_particle(&opposite);
  fcc::Particle& ptc = result.second;
  TLorentzVector final = utils::lvFromPOD( ptc.core().p4 );
  p4star += final;
  jet.addparticles(ptc);
  particles.push_back(ptc);

  // now boosting all particles to lab frame
  TLorentzVector jetlv;
  float gamma = energy/p4star.M();
  float beta = sqrt(1 - 1/(gamma*gamma));
  TVector3 boost(direction.Unit());
  boost *= static_cast<double>(beta);
  for(fcc::Particle& ptc : particles) {
    TLorentzVector lv = utils::lvFromPOD( ptc.core().p4 );
    lv.Boost( boost );
    ptc.core().p4 = utils::lvToPOD(lv);
    jetlv += lv;
  }
  jet.core().p4 = utils::lvToPOD(jetlv);

  m_jets.push_back(jet);
}

std::pair<bool, fcc::Particle> DummyGenerator::generate_particle(const TLorentzVector* lv, int itype) {

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

  fcc::LorentzVector lvpod;
  if( lv == nullptr ) {
    float phistar = m_phi(m_engine);
    float thetastar = m_theta(m_engine);
    float costheta = cos(thetastar);
    float sintheta = sin(thetastar);
    float cosphi = cos(phistar);
    float sinphi = sin(phistar);
    float pstar = m_pstar(m_engine);

    lvpod.mass = mass;
    lvpod.px = pstar * sintheta * cosphi;
    lvpod.py = pstar * sintheta * sinphi;
    lvpod.pz = pstar * costheta;
  }
  else{
    float pmag = lv->Vect().Mag();
    float energy = sqrt(pmag*pmag + mass*mass);
    TLorentzVector p4( lv->Px(), lv->Py(), lv->Pz(), energy);
    lvpod = utils::lvToPOD(p4);
  }
  int id = itype;

  auto ptc = m_particles.create();
  ptc.core().pdgId = id;
  ptc.core().p4 = lvpod;

  if(m_ievt<m_nprint) {
    TLorentzVector lv = utils::lvFromPOD(ptc.core().p4);
    std::cout<<"\tparticle "<<ptc.core().pdgId<<" "<<lv.Eta()<<" "<<lv.Phi()<<" "<<lv.Pt()<<" "<<lv.E()<<std::endl;
  }

  return std::pair<bool, fcc::Particle>(true, ptc);
}
