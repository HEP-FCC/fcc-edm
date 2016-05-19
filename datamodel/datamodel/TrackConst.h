#ifndef ConstTrack_H
#define ConstTrack_H
#include "TrackData.h"
#include <vector>
#include "podio/ObjectID.h"

// Track reconstructed from clusters in the inner tracker
// author: C. Bernet, B. Hegner

//forward declarations


#include "TrackObj.h"

namespace fcc {

class TrackObj;
class Track;
class TrackCollection;
class TrackCollectionIterator;

class ConstTrack {

  friend Track;
  friend TrackCollection;
  friend TrackCollectionIterator;

public:

  /// default constructor
  ConstTrack();
  ConstTrack(float Chi2,unsigned Ndf,unsigned Bits);

  /// constructor from existing TrackObj
  ConstTrack(TrackObj* obj);
  /// copy constructor
  ConstTrack(const ConstTrack& other);
  /// copy-assignment operator
  ConstTrack& operator=(const ConstTrack& other);
  /// support cloning (deep-copy)
  ConstTrack clone() const;
  /// destructor
  ~ConstTrack();


public:

  const float& Chi2() const;
  const unsigned& Ndf() const;
  const unsigned& Bits() const;



  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from TrackObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const ConstTrack& other) const {
       return (m_obj==other.m_obj);
  }

  bool operator==(const Track& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const Track& p1,
//       const Track& p2 );
  bool operator<(const ConstTrack& other) const { return m_obj < other.m_obj  ; }

  const podio::ObjectID getObjectID() const;

private:
  TrackObj* m_obj;

};
} // namespace fcc

#endif
