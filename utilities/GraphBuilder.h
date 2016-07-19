#ifndef  FCC_GRAPHBUILDER_H
#define  FCC_GRAPHBUILDER_H

#include "utilities/directedacyclicgraph.h"
#include "datamodel/MCParticleCollection.h"
#include "podio/ObjectID.h"

#include <map>

/** @class fcc::GraphBuilder GraphBuilder.h GraphBuilder.h
 *
 *  @author J. Lingemann, A. Robson
 */
namespace fcc {
typedef DAG::Node<podio::ObjectID> IdNode;

class GraphBuilder {
public:
  /// Default constructor
  GraphBuilder() = default;

  /// Destructor
  virtual ~GraphBuilder();

  void build(const fcc::MCParticleCollection& particles);
  const IdNode& getNode(const fcc::ConstMCParticle& particle) const;
  void clear();

private:
  IdNode& add(const fcc::ConstMCParticle& particle);
  std::vector<IdNode*> m_nodes;
};

} // namespace

#endif /* define  FCC_GRAPHBUILDER_H */
