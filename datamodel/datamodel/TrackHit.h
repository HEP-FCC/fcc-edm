#ifndef TrackHit_H
#define TrackHit_H
#include "TrackHitData.h"
#include "BareHit.h"

#include <vector>
#include "podio/ObjectID.h"

//  contains basic hit information
// author: C. Bernet, B. Hegner

//forward declarations


#include "TrackHitConst.h"
#include "TrackHitObj.h"



class TrackHitCollection;
class TrackHitCollectionIterator;
class ConstTrackHit;

class TrackHit {

  friend TrackHitCollection;
  friend TrackHitCollectionIterator;
  friend ConstTrackHit;

public:

  /// default constructor
  TrackHit();
    TrackHit(BareHit Core);

  /// constructor from existing TrackHitObj
  TrackHit(TrackHitObj* obj);
  /// copy constructor
  TrackHit(const TrackHit& other);
  /// copy-assignment operator
  TrackHit& operator=(const TrackHit& other);
  /// support cloning (deep-copy)
  TrackHit clone() const;
  /// destructor
  ~TrackHit();

  /// conversion to const object
  operator ConstTrackHit () const;

public:

  const BareHit& Core() const;

  BareHit& Core();
  void Core(class BareHit value);


  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from TrackHitObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const TrackHit& other) const {
       return (m_obj==other.m_obj);
  }

  bool operator==(const ConstTrackHit& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const TrackHit& p1,
//       const TrackHit& p2 );

  const podio::ObjectID getObjectID() const;

private:
  TrackHitObj* m_obj;

};



#endif
