#ifndef GenJetTagAssociationOBJ_H
#define GenJetTagAssociationOBJ_H

// std includes
#include <atomic>
#include <iostream>

// data model specific includes
#include "podio/ObjBase.h"
#include "GenJetTagAssociationData.h"



// forward declarations
class GenJetTagAssociation;
class ConstGenJetTagAssociation;
namespace fcc {class ConstGenJet;
class ConstTag;
}


namespace fcc {
class GenJetTagAssociationObj : public podio::ObjBase {
public:
  /// constructor
  GenJetTagAssociationObj();
  /// copy constructor (does a deep-copy of relation containers)
  GenJetTagAssociationObj(const GenJetTagAssociationObj&);
  /// constructor from ObjectID and GenJetTagAssociationData
  /// does not initialize the internal relation containers
  GenJetTagAssociationObj(const podio::ObjectID id, GenJetTagAssociationData data);
  virtual ~GenJetTagAssociationObj();

public:
  GenJetTagAssociationData data;
  ::fcc::ConstGenJet* m_Jet;
  ::fcc::ConstTag* m_Tag;


};
} // namespace fcc


#endif
