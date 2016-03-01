#ifndef GenJetIntTagAssociationOBJ_H
#define GenJetIntTagAssociationOBJ_H

// std includes
#include <atomic>
#include <iostream>

// data model specific includes
#include "podio/ObjBase.h"
#include "GenJetIntTagAssociationData.h"



// forward declarations
class GenJetIntTagAssociation;
class ConstGenJetIntTagAssociation;
namespace fcc {class ConstGenJet;
class ConstIntTag;
}


namespace fcc {
class GenJetIntTagAssociationObj : public podio::ObjBase {
public:
  /// constructor
  GenJetIntTagAssociationObj();
  /// copy constructor (does a deep-copy of relation containers)
  GenJetIntTagAssociationObj(const GenJetIntTagAssociationObj&);
  /// constructor from ObjectID and GenJetIntTagAssociationData
  /// does not initialize the internal relation containers
  GenJetIntTagAssociationObj(const podio::ObjectID id, GenJetIntTagAssociationData data);
  virtual ~GenJetIntTagAssociationObj();

public:
  GenJetIntTagAssociationData data;
  ::fcc::ConstGenJet* m_Jet;
  ::fcc::ConstIntTag* m_Tag;


};
} // namespace fcc


#endif
