#include "utilities/ParticleGraph.h"

#include "datamodel/GenVertex.h"
#include <utility>

void fcc::ParticleGraph::build(const fcc::MCParticleCollection& particles) {
  std::vector<fcc::ConstMCParticle> daughters;
  std::vector<fcc::ConstMCParticle> mothers;
  for (const auto& mcpart : particles) {
    auto startID = mcpart.StartVertex().getObjectID();
    auto endID = mcpart.EndVertex().getObjectID();
    auto pID = mcpart.getObjectID();
    IdNode& particleNode = add(mcpart);
    for (const auto& mcpart2 : particles) {
      if (mcpart2.getObjectID() == pID) continue;
      if (endID.collectionID != -2 && mcpart2.StartVertex().getObjectID() == endID) {
        IdNode& daughter = add(mcpart2);
        particleNode.addChild(daughter);
      }
      if (startID.collectionID != -2 && mcpart2.EndVertex().getObjectID() == startID) {
        IdNode& mother = add(mcpart2);
        mother.addChild(mother);
      }
    }
  }
}

fcc::IdNode& fcc::ParticleGraph::add(const fcc::ConstMCParticle& particle) {
  auto id = particle.getObjectID();
  if (id.collectionID == -2) {
    throw std::invalid_argument("Trying to add Particle that is not part of a collection.");
  }
  auto result = std::find_if(begin(m_nodes), end(m_nodes),
                               [id](const IdNode* item)->bool { return id == item->value(); }
  );
  if (result == end(m_nodes)) {
    m_nodes.emplace_back(new IdNode(id));
    return *m_nodes.back();
  }
  return **result;
}

void fcc::ParticleGraph::clear() {
  for (auto node : m_nodes) {
    delete node;
  }
  m_nodes.clear();
}

fcc::ParticleGraph::~ParticleGraph() {
  clear();
}

const fcc::IdNode& fcc::ParticleGraph::getNode(const fcc::ConstMCParticle& particle) const {
  auto id = particle.getObjectID();
  auto result = std::find_if(begin(m_nodes), end(m_nodes),
                               [id](const IdNode* item)->bool { return id == item->value(); }
  );
  if (result == end(m_nodes)) {
    throw std::invalid_argument("Requested particle is not registered in the graph.");
  }
  return **result;
}
