#ifndef TaggedJetOBJ_H
#define TaggedJetOBJ_H

// std includes
#include <atomic>
#include <iostream>

// data model specific includes
#include "podio/ObjBase.h"
#include "TaggedJetData.h"



// forward declarations
class TaggedJet;
class ConstTaggedJet;
namespace fcc {class ConstJet;
}


namespace fcc {
class TaggedJetObj : public podio::ObjBase {
public:
  /// constructor
  TaggedJetObj();
  /// copy constructor (does a deep-copy of relation containers)
  TaggedJetObj(const TaggedJetObj&);
  /// constructor from ObjectID and TaggedJetData
  /// does not initialize the internal relation containers
  TaggedJetObj(const podio::ObjectID id, TaggedJetData data);
  virtual ~TaggedJetObj();

public:
  TaggedJetData data;
  ::fcc::ConstJet* m_jet;


};
} // namespace fcc


#endif
