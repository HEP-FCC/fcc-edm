#ifndef ConstSimCaloHit_H
#define ConstSimCaloHit_H
#include "SimCaloHitData.h"
#include "BareHit.h"

#include <vector>
#include "podio/ObjectID.h"

//  contains basic hit information
// author: C. Bernet, B. Hegner

//forward declarations


#include "SimCaloHitObj.h"



class SimCaloHitObj;
class SimCaloHit;
class SimCaloHitCollection;
class SimCaloHitCollectionIterator;

class ConstSimCaloHit {

  friend SimCaloHit;
  friend SimCaloHitCollection;
  friend SimCaloHitCollectionIterator;

public:

  /// default constructor
  ConstSimCaloHit();
  ConstSimCaloHit(BareHit Core);

  /// constructor from existing SimCaloHitObj
  ConstSimCaloHit(SimCaloHitObj* obj);
  /// copy constructor
  ConstSimCaloHit(const ConstSimCaloHit& other);
  /// copy-assignment operator
  ConstSimCaloHit& operator=(const ConstSimCaloHit& other);
  /// support cloning (deep-copy)
  ConstSimCaloHit clone() const;
  /// destructor
  ~ConstSimCaloHit();


public:

  const BareHit& Core() const;


  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from SimCaloHitObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const ConstSimCaloHit& other) const {
       return (m_obj==other.m_obj);
  }

  bool operator==(const SimCaloHit& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const SimCaloHit& p1,
//       const SimCaloHit& p2 );

  const podio::ObjectID getObjectID() const;

private:
  SimCaloHitObj* m_obj;

};


#endif
