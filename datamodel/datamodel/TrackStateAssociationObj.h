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
class ConstTrack;
class ConstTrackState;



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
  ConstTrack* m_Track;
  ConstTrackState* m_State;


};



#endif
