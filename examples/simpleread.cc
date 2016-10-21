// Data model
#include "datamodel/EventInfo.h"
#include "datamodel/EventInfoCollection.h"
#include "datamodel/MCParticle.h"
#include "datamodel/MCParticleCollection.h"
#include "datamodel/TaggedGenJetCollection.h"
#include "datamodel/TagCollection.h"
#include "datamodel/LorentzVector.h"

// Utility functions
#include "utilities/VectorUtils.h"
#include "utilities/JetUtils.h"

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
  jetutils::JetUtils jetUtils(*(reader.getCollectionIDTable()));

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


    const fcc::MCParticleCollection* particles;
    bool particlesPresent = store.get("mcparticles", particles);

    if (particlesPresent) {
      auto ptc = (*particles)[0];
      if (iev < 10) {
        std::cout << ptc.pdgId() << std::endl;
        std::cout << ptc.p4().px << std::endl;
      }
    }

    const fcc::TaggedGenJetCollection* jets;
    bool jetsPresent = store.get("taggedjet", jets);
    if (jetsPresent) {
      auto jet = (*jets)[0];
      auto tag1 = jetUtils.tag(jet, "tag1");
      auto tag2 = jetUtils.tag(jet, "tag2");
      std::cout << "tag1 = " << tag1.value() << "; tag2 = " << tag2.value();
    }

    store.clear();
    reader.endOfEvent();
  }
  return 0;
}
