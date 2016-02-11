#ifndef JetTagAssociation_H
#define JetTagAssociation_H
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


#include "JetTagAssociationConst.h"
#include "JetTagAssociationObj.h"

namespace fcc {

class JetTagAssociationCollection;
class JetTagAssociationCollectionIterator;
class ConstJetTagAssociation;

class JetTagAssociation {

  friend JetTagAssociationCollection;
  friend JetTagAssociationCollectionIterator;
  friend ConstJetTagAssociation;

public:

  /// default constructor
  JetTagAssociation();
  
  /// constructor from existing JetTagAssociationObj
  JetTagAssociation(JetTagAssociationObj* obj);
  /// copy constructor
  JetTagAssociation(const JetTagAssociation& other);
  /// copy-assignment operator
  JetTagAssociation& operator=(const JetTagAssociation& other);
  /// support cloning (deep-copy)
  JetTagAssociation clone() const;
  /// destructor
  ~JetTagAssociation();

  /// conversion to const object
  operator ConstJetTagAssociation () const;

public:

  const fcc::ConstJet Jet() const;
  const fcc::ConstTag Tag() const;

  void Jet(fcc::ConstJet value);
  void Tag(fcc::ConstTag value);


  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from JetTagAssociationObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const JetTagAssociation& other) const {
       return (m_obj==other.m_obj);
  }

  bool operator==(const ConstJetTagAssociation& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const JetTagAssociation& p1,
//       const JetTagAssociation& p2 );

  const podio::ObjectID getObjectID() const;

private:
  JetTagAssociationObj* m_obj;

};

} // namespace fcc

#endif
