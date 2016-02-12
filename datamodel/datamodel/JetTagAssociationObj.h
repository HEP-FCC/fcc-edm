#ifndef JetTagAssociationOBJ_H
#define JetTagAssociationOBJ_H

// std includes
#include <atomic>
#include <iostream>

// data model specific includes
#include "podio/ObjBase.h"
#include "JetTagAssociationData.h"



// forward declarations
class JetTagAssociation;
class ConstJetTagAssociation;
namespace fcc {class ConstJet;
class ConstTag;
}


namespace fcc {
class JetTagAssociationObj : public podio::ObjBase {
public:
  /// constructor
  JetTagAssociationObj();
  /// copy constructor (does a deep-copy of relation containers)
  JetTagAssociationObj(const JetTagAssociationObj&);
  /// constructor from ObjectID and JetTagAssociationData
  /// does not initialize the internal relation containers
  JetTagAssociationObj(const podio::ObjectID id, JetTagAssociationData data);
  virtual ~JetTagAssociationObj();

public:
  JetTagAssociationData data;
  ::fcc::ConstJet* m_Jet;
  ::fcc::ConstTag* m_Tag;


};
} // namespace fcc


#endif
