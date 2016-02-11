#ifndef TrackStateAssociationOBJ_H
#define TrackStateAssociationOBJ_H

// std includes
#include <atomic>
#include <iostream>

// data model specific includes
#include "podio/ObjBase.h"
#include "TrackStateAssociationData.h"



// forward declarations
class TrackStateAssociation;
class ConstTrackStateAssociation;
namespace fcc {class ConstTrack;
class ConstTrackState;
}


namespace fcc {
class TrackStateAssociationObj : public podio::ObjBase {
public:
  /// constructor
  TrackStateAssociationObj();
  /// copy constructor (does a deep-copy of relation containers)
  TrackStateAssociationObj(const TrackStateAssociationObj&);
  /// constructor from ObjectID and TrackStateAssociationData
  /// does not initialize the internal relation containers
  TrackStateAssociationObj(const podio::ObjectID id, TrackStateAssociationData data);
  virtual ~TrackStateAssociationObj();

public:
  TrackStateAssociationData data;
  ::fcc::ConstTrack* m_Track;
  ::fcc::ConstTrackState* m_State;


};
} // namespace fcc


#endif
