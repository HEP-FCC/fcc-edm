#include "utilities/ParticleGraph.h"

#include "datamodel/GenVertex.h"
#include <utility>

void fcc::ParticleGraph::build(const fcc::MCParticleCollection& particles) {
  // collect all particles associated with given start and end vertex
  fcc::ParticleGraph::VertexMap startVertexMap;
  fcc::ParticleGraph::VertexMap endVertexMap;

  for (const auto& mcpart : particles) {
    auto& startID = mcpart.StartVertex().getObjectID();
    auto& endID = mcpart.EndVertex().getObjectID();
    auto siblingsIt = startVertexMap.find(startID.index);
    auto parentsIt = endVertexMap.find(endID.index);

    unsigned particleIdx = mcpart.getObjectID().index;
    if (startID.collectionID != -2) {
      if (siblingsIt == end(startVertexMap)) {
        startVertexMap[startID.index] = std::vector<unsigned>{particleIdx};
      } else {
        siblingsIt->second.push_back(particleIdx);
      }
    }
    if (endID.collectionID != -2) {
      if (parentsIt == end(endVertexMap)) {
        endVertexMap[endID.index] = std::vector<unsigned>{particleIdx};
      } else {
        parentsIt->second.push_back(particleIdx);
      }
    }
  }

  // Now establish connections with above maps:
  // 0 --- p1 --- 1 --- p2 --- 2
  //              + --- p3 --- 3
  // p1 has startVertex "0", looking in the endVertex map for "0" won't find anything
  // p1 has endVertex "1", looking in startVertex map for "1" will find p2 and p3 which are its children
  // p2 has startVertex "1", looking for "1" in endVertex map finds p1, which is its parent
  for (const auto& mcpart : particles) {
    auto& startID = mcpart.StartVertex().getObjectID();
    auto& endID = mcpart.EndVertex().getObjectID();
    // to find children, look for the endVertex ID in the startVertex map (see above)
    auto childrenIt = startVertexMap.find(endID.index);
    // to find parents, look for the startVertex ID in the endVertex map (see above)
    auto parentsIt = endVertexMap.find(startID.index);
    // actually establish the connections and add to the nodes
    IdNode& particleNode = add(mcpart);
    if (childrenIt != end(startVertexMap)) {
      for (auto childIdx : childrenIt->second) {
        const auto& child = particles.at(childIdx);
        IdNode& childNode = add(child);
        particleNode.addChild(childNode);
      }
    }
    if (parentsIt != end(endVertexMap)) {
      for (auto parentIdx : parentsIt->second) {
        const auto& parent = particles.at(parentIdx);
        IdNode& parentNode = add(parent);
        parentNode.addChild(particleNode);
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
