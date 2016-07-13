#include "utilities/GraphBuilder.h"

#include "datamodel/GenVertex.h"
#include <utility>

void fcc::GraphBuilder::build(const fcc::MCParticleCollection& particles) {
  std::vector<fcc::ConstMCParticle> daughters;
  std::vector<fcc::ConstMCParticle> mothers;
  for (const auto& mcpart : particles) {
    auto startID = mcpart.StartVertex().getObjectID();
    auto endID = mcpart.EndVertex().getObjectID();
    auto pID = mcpart.getObjectID();
    IdNode& particleNode = add(mcpart);
    for (const auto& mcpart2 : particles) {
      if (mcpart2.getObjectID() == pID) continue;
      if (mcpart2.StartVertex().getObjectID() == endID) {
        IdNode& daughter = add(mcpart2);
        particleNode.addChild(daughter);
      }
      if (mcpart2.EndVertex().getObjectID() == startID) {
        IdNode& mother = add(mcpart2);
        mother.addChild(mother);
      }
    }
  }
}

fcc::IdNode& fcc::GraphBuilder::add(const fcc::ConstMCParticle& particle) {
  auto id = particle.getObjectID();
  auto result = std::find_if(begin(m_nodes), end(m_nodes),
                               [id](const IdNodePair& item)->bool { return id == item.first; }
  );
  if (result == end(m_nodes)) {
    m_nodes.push_back(std::make_pair<podio::ObjectID, IdNode>(std::move(id), IdNode(id)));
    return m_nodes.back().second;
  }
  return result->second;
}

void fcc::GraphBuilder::clear() {
  m_nodes.clear();
}

const fcc::IdNode& fcc::GraphBuilder::getNode(const fcc::ConstMCParticle& particle) const {
  auto id = particle.getObjectID();
  auto result = std::find_if(begin(m_nodes), end(m_nodes),
                               [id](const IdNodePair& item)->bool { return id == item.first; }
  );
  return result->second;
}
