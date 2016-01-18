#ifndef Track_H
#define Track_H
#include "TrackData.h"

#include <vector>
#include "podio/ObjectID.h"

//  Stores flags
// author: C. Bernet, B. Hegner

//forward declarations


#include "TrackConst.h"
#include "TrackObj.h"



class TrackCollection;
class TrackCollectionIterator;
class ConstTrack;

class Track {

  friend TrackCollection;
  friend TrackCollectionIterator;
  friend ConstTrack;

public:

  /// default constructor
  Track();
    Track(float Chi2,unsigned Ndf,unsigned Bits);

  /// constructor from existing TrackObj
  Track(TrackObj* obj);
  /// copy constructor
  Track(const Track& other);
  /// copy-assignment operator
  Track& operator=(const Track& other);
  /// support cloning (deep-copy)
  Track clone() const;
  /// destructor
  ~Track();

  /// conversion to const object
  operator ConstTrack () const;

public:

  const float& Chi2() const;
  const unsigned& Ndf() const;
  const unsigned& Bits() const;

  void Chi2(float value);
  void Ndf(unsigned value);
  void Bits(unsigned value);


  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from TrackObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const Track& other) const {
       return (m_obj==other.m_obj);
  }

  bool operator==(const ConstTrack& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const Track& p1,
//       const Track& p2 );

  const podio::ObjectID getObjectID() const;

private:
  TrackObj* m_obj;

};



#endif
