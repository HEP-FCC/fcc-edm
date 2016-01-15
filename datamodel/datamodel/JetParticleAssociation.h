#ifndef JetParticleAssociation_H
#define JetParticleAssociation_H
#include "JetParticleAssociationData.h"

#include <vector>
#include "podio/ObjectID.h"

// Association between a Jet and a Particle. Used to keep track of jet constituents
// author: C. Bernet, B. Hegner

//forward declarations
class Jet;
class ConstJet;
class Particle;
class ConstParticle;


#include "JetParticleAssociationConst.h"
#include "JetParticleAssociationObj.h"



class JetParticleAssociationCollection;
class JetParticleAssociationCollectionIterator;
class ConstJetParticleAssociation;

class JetParticleAssociation {

  friend JetParticleAssociationCollection;
  friend JetParticleAssociationCollectionIterator;
  friend ConstJetParticleAssociation;

public:

  /// default constructor
  JetParticleAssociation();
  
  /// constructor from existing JetParticleAssociationObj
  JetParticleAssociation(JetParticleAssociationObj* obj);
  /// copy constructor
  JetParticleAssociation(const JetParticleAssociation& other);
  /// copy-assignment operator
  JetParticleAssociation& operator=(const JetParticleAssociation& other);
  /// support cloning (deep-copy)
  JetParticleAssociation clone() const;
  /// destructor
  ~JetParticleAssociation();

  /// conversion to const object
  operator ConstJetParticleAssociation () const;

public:

  const ConstJet Jet() const;
  const ConstParticle Particle() const;

  void Jet(ConstJet value);
  void Particle(ConstParticle value);


  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from JetParticleAssociationObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const JetParticleAssociation& other) const {
       return (m_obj==other.m_obj);
  }

  bool operator==(const ConstJetParticleAssociation& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const JetParticleAssociation& p1,
//       const JetParticleAssociation& p2 );

  const podio::ObjectID getObjectID() const;

private:
  JetParticleAssociationObj* m_obj;

};



#endif
