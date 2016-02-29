#ifndef JetIntTagAssociationOBJ_H
#define JetIntTagAssociationOBJ_H

// std includes
#include <atomic>
#include <iostream>

// data model specific includes
#include "podio/ObjBase.h"
#include "JetIntTagAssociationData.h"



// forward declarations
class JetIntTagAssociation;
class ConstJetIntTagAssociation;
namespace fcc {class ConstJet;
class ConstIntTag;
}


namespace fcc {
class JetIntTagAssociationObj : public podio::ObjBase {
public:
  /// constructor
  JetIntTagAssociationObj();
  /// copy constructor (does a deep-copy of relation containers)
  JetIntTagAssociationObj(const JetIntTagAssociationObj&);
  /// constructor from ObjectID and JetIntTagAssociationData
  /// does not initialize the internal relation containers
  JetIntTagAssociationObj(const podio::ObjectID id, JetIntTagAssociationData data);
  virtual ~JetIntTagAssociationObj();

public:
  JetIntTagAssociationData data;
  ::fcc::ConstJet* m_Jet;
  ::fcc::ConstIntTag* m_Tag;


};
} // namespace fcc


#endif
