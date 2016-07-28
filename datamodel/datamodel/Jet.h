#ifndef Jet_H
#define Jet_H
#include "BareJet.h"
#include "JetData.h"
#include <vector>
#include "Particle.h"
#include <vector>
#include "podio/ObjectID.h"

//forward declarations


#include "JetConst.h"
#include "JetObj.h"

namespace fcc {

class JetCollection;
class JetCollectionIterator;
class ConstJet;

/** @class Jet
 *  Reconstructed jet.
 *  @author: C. Bernet, B. Hegner
 */
class Jet {

  friend JetCollection;
  friend JetCollectionIterator;
  friend ConstJet;

public:

  /// default constructor
  Jet();
  Jet(fcc::BareJet core);

  /// constructor from existing JetObj
  Jet(JetObj* obj);
  /// copy constructor
  Jet(const Jet& other);
  /// copy-assignment operator
  Jet& operator=(const Jet& other);
  /// support cloning (deep-copy)
  Jet clone() const;
  /// destructor
  ~Jet();

  /// conversion to const object
  operator ConstJet () const;

public:

  /// Access the  Basic jet information.
  const fcc::BareJet& core() const;
  /// Access the member of  Basic jet information.
  const float& area() const;
  /// Access the member of  Basic jet information.
  const unsigned& bits() const;
  /// Access the member of  Basic jet information.
  const ::fcc::LorentzVector& p4() const;

  /// Get reference to the  Basic jet information.
  fcc::BareJet& core();
  /// Set the  Basic jet information.
  void core(class fcc::BareJet value);
  /// Set the  member of  Basic jet information.
  void area(float value);

  /// Set the  member of  Basic jet information.
  void bits(unsigned value);

  /// Get reference to the member of  Basic jet information.
  ::fcc::LorentzVector& p4();
  /// Set the  member of  Basic jet information.
  void p4(class ::fcc::LorentzVector value);

  void addparticles(fcc::ConstParticle);
  unsigned int particles_size() const;
  fcc::ConstParticle particles(unsigned int) const;
  std::vector<fcc::ConstParticle>::const_iterator particles_begin() const;
  std::vector<fcc::ConstParticle>::const_iterator particles_end() const;



  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from JetObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const Jet& other) const {
    return (m_obj==other.m_obj);
  }

  bool operator==(const ConstJet& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const Jet& p1,
//       const Jet& p2 );
  bool operator<(const Jet& other) const { return m_obj < other.m_obj  ; }

  const podio::ObjectID getObjectID() const;

private:
  JetObj* m_obj;

};

} // namespace fcc

#endif
