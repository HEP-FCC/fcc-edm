#ifndef Particle_H
#define Particle_H
#include "BareParticle.h"
#include "ParticleData.h"
#include <vector>
#include "podio/ObjectID.h"

// Reconstructed particle
// author: C. Bernet, B. Hegner

//forward declarations


#include "ParticleConst.h"
#include "ParticleObj.h"

namespace fcc {

class ParticleCollection;
class ParticleCollectionIterator;
class ConstParticle;

class Particle {

  friend ParticleCollection;
  friend ParticleCollectionIterator;
  friend ConstParticle;

public:

  /// default constructor
  Particle();
  Particle(fcc::BareParticle Core);

  /// constructor from existing ParticleObj
  Particle(ParticleObj* obj);
  /// copy constructor
  Particle(const Particle& other);
  /// copy-assignment operator
  Particle& operator=(const Particle& other);
  /// support cloning (deep-copy)
  Particle clone() const;
  /// destructor
  ~Particle();

  /// conversion to const object
  operator ConstParticle () const;

public:

  const fcc::BareParticle& Core() const;

  fcc::BareParticle& Core();
  void Core(class fcc::BareParticle value);



  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from ParticleObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const Particle& other) const {
    return (m_obj==other.m_obj);
  }

  bool operator==(const ConstParticle& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const Particle& p1,
//       const Particle& p2 );

  const podio::ObjectID getObjectID() const;

private:
  ParticleObj* m_obj;

};

} // namespace fcc

#endif
