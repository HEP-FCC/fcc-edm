#ifndef ConstMET_H
#define ConstMET_H
#include "METData.h"
#include <vector>
#include "podio/ObjectID.h"

// Naive MET type
// author: C. Bernet, B. Hegner

//forward declarations


#include "METObj.h"

namespace fcc {

class METObj;
class MET;
class METCollection;
class METCollectionIterator;

class ConstMET {

  friend MET;
  friend METCollection;
  friend METCollectionIterator;

public:

  /// default constructor
  ConstMET();
  ConstMET(float Magnitude,float Phi,float ScalarSum);

  /// constructor from existing METObj
  ConstMET(METObj* obj);
  /// copy constructor
  ConstMET(const ConstMET& other);
  /// copy-assignment operator
  ConstMET& operator=(const ConstMET& other);
  /// support cloning (deep-copy)
  ConstMET clone() const;
  /// destructor
  ~ConstMET();


public:

  const float& Magnitude() const;
  const float& Phi() const;
  const float& ScalarSum() const;



  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from METObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const ConstMET& other) const {
       return (m_obj==other.m_obj);
  }

  bool operator==(const MET& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const MET& p1,
//       const MET& p2 );

  const podio::ObjectID getObjectID() const;

private:
  METObj* m_obj;

};
} // namespace fcc

#endif
