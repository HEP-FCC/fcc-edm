#ifndef GenJetIntTagAssociation_H
#define GenJetIntTagAssociation_H
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


#include "GenJetIntTagAssociationConst.h"
#include "GenJetIntTagAssociationObj.h"

namespace fcc {

class GenJetIntTagAssociationCollection;
class GenJetIntTagAssociationCollectionIterator;
class ConstGenJetIntTagAssociation;

class GenJetIntTagAssociation {

  friend GenJetIntTagAssociationCollection;
  friend GenJetIntTagAssociationCollectionIterator;
  friend ConstGenJetIntTagAssociation;

public:

  /// default constructor
  GenJetIntTagAssociation();
  
  /// constructor from existing GenJetIntTagAssociationObj
  GenJetIntTagAssociation(GenJetIntTagAssociationObj* obj);
  /// copy constructor
  GenJetIntTagAssociation(const GenJetIntTagAssociation& other);
  /// copy-assignment operator
  GenJetIntTagAssociation& operator=(const GenJetIntTagAssociation& other);
  /// support cloning (deep-copy)
  GenJetIntTagAssociation clone() const;
  /// destructor
  ~GenJetIntTagAssociation();

  /// conversion to const object
  operator ConstGenJetIntTagAssociation () const;

public:

  const fcc::ConstGenJet Jet() const;
  const fcc::ConstIntTag Tag() const;

  void Jet(fcc::ConstGenJet value);
  void Tag(fcc::ConstIntTag value);


  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from GenJetIntTagAssociationObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const GenJetIntTagAssociation& other) const {
       return (m_obj==other.m_obj);
  }

  bool operator==(const ConstGenJetIntTagAssociation& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const GenJetIntTagAssociation& p1,
//       const GenJetIntTagAssociation& p2 );

  const podio::ObjectID getObjectID() const;

private:
  GenJetIntTagAssociationObj* m_obj;

};

} // namespace fcc

#endif
