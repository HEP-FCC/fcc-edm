#ifndef TrackStateAssociation_H
#define TrackStateAssociation_H
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


#include "TrackStateAssociationConst.h"
#include "TrackStateAssociationObj.h"

namespace fcc {

class TrackStateAssociationCollection;
class TrackStateAssociationCollectionIterator;
class ConstTrackStateAssociation;

class TrackStateAssociation {

  friend TrackStateAssociationCollection;
  friend TrackStateAssociationCollectionIterator;
  friend ConstTrackStateAssociation;

public:

  /// default constructor
  TrackStateAssociation();

  /// constructor from existing TrackStateAssociationObj
  TrackStateAssociation(TrackStateAssociationObj* obj);
  /// copy constructor
  TrackStateAssociation(const TrackStateAssociation& other);
  /// copy-assignment operator
  TrackStateAssociation& operator=(const TrackStateAssociation& other);
  /// support cloning (deep-copy)
  TrackStateAssociation clone() const;
  /// destructor
  ~TrackStateAssociation();

  /// conversion to const object
  operator ConstTrackStateAssociation () const;

public:

  const fcc::ConstTrack Track() const;
  const fcc::ConstTrackState State() const;

  void Track(fcc::ConstTrack value);
  void State(fcc::ConstTrackState value);



  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from TrackStateAssociationObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const TrackStateAssociation& other) const {
    return (m_obj==other.m_obj);
  }

  bool operator==(const ConstTrackStateAssociation& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const TrackStateAssociation& p1,
//       const TrackStateAssociation& p2 );

  const podio::ObjectID getObjectID() const;

private:
  TrackStateAssociationObj* m_obj;

};

} // namespace fcc

#endif
