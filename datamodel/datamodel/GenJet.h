#ifndef GenJet_H
#define GenJet_H
#include "BareJet.h"
#include "GenJetData.h"
#include <vector>
#include "podio/ObjectID.h"

// Generated jet.
// author: C. Bernet, B. Hegner

//forward declarations


#include "GenJetConst.h"
#include "GenJetObj.h"

namespace fcc {

class GenJetCollection;
class GenJetCollectionIterator;
class ConstGenJet;

class GenJet {

  friend GenJetCollection;
  friend GenJetCollectionIterator;
  friend ConstGenJet;

public:

  /// default constructor
  GenJet();
  GenJet(fcc::BareJet Core);

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

  const fcc::BareJet& Core() const;

  fcc::BareJet& Core();
  void Core(class fcc::BareJet value);



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
