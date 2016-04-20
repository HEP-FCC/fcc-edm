#ifndef GenJetTagAssociation_H
#define GenJetTagAssociation_H
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


#include "GenJetTagAssociationConst.h"
#include "GenJetTagAssociationObj.h"

namespace fcc {

class GenJetTagAssociationCollection;
class GenJetTagAssociationCollectionIterator;
class ConstGenJetTagAssociation;

class GenJetTagAssociation {

  friend GenJetTagAssociationCollection;
  friend GenJetTagAssociationCollectionIterator;
  friend ConstGenJetTagAssociation;

public:

  /// default constructor
  GenJetTagAssociation();

  /// constructor from existing GenJetTagAssociationObj
  GenJetTagAssociation(GenJetTagAssociationObj* obj);
  /// copy constructor
  GenJetTagAssociation(const GenJetTagAssociation& other);
  /// copy-assignment operator
  GenJetTagAssociation& operator=(const GenJetTagAssociation& other);
  /// support cloning (deep-copy)
  GenJetTagAssociation clone() const;
  /// destructor
  ~GenJetTagAssociation();

  /// conversion to const object
  operator ConstGenJetTagAssociation () const;

public:

  const fcc::ConstGenJet Jet() const;
  const fcc::ConstTag Tag() const;

  void Jet(fcc::ConstGenJet value);
  void Tag(fcc::ConstTag value);



  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from GenJetTagAssociationObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const GenJetTagAssociation& other) const {
    return (m_obj==other.m_obj);
  }

  bool operator==(const ConstGenJetTagAssociation& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const GenJetTagAssociation& p1,
//       const GenJetTagAssociation& p2 );

  const podio::ObjectID getObjectID() const;

private:
  GenJetTagAssociationObj* m_obj;

};

} // namespace fcc

#endif
