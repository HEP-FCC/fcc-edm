#ifndef ConstTrackStateAssociation_H
#define ConstTrackStateAssociation_H
#include "TrackStateAssociationData.h"

#include <vector>
#include "podio/ObjectID.h"

// Association between a track and a track state.
// author: C. Bernet, B. Hegner

//forward declarations
namespace fcc {
class Track;
class ConstTrack;
class TrackState;
class ConstTrackState;
}


#include "TrackStateAssociationObj.h"

namespace fcc {

class TrackStateAssociationObj;
class TrackStateAssociation;
class TrackStateAssociationCollection;
class TrackStateAssociationCollectionIterator;

class ConstTrackStateAssociation {

  friend TrackStateAssociation;
  friend TrackStateAssociationCollection;
  friend TrackStateAssociationCollectionIterator;

public:

  /// default constructor
  ConstTrackStateAssociation();
  
  /// constructor from existing TrackStateAssociationObj
  ConstTrackStateAssociation(TrackStateAssociationObj* obj);
  /// copy constructor
  ConstTrackStateAssociation(const ConstTrackStateAssociation& other);
  /// copy-assignment operator
  ConstTrackStateAssociation& operator=(const ConstTrackStateAssociation& other);
  /// support cloning (deep-copy)
  ConstTrackStateAssociation clone() const;
  /// destructor
  ~ConstTrackStateAssociation();


public:

  const fcc::ConstTrack Track() const;
  const fcc::ConstTrackState State() const;


  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from TrackStateAssociationObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const ConstTrackStateAssociation& other) const {
       return (m_obj==other.m_obj);
  }

  bool operator==(const TrackStateAssociation& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const TrackStateAssociation& p1,
//       const TrackStateAssociation& p2 );

  const podio::ObjectID getObjectID() const;

private:
  TrackStateAssociationObj* m_obj;

};
} // namespace fcc

#endif
