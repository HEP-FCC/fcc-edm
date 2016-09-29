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
#include "podio/ROOTReader.h"

int main(){
  std::cout<<"start processing"<<std::endl;

  auto store = podio::EventStore();
  auto reader = podio::ROOTReader();

  reader.openFile("simpleexample.root");
  store.setReader(&reader);
  unsigned nevents= reader.getEntries();

  for(unsigned iev=0; iev<nevents; ++iev) {
    if(iev % 1000 == 0)
      std::cout << "processing event " << iev << std::endl;

    const fcc::EventInfoCollection* evinfocoll(nullptr);
    bool evinfoPresent = store.get("evtinfo", evinfocoll);
    if (evinfoPresent) {
      auto evinfo = (*evinfocoll)[0];
      if (iev < 10) {
        std::cout << "read " << evinfo.number() << std::endl;
      }
    }


    const fcc::ParticleCollection* particles;
    bool particlesPresent = store.get("mcparticles", particles);

    if (particlesPresent) {
      auto ptc = (*particles)[0];
      if (iev < 10) {
        std::cout << ptc.pdgId() << std::endl;
        std::cout << ptc.p4().px << std::endl;
      }
    }

    store.clear();
    reader.endOfEvent();
  }
  return 0;
}
