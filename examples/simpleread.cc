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
#include "utilities/TagUtils.h"

// ROOT
#include "TLorentzVector.h"
#include "TBranch.h"
#include "TFile.h"
#include "TTree.h"

// STL
#include <iostream>
#include <vector>
#include <cassert>

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
  tagutils::TagUtils tagUtils(*(reader.getCollectionIDTable()));
  int tag2Id = reader.getCollectionIDTable()->collectionID("tag2");

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
    bool jetsPresent = store.get("taggedjets", jets);
    if (jetsPresent) {
      auto jet = (*jets)[0];
      // looks up the ID every time you request it (O(logN) of collections in IDTable)
      auto tag1 = tagUtils.tag(jet, "tag1");
      // instead use the locally cached ID
      auto tag2 = tagutils::tag(jet, tag2Id);
      if (nullptr != tag1 && nullptr != tag2 && iev < 10) {
        std::cout << "tag1 = " << tag1->value() << "; tag2 = " << tag2->value() << std::endl;
      }
      auto tagNotPresent = tagUtils.tag(jet, "tag123");
      assert(tagNotPresent == nullptr);
    }

    store.clear();
    reader.endOfEvent();
  }
  return 0;
}
