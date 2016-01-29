#ifndef SimCaloHit_H
#define SimCaloHit_H
#include "SimCaloHitData.h"
#include "BareHit.h"

#include <vector>
#include "podio/ObjectID.h"

//  contains basic hit information
// author: C. Bernet, B. Hegner

//forward declarations


#include "SimCaloHitConst.h"
#include "SimCaloHitObj.h"

namespace fcc {

class SimCaloHitCollection;
class SimCaloHitCollectionIterator;
class ConstSimCaloHit;

class SimCaloHit {

  friend SimCaloHitCollection;
  friend SimCaloHitCollectionIterator;
  friend ConstSimCaloHit;

public:

  /// default constructor
  SimCaloHit();
    SimCaloHit(fcc::BareHit Core);

  /// constructor from existing SimCaloHitObj
  SimCaloHit(SimCaloHitObj* obj);
  /// copy constructor
  SimCaloHit(const SimCaloHit& other);
  /// copy-assignment operator
  SimCaloHit& operator=(const SimCaloHit& other);
  /// support cloning (deep-copy)
  SimCaloHit clone() const;
  /// destructor
  ~SimCaloHit();

  /// conversion to const object
  operator ConstSimCaloHit () const;

public:

  const fcc::BareHit& Core() const;

  fcc::BareHit& Core();
  void Core(class fcc::BareHit value);


  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from SimCaloHitObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const SimCaloHit& other) const {
       return (m_obj==other.m_obj);
  }

  bool operator==(const ConstSimCaloHit& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const SimCaloHit& p1,
//       const SimCaloHit& p2 );

  const podio::ObjectID getObjectID() const;

private:
  SimCaloHitObj* m_obj;

};

} // namespace fcc

#endif
