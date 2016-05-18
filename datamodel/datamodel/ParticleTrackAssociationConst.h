#ifndef ConstParticleTrackAssociation_H
#define ConstParticleTrackAssociation_H
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


#include "ParticleTrackAssociationObj.h"

namespace fcc {

class ParticleTrackAssociationObj;
class ParticleTrackAssociation;
class ParticleTrackAssociationCollection;
class ParticleTrackAssociationCollectionIterator;

class ConstParticleTrackAssociation {

  friend ParticleTrackAssociation;
  friend ParticleTrackAssociationCollection;
  friend ParticleTrackAssociationCollectionIterator;

public:

  /// default constructor
  ConstParticleTrackAssociation();
  
  /// constructor from existing ParticleTrackAssociationObj
  ConstParticleTrackAssociation(ParticleTrackAssociationObj* obj);
  /// copy constructor
  ConstParticleTrackAssociation(const ConstParticleTrackAssociation& other);
  /// copy-assignment operator
  ConstParticleTrackAssociation& operator=(const ConstParticleTrackAssociation& other);
  /// support cloning (deep-copy)
  ConstParticleTrackAssociation clone() const;
  /// destructor
  ~ConstParticleTrackAssociation();


public:

  const fcc::ConstParticle Particle() const;
  const fcc::ConstTrack Track() const;



  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from ParticleTrackAssociationObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const ConstParticleTrackAssociation& other) const {
       return (m_obj==other.m_obj);
  }

  bool operator==(const ParticleTrackAssociation& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const ParticleTrackAssociation& p1,
//       const ParticleTrackAssociation& p2 );
  bool operator<(const ConstParticleTrackAssociation& other) const { return m_obj < other.m_obj  ; }

  const podio::ObjectID getObjectID() const;

private:
  ParticleTrackAssociationObj* m_obj;

};
} // namespace fcc

#endif
