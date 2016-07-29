#ifndef ConstWeightedTrack_H
#define ConstWeightedTrack_H
#include "WeightedTrackData.h"
#include <vector>
#include "podio/ObjectID.h"

//forward declarations
namespace fcc {
class Track;
class ConstTrack;
}


#include "WeightedTrackObj.h"

namespace fcc {

class WeightedTrackObj;
class WeightedTrack;
class WeightedTrackCollection;
class WeightedTrackCollectionIterator;

/** @class ConstWeightedTrack
 *  A track associated to a vertex with its weight.
 *  @author: J. Lingemann
 */

class ConstWeightedTrack {

  friend WeightedTrack;
  friend WeightedTrackCollection;
  friend WeightedTrackCollectionIterator;

public:

  /// default constructor
  ConstWeightedTrack();
  ConstWeightedTrack(float weight);

  /// constructor from existing WeightedTrackObj
  ConstWeightedTrack(WeightedTrackObj* obj);
  /// copy constructor
  ConstWeightedTrack(const ConstWeightedTrack& other);
  /// copy-assignment operator
  ConstWeightedTrack& operator=(const ConstWeightedTrack& other);
  /// support cloning (deep-copy)
  ConstWeightedTrack clone() const;
  /// destructor
  ~ConstWeightedTrack();


public:

  /// Access the  Weight of the track in the vertex
  const float& weight() const;
  /// Access the  The track.
  const fcc::ConstTrack track() const;



  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from WeightedTrackObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const ConstWeightedTrack& other) const {
       return (m_obj==other.m_obj);
  }

  bool operator==(const WeightedTrack& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const WeightedTrack& p1,
//       const WeightedTrack& p2 );
  bool operator<(const ConstWeightedTrack& other) const { return m_obj < other.m_obj  ; }

  const podio::ObjectID getObjectID() const;

private:
  WeightedTrackObj* m_obj;

};
} // namespace fcc

#endif
