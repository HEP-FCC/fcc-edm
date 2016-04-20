#ifndef ConstJetTagAssociation_H
#define ConstJetTagAssociation_H
#include "JetTagAssociationData.h"
#include <vector>
#include "podio/ObjectID.h"

// Association between a Jet and Tag information using a preferred algorithm
// author: C. Bernet, Z. Drasal

//forward declarations
namespace fcc {
class Jet;
class ConstJet;
class Tag;
class ConstTag;
}


#include "JetTagAssociationObj.h"

namespace fcc {

class JetTagAssociationObj;
class JetTagAssociation;
class JetTagAssociationCollection;
class JetTagAssociationCollectionIterator;

class ConstJetTagAssociation {

  friend JetTagAssociation;
  friend JetTagAssociationCollection;
  friend JetTagAssociationCollectionIterator;

public:

  /// default constructor
  ConstJetTagAssociation();
  
  /// constructor from existing JetTagAssociationObj
  ConstJetTagAssociation(JetTagAssociationObj* obj);
  /// copy constructor
  ConstJetTagAssociation(const ConstJetTagAssociation& other);
  /// copy-assignment operator
  ConstJetTagAssociation& operator=(const ConstJetTagAssociation& other);
  /// support cloning (deep-copy)
  ConstJetTagAssociation clone() const;
  /// destructor
  ~ConstJetTagAssociation();


public:

  const fcc::ConstJet Jet() const;
  const fcc::ConstTag Tag() const;



  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from JetTagAssociationObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const ConstJetTagAssociation& other) const {
       return (m_obj==other.m_obj);
  }

  bool operator==(const JetTagAssociation& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const JetTagAssociation& p1,
//       const JetTagAssociation& p2 );

  const podio::ObjectID getObjectID() const;

private:
  JetTagAssociationObj* m_obj;

};
} // namespace fcc

#endif
