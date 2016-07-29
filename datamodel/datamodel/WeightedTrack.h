#ifndef WeightedTrack_H
#define WeightedTrack_H
#include "WeightedTrackData.h"
#include <vector>
#include "podio/ObjectID.h"

//forward declarations
namespace fcc {
class Track;
class ConstTrack;
}


#include "WeightedTrackConst.h"
#include "WeightedTrackObj.h"

namespace fcc {

class WeightedTrackCollection;
class WeightedTrackCollectionIterator;
class ConstWeightedTrack;

/** @class WeightedTrack
 *  A track associated to a vertex with its weight.
 *  @author: J. Lingemann
 */
class WeightedTrack {

  friend WeightedTrackCollection;
  friend WeightedTrackCollectionIterator;
  friend ConstWeightedTrack;

public:

  /// default constructor
  WeightedTrack();
  WeightedTrack(float weight);

  /// constructor from existing WeightedTrackObj
  WeightedTrack(WeightedTrackObj* obj);
  /// copy constructor
  WeightedTrack(const WeightedTrack& other);
  /// copy-assignment operator
  WeightedTrack& operator=(const WeightedTrack& other);
  /// support cloning (deep-copy)
  WeightedTrack clone() const;
  /// destructor
  ~WeightedTrack();

  /// conversion to const object
  operator ConstWeightedTrack () const;

public:

  /// Access the  Weight of the track in the vertex
  const float& weight() const;
  /// Access the  The track.
  const fcc::ConstTrack track() const;

  /// Set the  Weight of the track in the vertex
  void weight(float value);

  /// Set the  The track.
  void track(fcc::ConstTrack value);



  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from WeightedTrackObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const WeightedTrack& other) const {
    return (m_obj==other.m_obj);
  }

  bool operator==(const ConstWeightedTrack& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const WeightedTrack& p1,
//       const WeightedTrack& p2 );
  bool operator<(const WeightedTrack& other) const { return m_obj < other.m_obj  ; }

  const podio::ObjectID getObjectID() const;

private:
  WeightedTrackObj* m_obj;

};

} // namespace fcc

#endif
