#ifndef JetIntTagAssociation_H
#define JetIntTagAssociation_H
#include "JetIntTagAssociationData.h"

#include <vector>
#include "podio/ObjectID.h"

// Association between a Jet and IntTag information using a preferred algorithm
// author: C. Bernet, Z. Drasal

//forward declarations
namespace fcc {
class Jet;
class ConstJet;
class IntTag;
class ConstIntTag;
}


#include "JetIntTagAssociationConst.h"
#include "JetIntTagAssociationObj.h"

namespace fcc {

class JetIntTagAssociationCollection;
class JetIntTagAssociationCollectionIterator;
class ConstJetIntTagAssociation;

class JetIntTagAssociation {

  friend JetIntTagAssociationCollection;
  friend JetIntTagAssociationCollectionIterator;
  friend ConstJetIntTagAssociation;

public:

  /// default constructor
  JetIntTagAssociation();
  
  /// constructor from existing JetIntTagAssociationObj
  JetIntTagAssociation(JetIntTagAssociationObj* obj);
  /// copy constructor
  JetIntTagAssociation(const JetIntTagAssociation& other);
  /// copy-assignment operator
  JetIntTagAssociation& operator=(const JetIntTagAssociation& other);
  /// support cloning (deep-copy)
  JetIntTagAssociation clone() const;
  /// destructor
  ~JetIntTagAssociation();

  /// conversion to const object
  operator ConstJetIntTagAssociation () const;

public:

  const fcc::ConstJet Jet() const;
  const fcc::ConstIntTag Tag() const;

  void Jet(fcc::ConstJet value);
  void Tag(fcc::ConstIntTag value);


  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from JetIntTagAssociationObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const JetIntTagAssociation& other) const {
       return (m_obj==other.m_obj);
  }

  bool operator==(const ConstJetIntTagAssociation& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const JetIntTagAssociation& p1,
//       const JetIntTagAssociation& p2 );

  const podio::ObjectID getObjectID() const;

private:
  JetIntTagAssociationObj* m_obj;

};

} // namespace fcc

#endif
