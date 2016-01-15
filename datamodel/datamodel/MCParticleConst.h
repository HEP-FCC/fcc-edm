#ifndef ConstMCParticle_H
#define ConstMCParticle_H
#include "MCParticleData.h"
#include "BareParticle.h"

#include <vector>
#include "podio/ObjectID.h"

//  Basic particle information.
// author: C. Bernet, B. Hegner

//forward declarations
class GenVertex;
class ConstGenVertex;
class GenVertex;
class ConstGenVertex;


#include "MCParticleObj.h"



class MCParticleObj;
class MCParticle;
class MCParticleCollection;
class MCParticleCollectionIterator;

class ConstMCParticle {

  friend MCParticle;
  friend MCParticleCollection;
  friend MCParticleCollectionIterator;

public:

  /// default constructor
  ConstMCParticle();
  ConstMCParticle(BareParticle Core);

  /// constructor from existing MCParticleObj
  ConstMCParticle(MCParticleObj* obj);
  /// copy constructor
  ConstMCParticle(const ConstMCParticle& other);
  /// copy-assignment operator
  ConstMCParticle& operator=(const ConstMCParticle& other);
  /// support cloning (deep-copy)
  ConstMCParticle clone() const;
  /// destructor
  ~ConstMCParticle();


public:

  const BareParticle& Core() const;
  const ConstGenVertex StartVertex() const;
  const ConstGenVertex EndVertex() const;


  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from MCParticleObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const ConstMCParticle& other) const {
       return (m_obj==other.m_obj);
  }

  bool operator==(const MCParticle& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const MCParticle& p1,
//       const MCParticle& p2 );

  const podio::ObjectID getObjectID() const;

private:
  MCParticleObj* m_obj;

};


#endif
