#ifndef  FCC_GRAPHBUILDER_H
#define  FCC_GRAPHBUILDER_H

#include "utilities/directedacyclicgraph.h"
#include "datamodel/MCParticleCollection.h"
#include "podio/ObjectID.h"

#include <map>

/** @class fcc::ParticleGraph ParticleGraph.h ParticleGraph.h
 *
 *  @author J. Lingemann, A. Robson
 */
namespace fcc {
typedef DAG::Node<podio::ObjectID> IdNode;

class ParticleGraph {
public:
  /// Default constructor
  ParticleGraph() = default;

  /// Destructor
  virtual ~ParticleGraph();

  void build(const fcc::MCParticleCollection& particles);
  const IdNode& getNode(const fcc::ConstMCParticle& particle) const;
  void clear();

private:
  IdNode& add(const fcc::ConstMCParticle& particle);
  std::vector<IdNode*> m_nodes;
};

} // namespace

#endif /* define  FCC_GRAPHBUILDER_H */
