#ifndef Particle_H
#define Particle_H
#include "BareParticle.h"
#include "ParticleData.h"
#include <vector>
#include "Track.h"
#include "CaloCluster.h"
#include <vector>
#include "podio/ObjectID.h"

//forward declarations


#include "ParticleConst.h"
#include "ParticleObj.h"

namespace fcc {

class ParticleCollection;
class ParticleCollectionIterator;
class ConstParticle;

/** @class Particle
 *  Reconstructed particle
 *  @author: C. Bernet, B. Hegner
 */
class Particle {

  friend ParticleCollection;
  friend ParticleCollectionIterator;
  friend ConstParticle;

public:

  /// default constructor
  Particle();
  Particle(fcc::BareParticle core);

  /// constructor from existing ParticleObj
  Particle(ParticleObj* obj);
  /// copy constructor
  Particle(const Particle& other);
  /// copy-assignment operator
  Particle& operator=(const Particle& other);
  /// support cloning (deep-copy)
  Particle clone() const;
  /// destructor
  ~Particle();

  /// conversion to const object
  operator ConstParticle () const;

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

  /// Get reference to the  Contains basic particle information.
  fcc::BareParticle& core();
  /// Set the  Contains basic particle information.
  void core(class fcc::BareParticle value);
  /// Set the  member of  Contains basic particle information.
  void bits(unsigned value);

  /// Set the  member of  Contains basic particle information.
  void charge(int value);

  /// Get reference to the member of  Contains basic particle information.
  ::fcc::LorentzVector& p4();
  /// Set the  member of  Contains basic particle information.
  void p4(class ::fcc::LorentzVector value);
  /// Set the  member of  Contains basic particle information.
  void status(unsigned value);

  /// Set the  member of  Contains basic particle information.
  void type(int value);

  /// Get reference to the member of  Contains basic particle information.
  ::fcc::Point& vertex();
  /// Set the  member of  Contains basic particle information.
  void vertex(class ::fcc::Point value);

  void addtracks(fcc::ConstTrack);
  unsigned int tracks_size() const;
  fcc::ConstTrack tracks(unsigned int) const;
  std::vector<fcc::ConstTrack>::const_iterator tracks_begin() const;
  std::vector<fcc::ConstTrack>::const_iterator tracks_end() const;

  void addclusters(fcc::ConstCaloCluster);
  unsigned int clusters_size() const;
  fcc::ConstCaloCluster clusters(unsigned int) const;
  std::vector<fcc::ConstCaloCluster>::const_iterator clusters_begin() const;
  std::vector<fcc::ConstCaloCluster>::const_iterator clusters_end() const;



  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from ParticleObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const Particle& other) const {
    return (m_obj==other.m_obj);
  }

  bool operator==(const ConstParticle& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const Particle& p1,
//       const Particle& p2 );
  bool operator<(const Particle& other) const { return m_obj < other.m_obj  ; }

  const podio::ObjectID getObjectID() const;

private:
  ParticleObj* m_obj;

};

} // namespace fcc

#endif
