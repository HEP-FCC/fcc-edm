#ifndef MET_H
#define MET_H
#include "METData.h"

#include <vector>
#include "podio/ObjectID.h"

//  .
// author: C. Bernet, B. Hegner

//forward declarations


#include "METConst.h"
#include "METObj.h"

namespace fcc {

class METCollection;
class METCollectionIterator;
class ConstMET;

class MET {

  friend METCollection;
  friend METCollectionIterator;
  friend ConstMET;

public:

  /// default constructor
  MET();
    MET(float Pt,float Phi);

  /// constructor from existing METObj
  MET(METObj* obj);
  /// copy constructor
  MET(const MET& other);
  /// copy-assignment operator
  MET& operator=(const MET& other);
  /// support cloning (deep-copy)
  MET clone() const;
  /// destructor
  ~MET();

  /// conversion to const object
  operator ConstMET () const;

public:

  const float& Pt() const;
  const float& Phi() const;

  void Pt(float value);
  void Phi(float value);


  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from METObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const MET& other) const {
       return (m_obj==other.m_obj);
  }

  bool operator==(const ConstMET& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const MET& p1,
//       const MET& p2 );

  const podio::ObjectID getObjectID() const;

private:
  METObj* m_obj;

};

} // namespace fcc

#endif
