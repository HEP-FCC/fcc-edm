#ifndef TaggedGenJetOBJ_H
#define TaggedGenJetOBJ_H

// std includes
#include <atomic>
#include <iostream>

// data model specific includes
#include "podio/ObjBase.h"
#include "TaggedGenJetData.h"



// forward declarations
class TaggedGenJet;
class ConstTaggedGenJet;
namespace fcc {class ConstGenJet;
}


namespace fcc {
class TaggedGenJetObj : public podio::ObjBase {
public:
  /// constructor
  TaggedGenJetObj();
  /// copy constructor (does a deep-copy of relation containers)
  TaggedGenJetObj(const TaggedGenJetObj&);
  /// constructor from ObjectID and TaggedGenJetData
  /// does not initialize the internal relation containers
  TaggedGenJetObj(const podio::ObjectID id, TaggedGenJetData data);
  virtual ~TaggedGenJetObj();

public:
  TaggedGenJetData data;
  ::fcc::ConstGenJet* m_jet;


};
} // namespace fcc


#endif
