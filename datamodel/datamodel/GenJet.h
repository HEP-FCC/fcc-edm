#ifndef GenJet_H
#define GenJet_H
#include "BareJet.h"
#include "GenJetData.h"
#include <vector>
#include "MCParticle.h"
#include <vector>
#include "podio/ObjectID.h"

//forward declarations


#include "GenJetConst.h"
#include "GenJetObj.h"

namespace fcc {

class GenJetCollection;
class GenJetCollectionIterator;
class ConstGenJet;

/** @class GenJet
 *  Generated jet.
 *  @author: C. Bernet, B. Hegner
 */
class GenJet {

  friend GenJetCollection;
  friend GenJetCollectionIterator;
  friend ConstGenJet;

public:

  /// default constructor
  GenJet();
  GenJet(fcc::BareJet core);

  /// constructor from existing GenJetObj
  GenJet(GenJetObj* obj);
  /// copy constructor
  GenJet(const GenJet& other);
  /// copy-assignment operator
  GenJet& operator=(const GenJet& other);
  /// support cloning (deep-copy)
  GenJet clone() const;
  /// destructor
  ~GenJet();

  /// conversion to const object
  operator ConstGenJet () const;

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

  void addparticles(fcc::ConstMCParticle);
  unsigned int particles_size() const;
  fcc::ConstMCParticle particles(unsigned int) const;
  std::vector<fcc::ConstMCParticle>::const_iterator particles_begin() const;
  std::vector<fcc::ConstMCParticle>::const_iterator particles_end() const;



  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from GenJetObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const GenJet& other) const {
    return (m_obj==other.m_obj);
  }

  bool operator==(const ConstGenJet& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const GenJet& p1,
//       const GenJet& p2 );
  bool operator<(const GenJet& other) const { return m_obj < other.m_obj  ; }

  const podio::ObjectID getObjectID() const;

private:
  GenJetObj* m_obj;

};

} // namespace fcc

#endif
