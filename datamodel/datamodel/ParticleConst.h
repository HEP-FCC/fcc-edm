#ifndef ConstParticle_H
#define ConstParticle_H
#include "BareParticle.h"
#include "ParticleData.h"
#include <vector>
#include "Track.h"
#include "CaloCluster.h"
#include <vector>
#include "podio/ObjectID.h"

//forward declarations


#include "ParticleObj.h"

namespace fcc {

class ParticleObj;
class Particle;
class ParticleCollection;
class ParticleCollectionIterator;

/** @class ConstParticle
 *  Reconstructed particle
 *  @author: C. Bernet, B. Hegner
 */

class ConstParticle {

  friend Particle;
  friend ParticleCollection;
  friend ParticleCollectionIterator;

public:

  /// default constructor
  ConstParticle();
  ConstParticle(fcc::BareParticle core);

  /// constructor from existing ParticleObj
  ConstParticle(ParticleObj* obj);
  /// copy constructor
  ConstParticle(const ConstParticle& other);
  /// copy-assignment operator
  ConstParticle& operator=(const ConstParticle& other);
  /// support cloning (deep-copy)
  ConstParticle clone() const;
  /// destructor
  ~ConstParticle();


public:

  /// Access the  Contains basic particle information.
  const fcc::BareParticle& core() const;
  /// Access the member of  Contains basic particle information.
  const unsigned& bits() const;
  /// Access the member of  Contains basic particle information.
  const int& charge() const;
  /// Access the member of  Contains basic particle information.
  const ::fcc::LorentzVector& p4() const;
  /// Access the member of  Contains basic particle information.
  const unsigned& status() const;
  /// Access the member of  Contains basic particle information.
  const int& type() const;
  /// Access the member of  Contains basic particle information.
  const ::fcc::Point& vertex() const;

  unsigned int tracks_size() const;
  fcc::ConstTrack tracks(unsigned int) const;
  std::vector<fcc::ConstTrack>::const_iterator tracks_begin() const;
  std::vector<fcc::ConstTrack>::const_iterator tracks_end() const;
  unsigned int clusters_size() const;
  fcc::ConstCaloCluster clusters(unsigned int) const;
  std::vector<fcc::ConstCaloCluster>::const_iterator clusters_begin() const;
  std::vector<fcc::ConstCaloCluster>::const_iterator clusters_end() const;


  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from ParticleObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const ConstParticle& other) const {
       return (m_obj==other.m_obj);
  }

  bool operator==(const Particle& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const Particle& p1,
//       const Particle& p2 );
  bool operator<(const ConstParticle& other) const { return m_obj < other.m_obj  ; }

  const podio::ObjectID getObjectID() const;

private:
  ParticleObj* m_obj;

};
} // namespace fcc

#endif
