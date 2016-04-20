#ifndef ParticleTrackAssociation_H
#define ParticleTrackAssociation_H
#include "ParticleTrackAssociationData.h"
#include <vector>
#include "podio/ObjectID.h"

// Association between a Particle and a Track.
// author: C. Bernet, B. Hegner

//forward declarations
namespace fcc {
class Particle;
class ConstParticle;
class Track;
class ConstTrack;
}


#include "ParticleTrackAssociationConst.h"
#include "ParticleTrackAssociationObj.h"

namespace fcc {

class ParticleTrackAssociationCollection;
class ParticleTrackAssociationCollectionIterator;
class ConstParticleTrackAssociation;

class ParticleTrackAssociation {

  friend ParticleTrackAssociationCollection;
  friend ParticleTrackAssociationCollectionIterator;
  friend ConstParticleTrackAssociation;

public:

  /// default constructor
  ParticleTrackAssociation();

  /// constructor from existing ParticleTrackAssociationObj
  ParticleTrackAssociation(ParticleTrackAssociationObj* obj);
  /// copy constructor
  ParticleTrackAssociation(const ParticleTrackAssociation& other);
  /// copy-assignment operator
  ParticleTrackAssociation& operator=(const ParticleTrackAssociation& other);
  /// support cloning (deep-copy)
  ParticleTrackAssociation clone() const;
  /// destructor
  ~ParticleTrackAssociation();

  /// conversion to const object
  operator ConstParticleTrackAssociation () const;

public:

  const fcc::ConstParticle Particle() const;
  const fcc::ConstTrack Track() const;

  void Particle(fcc::ConstParticle value);
  void Track(fcc::ConstTrack value);



  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from ParticleTrackAssociationObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const ParticleTrackAssociation& other) const {
    return (m_obj==other.m_obj);
  }

  bool operator==(const ConstParticleTrackAssociation& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const ParticleTrackAssociation& p1,
//       const ParticleTrackAssociation& p2 );

  const podio::ObjectID getObjectID() const;

private:
  ParticleTrackAssociationObj* m_obj;

};

} // namespace fcc

#endif
