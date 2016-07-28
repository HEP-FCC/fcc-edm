#include "WeightedTrackObj.h"
#include "TrackConst.h"


namespace fcc {
WeightedTrackObj::WeightedTrackObj() :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}, data(), m_track(nullptr)

{ }

WeightedTrackObj::WeightedTrackObj(const podio::ObjectID id, WeightedTrackData data) :
    ObjBase{id,0}, data(data)
{ }

WeightedTrackObj::WeightedTrackObj(const WeightedTrackObj& other) :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    , data(other.data), m_track(nullptr)
{
  if (other.m_track != nullptr) {
     m_track = new ::fcc::ConstTrack(*(other.m_track));
  }

}

WeightedTrackObj::~WeightedTrackObj() {
  if (id.index == podio::ObjectID::untracked) {

  }
    if (m_track != nullptr) delete m_track;

}
} // namespace fcc
