// Data model
#include "datamodel/MCParticleCollection.h"
#include "datamodel/LorentzVector.h"
#include "datamodel/GenVertexCollection.h"

// STL
#include <iostream>
#include <vector>

// podio specific includes
#include "podio/EventStore.h"
#include "podio/ROOTWriter.h"


// prepares a file with particles that have a history (only one event and physically nonsensical)
int main() {
  auto store = podio::EventStore();
  podio::ROOTWriter writer("graphexample.root", &store);
  auto& particleColl = store.create<fcc::MCParticleCollection>("mcparticles");
  auto& vtxColl = store.create<fcc::GenVertexCollection>("mcvertices");

  writer.registerForWrite("mcparticles");
  writer.registerForWrite("mcvertices");

  auto ptc = particleColl.create();
  auto vtxStartParent = vtxColl.create();
  auto vtxStartChild = vtxColl.create();

  ptc.startVertex(vtxStartParent);
  ptc.endVertex(vtxStartChild);
  for (int ichild = 0; ichild < 3; ++ichild) {
    auto childPtc = particleColl.create();
    auto vtxStartGrandChild = vtxColl.create();
    childPtc.startVertex(vtxStartChild);
    childPtc.endVertex(vtxStartGrandChild);
    for (int igrandchild = 0; igrandchild < 3; ++igrandchild) {
      auto vtxEndGrandChild = vtxColl.create();
      auto grandChildPtc = particleColl.create();
      grandChildPtc.startVertex(vtxStartGrandChild);
      grandChildPtc.endVertex(vtxEndGrandChild);
    }
  }
  writer.writeEvent();
  store.clearCollections();
  writer.finish();

  return 0;
}
