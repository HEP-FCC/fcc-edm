#ifndef ConstJetIntTagAssociation_H
#define ConstJetIntTagAssociation_H
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


#include "JetIntTagAssociationObj.h"

namespace fcc {

class JetIntTagAssociationObj;
class JetIntTagAssociation;
class JetIntTagAssociationCollection;
class JetIntTagAssociationCollectionIterator;

class ConstJetIntTagAssociation {

  friend JetIntTagAssociation;
  friend JetIntTagAssociationCollection;
  friend JetIntTagAssociationCollectionIterator;

public:

  /// default constructor
  ConstJetIntTagAssociation();
  
  /// constructor from existing JetIntTagAssociationObj
  ConstJetIntTagAssociation(JetIntTagAssociationObj* obj);
  /// copy constructor
  ConstJetIntTagAssociation(const ConstJetIntTagAssociation& other);
  /// copy-assignment operator
  ConstJetIntTagAssociation& operator=(const ConstJetIntTagAssociation& other);
  /// support cloning (deep-copy)
  ConstJetIntTagAssociation clone() const;
  /// destructor
  ~ConstJetIntTagAssociation();


public:

  const fcc::ConstJet Jet() const;
  const fcc::ConstIntTag Tag() const;



  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from JetIntTagAssociationObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const ConstJetIntTagAssociation& other) const {
       return (m_obj==other.m_obj);
  }

  bool operator==(const JetIntTagAssociation& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const JetIntTagAssociation& p1,
//       const JetIntTagAssociation& p2 );
  bool operator<(const ConstJetIntTagAssociation& other) const { return m_obj < other.m_obj  ; }

  const podio::ObjectID getObjectID() const;

private:
  JetIntTagAssociationObj* m_obj;

};
} // namespace fcc

#endif
