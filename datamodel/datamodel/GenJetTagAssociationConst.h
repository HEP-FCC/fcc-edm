#ifndef ConstGenJetTagAssociation_H
#define ConstGenJetTagAssociation_H
#include "GenJetTagAssociationData.h"
#include <vector>
#include "podio/ObjectID.h"

// Association between a GenJet and Tag information using a preferred algorithm
// author: C. Bernet, Z. Drasal

//forward declarations
namespace fcc {
class GenJet;
class ConstGenJet;
class Tag;
class ConstTag;
}


#include "GenJetTagAssociationObj.h"

namespace fcc {

class GenJetTagAssociationObj;
class GenJetTagAssociation;
class GenJetTagAssociationCollection;
class GenJetTagAssociationCollectionIterator;

class ConstGenJetTagAssociation {

  friend GenJetTagAssociation;
  friend GenJetTagAssociationCollection;
  friend GenJetTagAssociationCollectionIterator;

public:

  /// default constructor
  ConstGenJetTagAssociation();
  
  /// constructor from existing GenJetTagAssociationObj
  ConstGenJetTagAssociation(GenJetTagAssociationObj* obj);
  /// copy constructor
  ConstGenJetTagAssociation(const ConstGenJetTagAssociation& other);
  /// copy-assignment operator
  ConstGenJetTagAssociation& operator=(const ConstGenJetTagAssociation& other);
  /// support cloning (deep-copy)
  ConstGenJetTagAssociation clone() const;
  /// destructor
  ~ConstGenJetTagAssociation();


public:

  const fcc::ConstGenJet Jet() const;
  const fcc::ConstTag Tag() const;



  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from GenJetTagAssociationObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const ConstGenJetTagAssociation& other) const {
       return (m_obj==other.m_obj);
  }

  bool operator==(const GenJetTagAssociation& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const GenJetTagAssociation& p1,
//       const GenJetTagAssociation& p2 );
  bool operator<(const ConstGenJetTagAssociation& other) const { return m_obj < other.m_obj  ; }

  const podio::ObjectID getObjectID() const;

private:
  GenJetTagAssociationObj* m_obj;

};
} // namespace fcc

#endif
