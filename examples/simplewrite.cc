// Data model
#include "datamodel/EventInfo.h"
#include "datamodel/EventInfoCollection.h"
#include "datamodel/Particle.h"
#include "datamodel/ParticleCollection.h"
#include "datamodel/LorentzVector.h"

// Utility functions
#include "utilities/VectorUtils.h"

// ROOT
#include "TLorentzVector.h"
#include "TBranch.h"
#include "TFile.h"
#include "TTree.h"

// STL
#include <iostream>
#include <vector>

// podio specific includes
#include "podio/EventStore.h"
#include "podio/ROOTWriter.h"

// testing tools
#include "utilities/DummyGenerator.h"



int main(){
  std::cout<<"start processing"<<std::endl;

  auto store = podio::EventStore();
  podio::ROOTWriter writer("simpleexample.root", &store);

  unsigned nevents=10000;

  auto& evinfocoll = store.create<fcc::EventInfoCollection>("evtinfo");
  auto& pcoll = store.create<fcc::ParticleCollection>("mcparticles");

  writer.registerForWrite("evtinfo");
  writer.registerForWrite("mcparticles");

  for(unsigned iev=0; iev<nevents; ++iev) {
    if(iev % 1000 == 0)
      std::cout<<"processing event "<<iev<<std::endl;
    // fill event information
    auto evinfo = fcc::EventInfo(); // evinfocoll.create();
    evinfo.number(iev);
    evinfocoll.push_back(evinfo);

    auto ptc = fcc::Particle();
    ptc.pdgId(25);
    auto& p4 = ptc.p4();
    p4.px = static_cast<float>(iev);
    p4.py = 0.;
    p4.pz = 0.;
    p4.mass = 126.;
    pcoll.push_back(ptc);

    writer.writeEvent();
    store.clearCollections();
  }

  writer.finish();

  return 0;
}
