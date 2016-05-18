#ifndef ConstGenJet_H
#define ConstGenJet_H
#include "BareJet.h"
#include "GenJetData.h"
#include <vector>
#include "podio/ObjectID.h"

// Generated jet.
// author: C. Bernet, B. Hegner

//forward declarations


#include "GenJetObj.h"

namespace fcc {

class GenJetObj;
class GenJet;
class GenJetCollection;
class GenJetCollectionIterator;

class ConstGenJet {

  friend GenJet;
  friend GenJetCollection;
  friend GenJetCollectionIterator;

public:

  /// default constructor
  ConstGenJet();
  ConstGenJet(fcc::BareJet Core);

  /// constructor from existing GenJetObj
  ConstGenJet(GenJetObj* obj);
  /// copy constructor
  ConstGenJet(const ConstGenJet& other);
  /// copy-assignment operator
  ConstGenJet& operator=(const ConstGenJet& other);
  /// support cloning (deep-copy)
  ConstGenJet clone() const;
  /// destructor
  ~ConstGenJet();


public:

  const fcc::BareJet& Core() const;



  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from GenJetObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const ConstGenJet& other) const {
       return (m_obj==other.m_obj);
  }

  bool operator==(const GenJet& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const GenJet& p1,
//       const GenJet& p2 );
  bool operator<(const ConstGenJet& other) const { return m_obj < other.m_obj  ; }

  const podio::ObjectID getObjectID() const;

private:
  GenJetObj* m_obj;

};
} // namespace fcc

#endif
