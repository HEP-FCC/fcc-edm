// Data model
#include "datamodel/MCParticleCollection.h"
#include "datamodel/LorentzVector.h"
#include "datamodel/GenVertexCollection.h"

// utilities
#include "utilities/ParticleGraph.h"

// STL
#include <iostream>
#include <vector>

// DAG
#include "dag/DirectedAcyclicGraph.h"


// podio specific includes
#include "podio/EventStore.h"
#include "podio/ROOTReader.h"

// creates graph from particle history
int main(){
  std::cout<<"start processing"<<std::endl;

  auto store = podio::EventStore();
  auto reader = podio::ROOTReader();

  reader.openFile("graphexample.root");
  store.setReader(&reader);
  unsigned nevents = reader.getEntries();

  const fcc::MCParticleCollection* particles;
  fcc::ParticleGraph graph = fcc::ParticleGraph();
  bool particlesPresent = store.get("mcparticles", particles);
  if (particlesPresent) {
    graph.build(*particles);
    DAG::BFSVisitor<fcc::IdNode> visitor;
    const auto& root = (*particles)[0];
    auto rootNode = graph.getNode(root);
    int cntrChildren = 0;
    for (auto n : visitor.traverseChildren(rootNode, 1)) {
      if (n->value() == rootNode.value()) {
        continue;
      }
      cntrChildren++;
      if (n->children().size() != 3) {
        throw std::runtime_error("wrong number of grand children");
      }
    }
    if(rootNode.children().size() != 3) {
      throw std::runtime_error("wrong number of children");
    }
  }

  store.clear();
  reader.endOfEvent();
  return 0;
}
