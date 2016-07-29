#ifndef ConstJet_H
#define ConstJet_H
#include "BareJet.h"
#include "JetData.h"
#include <vector>
#include "Particle.h"
#include <vector>
#include "podio/ObjectID.h"

//forward declarations


#include "JetObj.h"

namespace fcc {

class JetObj;
class Jet;
class JetCollection;
class JetCollectionIterator;

/** @class ConstJet
 *  Reconstructed jet.
 *  @author: C. Bernet, B. Hegner
 */

class ConstJet {

  friend Jet;
  friend JetCollection;
  friend JetCollectionIterator;

public:

  /// default constructor
  ConstJet();
  ConstJet(fcc::BareJet core);

  /// constructor from existing JetObj
  ConstJet(JetObj* obj);
  /// copy constructor
  ConstJet(const ConstJet& other);
  /// copy-assignment operator
  ConstJet& operator=(const ConstJet& other);
  /// support cloning (deep-copy)
  ConstJet clone() const;
  /// destructor
  ~ConstJet();


public:

  /// Access the  Basic jet information.
  const fcc::BareJet& core() const;
  /// Access the member of  Basic jet information.
  const float& area() const;
  /// Access the member of  Basic jet information.
  const unsigned& bits() const;
  /// Access the member of  Basic jet information.
  const ::fcc::LorentzVector& p4() const;

  unsigned int particles_size() const;
  fcc::ConstParticle particles(unsigned int) const;
  std::vector<fcc::ConstParticle>::const_iterator particles_begin() const;
  std::vector<fcc::ConstParticle>::const_iterator particles_end() const;


  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from JetObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const ConstJet& other) const {
       return (m_obj==other.m_obj);
  }

  bool operator==(const Jet& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const Jet& p1,
//       const Jet& p2 );
  bool operator<(const ConstJet& other) const { return m_obj < other.m_obj  ; }

  const podio::ObjectID getObjectID() const;

private:
  JetObj* m_obj;

};
} // namespace fcc

#endif
