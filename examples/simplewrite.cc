// Data model
#include "datamodel/EventInfo.h"
#include "datamodel/EventInfoCollection.h"
#include "datamodel/MCParticle.h"
#include "datamodel/MCParticleCollection.h"
#include "datamodel/LorentzVector.h"
#include "datamodel/GenJetCollection.h"
#include "datamodel/TaggedGenJetCollection.h"
#include "datamodel/TagCollection.h"

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
  auto& pcoll = store.create<fcc::MCParticleCollection>("mcparticles");
  auto& jcoll = store.create<fcc::GenJetCollection>("mcjets");
  auto& t1coll = store.create<fcc::TagCollection>("tag1");
  auto& t2coll = store.create<fcc::TagCollection>("tag2");
  auto& jtcoll = store.create<fcc::TaggedGenJetCollection>("taggedjets");

  writer.registerForWrite<fcc::EventInfoCollection>("evtinfo");
  writer.registerForWrite<fcc::MCParticleCollection>("mcparticles");
  writer.registerForWrite<fcc::GenJetCollection>("mcjets");
  writer.registerForWrite<fcc::TagCollection>("tag1");
  writer.registerForWrite<fcc::TagCollection>("tag2");
  writer.registerForWrite<fcc::TaggedGenJetCollection>("taggedjets");


  for(unsigned iev=0; iev<nevents; ++iev) {
    if(iev % 1000 == 0)
      std::cout<<"processing event "<<iev<<std::endl;
    // fill event information
    auto evinfo = fcc::EventInfo(); // evinfocoll.create();
    evinfo.number(iev);
    evinfocoll.push_back(evinfo);

    auto ptc = pcoll.create();
    ptc.pdgId(25);
    auto& p4 = ptc.p4();
    p4.px = static_cast<float>(iev);
    p4.py = 0.;
    p4.pz = 0.;
    p4.mass = 126.;

    auto jet = jcoll.create();
    jet.addparticles(ptc);

    auto tagJet = jtcoll.create();
    tagJet.jet(jet);

    auto tag1 = t1coll.create();
    tag1.value(iev);
    auto tag2 = t1coll.create();
    tag2.value(-iev);

    tagJet.addtags(tag1);
    tagJet.addtags(tag2);

    writer.writeEvent();
    store.clearCollections();
  }

  writer.finish();

  return 0;
}
