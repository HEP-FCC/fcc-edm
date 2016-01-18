#ifndef Jet_H
#define Jet_H
#include "JetData.h"
#include "BareJet.h"

#include <vector>
#include "podio/ObjectID.h"

//  Basic jet information.
// author: C. Bernet, B. Hegner

//forward declarations


#include "JetConst.h"
#include "JetObj.h"



class JetCollection;
class JetCollectionIterator;
class ConstJet;

class Jet {

  friend JetCollection;
  friend JetCollectionIterator;
  friend ConstJet;

public:

  /// default constructor
  Jet();
    Jet(BareJet Core);

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

  const BareJet& Core() const;

  BareJet& Core();
  void Core(class BareJet value);


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

  const podio::ObjectID getObjectID() const;

private:
  JetObj* m_obj;

};



#endif
