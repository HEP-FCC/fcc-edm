#ifndef  FCC_GRAPHBUILDER_H
#define  FCC_GRAPHBUILDER_H

#include "utilities/DirectedAcyclicGraph.h"
#include "datamodel/MCParticleCollection.h"
#include "podio/ObjectID.h"

#include <unordered_map>

/** @class fcc::ParticleGraph ParticleGraph.h ParticleGraph.h
 *
 *  @author J. Lingemann, A. Robson
 */
namespace fcc {
typedef DAG::Node<podio::ObjectID> IdNode;

class ParticleGraph {
public:
  // map vertex index -> associated particle vertices
  typedef std::unordered_map<unsigned, std::vector<unsigned>> VertexMap;
  /// Default constructor
  ParticleGraph() {};

  /// Destructor
  virtual ~ParticleGraph();

  /// Create nodes (you need to clear at the end of processing or delete the graph) corresponding to particles in coll.
  void build(const fcc::MCParticleCollection& particles);
  /// Get the node corresponding to a particle.
  const IdNode& getNode(const fcc::ConstMCParticle& particle) const;
  /// Clear the nodes. Should be called at end of processing.
  void clear();

private:
  /// Check if particle is in graph and return node, otherwise add it and return node
  IdNode& add(const fcc::ConstMCParticle& particle);
  /// The nodes of the graph
  std::vector<IdNode*> m_nodes;
};

} // namespace

#endif /* define  FCC_GRAPHBUILDER_H */
