#ifndef ConstJet_H
#define ConstJet_H
#include "JetData.h"
#include "BareJet.h"

#include <vector>
#include "podio/ObjectID.h"

//  Basic jet information.
// author: C. Bernet, B. Hegner

//forward declarations


#include "JetObj.h"

namespace fcc {

class JetObj;
class Jet;
class JetCollection;
class JetCollectionIterator;

class ConstJet {

  friend Jet;
  friend JetCollection;
  friend JetCollectionIterator;

public:

  /// default constructor
  ConstJet();
  ConstJet(fcc::BareJet Core);

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

  const fcc::BareJet& Core() const;


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

  const podio::ObjectID getObjectID() const;

private:
  JetObj* m_obj;

};
} // namespace fcc

#endif
