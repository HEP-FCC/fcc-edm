#ifndef MCParticle_H
#define MCParticle_H
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


#include "MCParticleConst.h"
#include "MCParticleObj.h"

namespace fcc {

class MCParticleCollection;
class MCParticleCollectionIterator;
class ConstMCParticle;

/** @class MCParticle
 *  Monte-Carlo Particle, either generated or simulated.
 *  @author: C. Bernet, B. Hegner
 */
class MCParticle {

  friend MCParticleCollection;
  friend MCParticleCollectionIterator;
  friend ConstMCParticle;

public:

  /// default constructor
  MCParticle();
  MCParticle(fcc::BareParticle core);

  /// constructor from existing MCParticleObj
  MCParticle(MCParticleObj* obj);
  /// copy constructor
  MCParticle(const MCParticle& other);
  /// copy-assignment operator
  MCParticle& operator=(const MCParticle& other);
  /// support cloning (deep-copy)
  MCParticle clone() const;
  /// destructor
  ~MCParticle();

  /// conversion to const object
  operator ConstMCParticle () const;

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

  /// Get reference to the  Basic particle information.
  fcc::BareParticle& core();
  /// Set the  Basic particle information.
  void core(class fcc::BareParticle value);
  /// Set the  member of  Basic particle information.
  void bits(unsigned value);

  /// Set the  member of  Basic particle information.
  void charge(int value);

  /// Get reference to the member of  Basic particle information.
  ::fcc::LorentzVector& p4();
  /// Set the  member of  Basic particle information.
  void p4(class ::fcc::LorentzVector value);
  /// Set the  member of  Basic particle information.
  void status(unsigned value);

  /// Set the  member of  Basic particle information.
  void type(int value);

  /// Get reference to the member of  Basic particle information.
  ::fcc::Point& vertex();
  /// Set the  member of  Basic particle information.
  void vertex(class ::fcc::Point value);
  /// Set the  Reference to the vertex in which the particle was created.
  void startVertex(fcc::ConstGenVertex value);
  /// Set the  Reference to the vertex in which the particle was created.
  void endVertex(fcc::ConstGenVertex value);



  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from MCParticleObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const MCParticle& other) const {
    return (m_obj==other.m_obj);
  }

  bool operator==(const ConstMCParticle& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const MCParticle& p1,
//       const MCParticle& p2 );
  bool operator<(const MCParticle& other) const { return m_obj < other.m_obj  ; }

  const podio::ObjectID getObjectID() const;

private:
  MCParticleObj* m_obj;

};

} // namespace fcc

#endif
