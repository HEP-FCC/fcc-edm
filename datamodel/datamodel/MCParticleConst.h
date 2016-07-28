#ifndef ConstMCParticle_H
#define ConstMCParticle_H
#include "BareParticle.h"
#include "MCParticleData.h"
#include <vector>
#include "podio/ObjectID.h"

//forward declarations
namespace fcc {
class GenVertex;
class ConstGenVertex;
class GenVertex;
class ConstGenVertex;
}


#include "MCParticleObj.h"

namespace fcc {

class MCParticleObj;
class MCParticle;
class MCParticleCollection;
class MCParticleCollectionIterator;

/** @class ConstMCParticle
 *  Monte-Carlo Particle, either generated or simulated.
 *  @author: C. Bernet, B. Hegner
 */

class ConstMCParticle {

  friend MCParticle;
  friend MCParticleCollection;
  friend MCParticleCollectionIterator;

public:

  /// default constructor
  ConstMCParticle();
  ConstMCParticle(fcc::BareParticle core);

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

  /// Access the  Basic particle information.
  const fcc::BareParticle& core() const;
  /// Access the member of  Basic particle information.
  const unsigned& bits() const;
  /// Access the member of  Basic particle information.
  const int& charge() const;
  /// Access the member of  Basic particle information.
  const ::fcc::LorentzVector& p4() const;
  /// Access the member of  Basic particle information.
  const unsigned& status() const;
  /// Access the member of  Basic particle information.
  const int& type() const;
  /// Access the member of  Basic particle information.
  const ::fcc::Point& vertex() const;
  /// Access the  Reference to the vertex in which the particle was created.
  const fcc::ConstGenVertex startVertex() const;
  /// Access the  Reference to the vertex in which the particle was created.
  const fcc::ConstGenVertex endVertex() const;



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
  bool operator<(const ConstMCParticle& other) const { return m_obj < other.m_obj  ; }

  const podio::ObjectID getObjectID() const;

private:
  MCParticleObj* m_obj;

};
} // namespace fcc

#endif
