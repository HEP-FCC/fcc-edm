#include "dag/DirectedAcyclicGraph.h"

/** @file graph.cc
  *
  * This is a very simple example for using the nodes and visitors defined by DirectedAcyclicGraph.
  * The idpair is very similar to the PODIO ObjectID, so this may be instructive. For a more complete
  * example on how to use it in the context of the fcc-edm, have a look at tests/graph*test.cc or FCCSW
  *
  * @author: A. Robson, J. Lingemann
  */


class idpair {
public:
  int itype;
  int ivalue;
  idpair(int t,int v) {itype=t; ivalue=v;};
};


int main() {
  typedef DAG::Node<idpair> INode;
  std::vector<INode> nodes;

  // create a set of nodes
  nodes.push_back(idpair(1,2));
  nodes.push_back(idpair(1,3));
  nodes.push_back(idpair(2,3));
  nodes.push_back(idpair(2,2));

  // and now define the graph
  nodes[0].addChild(nodes[1]);  // link between n0 and n1
  nodes[0].addChild(nodes[2]);  // link between n0 and n2 etc
  nodes[1].addChild(nodes[3]);


  // Start at node 0
  std::cout << std::endl << "TRAVERSE CHILDREN (start Node 0) " << std::endl;
  DAG::BFSVisitor<INode> bfs;
  for (auto n : bfs.traverseChildren(nodes[0])) {
    std::cout << n->value().itype << ":" <<n->value().ivalue<<std::endl;
  }
  return 0;
}
