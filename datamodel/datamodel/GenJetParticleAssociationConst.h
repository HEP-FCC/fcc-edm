#ifndef ConstGenJetParticleAssociation_H
#define ConstGenJetParticleAssociation_H
#include "GenJetParticleAssociationData.h"

#include <vector>
#include "podio/ObjectID.h"

// Association between a GenJet and a MCParticle. Used to keep track of jet constituents
// author: C. Bernet, B. Hegner

//forward declarations
class GenJet;
class ConstGenJet;
class MCParticle;
class ConstMCParticle;


#include "GenJetParticleAssociationObj.h"



class GenJetParticleAssociationObj;
class GenJetParticleAssociation;
class GenJetParticleAssociationCollection;
class GenJetParticleAssociationCollectionIterator;

class ConstGenJetParticleAssociation {

  friend GenJetParticleAssociation;
  friend GenJetParticleAssociationCollection;
  friend GenJetParticleAssociationCollectionIterator;

public:

  /// default constructor
  ConstGenJetParticleAssociation();
  
  /// constructor from existing GenJetParticleAssociationObj
  ConstGenJetParticleAssociation(GenJetParticleAssociationObj* obj);
  /// copy constructor
  ConstGenJetParticleAssociation(const ConstGenJetParticleAssociation& other);
  /// copy-assignment operator
  ConstGenJetParticleAssociation& operator=(const ConstGenJetParticleAssociation& other);
  /// support cloning (deep-copy)
  ConstGenJetParticleAssociation clone() const;
  /// destructor
  ~ConstGenJetParticleAssociation();


public:

  const ConstGenJet Jet() const;
  const ConstMCParticle Particle() const;


  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from GenJetParticleAssociationObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const ConstGenJetParticleAssociation& other) const {
       return (m_obj==other.m_obj);
  }

  bool operator==(const GenJetParticleAssociation& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const GenJetParticleAssociation& p1,
//       const GenJetParticleAssociation& p2 );

  const podio::ObjectID getObjectID() const;

private:
  GenJetParticleAssociationObj* m_obj;

};


#endif
