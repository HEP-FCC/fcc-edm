#ifndef GenJetParticleAssociation_H
#define GenJetParticleAssociation_H
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


#include "GenJetParticleAssociationConst.h"
#include "GenJetParticleAssociationObj.h"



class GenJetParticleAssociationCollection;
class GenJetParticleAssociationCollectionIterator;
class ConstGenJetParticleAssociation;

class GenJetParticleAssociation {

  friend GenJetParticleAssociationCollection;
  friend GenJetParticleAssociationCollectionIterator;
  friend ConstGenJetParticleAssociation;

public:

  /// default constructor
  GenJetParticleAssociation();
  
  /// constructor from existing GenJetParticleAssociationObj
  GenJetParticleAssociation(GenJetParticleAssociationObj* obj);
  /// copy constructor
  GenJetParticleAssociation(const GenJetParticleAssociation& other);
  /// copy-assignment operator
  GenJetParticleAssociation& operator=(const GenJetParticleAssociation& other);
  /// support cloning (deep-copy)
  GenJetParticleAssociation clone() const;
  /// destructor
  ~GenJetParticleAssociation();

  /// conversion to const object
  operator ConstGenJetParticleAssociation () const;

public:

  const ConstGenJet Jet() const;
  const ConstMCParticle Particle() const;

  void Jet(ConstGenJet value);
  void Particle(ConstMCParticle value);


  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from GenJetParticleAssociationObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const GenJetParticleAssociation& other) const {
       return (m_obj==other.m_obj);
  }

  bool operator==(const ConstGenJetParticleAssociation& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const GenJetParticleAssociation& p1,
//       const GenJetParticleAssociation& p2 );

  const podio::ObjectID getObjectID() const;

private:
  GenJetParticleAssociationObj* m_obj;

};



#endif
