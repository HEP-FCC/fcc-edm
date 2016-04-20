#ifndef ConstParticle_H
#define ConstParticle_H
#include "BareParticle.h"
#include "ParticleData.h"
#include <vector>
#include "podio/ObjectID.h"

// Reconstructed particle
// author: C. Bernet, B. Hegner

//forward declarations


#include "ParticleObj.h"

namespace fcc {

class ParticleObj;
class Particle;
class ParticleCollection;
class ParticleCollectionIterator;

class ConstParticle {

  friend Particle;
  friend ParticleCollection;
  friend ParticleCollectionIterator;

public:

  /// default constructor
  ConstParticle();
  ConstParticle(fcc::BareParticle Core);

  /// constructor from existing ParticleObj
  ConstParticle(ParticleObj* obj);
  /// copy constructor
  ConstParticle(const ConstParticle& other);
  /// copy-assignment operator
  ConstParticle& operator=(const ConstParticle& other);
  /// support cloning (deep-copy)
  ConstParticle clone() const;
  /// destructor
  ~ConstParticle();


public:

  const fcc::BareParticle& Core() const;



  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from ParticleObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const ConstParticle& other) const {
       return (m_obj==other.m_obj);
  }

  bool operator==(const Particle& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const Particle& p1,
//       const Particle& p2 );

  const podio::ObjectID getObjectID() const;

private:
  ParticleObj* m_obj;

};
} // namespace fcc

#endif
