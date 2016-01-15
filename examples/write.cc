// Data model
#include "datamodel/EventInfo.h"
#include "datamodel/EventInfoCollection.h"
#include "datamodel/Particle.h"
#include "datamodel/ParticleCollection.h"
#include "datamodel/JetCollection.h"
#include "datamodel/JetParticleAssociationCollection.h"
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


void processEvent(unsigned iEvent, podio::EventStore& store, podio::ROOTWriter& writer, DummyGenerator& generator) {
  if(iEvent % 1000 == 0)
    std::cout<<"processing event "<<iEvent<<std::endl;

  generator.generate();

  // and now for the writing
  // TODO: do that at a different time w/o coll pointer
  // COLIN: calling writeEvent should not be left up to the user.
  writer.writeEvent();
  store.clearCollections();
  return;
}


int main(){
  std::cout<<"start processing"<<std::endl;

  podio::EventStore store;
  podio::ROOTWriter writer("example.root", &store);

  DummyGenerator generator(10, store);
  generator.setNPrint(10);

  unsigned nevents=10000;

  auto& evinfocoll = store.create<EventInfoCollection>("EventInfo");
  writer.registerForWrite<EventInfoCollection>("EventInfo");

  // collections from the dummy generator
  writer.registerForWrite<ParticleCollection>("GenParticle");
  writer.registerForWrite<JetCollection>("GenJet");
  writer.registerForWrite<JetParticleAssociationCollection>("GenJetParticle");

  for(unsigned i=0; i<nevents; ++i) {
  // fill event information
    auto evinfo = EventInfo();
    evinfo.Number(i);
    evinfocoll.push_back(evinfo);
    processEvent(i, store, writer, generator);
  }

  writer.finish();
}
