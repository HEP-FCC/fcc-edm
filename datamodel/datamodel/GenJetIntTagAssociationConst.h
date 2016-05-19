#ifndef ConstGenJetIntTagAssociation_H
#define ConstGenJetIntTagAssociation_H
#include "GenJetIntTagAssociationData.h"
#include <vector>
#include "podio/ObjectID.h"

// Association between a GenJet and IntTag information using a preferred algorithm
// author: C. Bernet, Z. Drasal

//forward declarations
namespace fcc {
class GenJet;
class ConstGenJet;
class IntTag;
class ConstIntTag;
}


#include "GenJetIntTagAssociationObj.h"

namespace fcc {

class GenJetIntTagAssociationObj;
class GenJetIntTagAssociation;
class GenJetIntTagAssociationCollection;
class GenJetIntTagAssociationCollectionIterator;

class ConstGenJetIntTagAssociation {

  friend GenJetIntTagAssociation;
  friend GenJetIntTagAssociationCollection;
  friend GenJetIntTagAssociationCollectionIterator;

public:

  /// default constructor
  ConstGenJetIntTagAssociation();
  
  /// constructor from existing GenJetIntTagAssociationObj
  ConstGenJetIntTagAssociation(GenJetIntTagAssociationObj* obj);
  /// copy constructor
  ConstGenJetIntTagAssociation(const ConstGenJetIntTagAssociation& other);
  /// copy-assignment operator
  ConstGenJetIntTagAssociation& operator=(const ConstGenJetIntTagAssociation& other);
  /// support cloning (deep-copy)
  ConstGenJetIntTagAssociation clone() const;
  /// destructor
  ~ConstGenJetIntTagAssociation();


public:

  const fcc::ConstGenJet Jet() const;
  const fcc::ConstIntTag Tag() const;



  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from GenJetIntTagAssociationObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const ConstGenJetIntTagAssociation& other) const {
       return (m_obj==other.m_obj);
  }

  bool operator==(const GenJetIntTagAssociation& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const GenJetIntTagAssociation& p1,
//       const GenJetIntTagAssociation& p2 );
  bool operator<(const ConstGenJetIntTagAssociation& other) const { return m_obj < other.m_obj  ; }

  const podio::ObjectID getObjectID() const;

private:
  GenJetIntTagAssociationObj* m_obj;

};
} // namespace fcc

#endif
