#ifndef ConstTaggedParticle_H
#define ConstTaggedParticle_H
#include "TaggedParticleData.h"
#include <vector>
#include "podio/ObjectID.h"

//forward declarations
namespace fcc {
class Particle;
class ConstParticle;
}


#include "TaggedParticleObj.h"

namespace fcc {

class TaggedParticleObj;
class TaggedParticle;
class TaggedParticleCollection;
class TaggedParticleCollectionIterator;

/** @class ConstTaggedParticle
 *  Association between a Particle and some arbitrary Tag information
 *  @author: C. Helsens, J. Lingemann
 */

class ConstTaggedParticle {

  friend TaggedParticle;
  friend TaggedParticleCollection;
  friend TaggedParticleCollectionIterator;

public:

  /// default constructor
  ConstTaggedParticle();
  ConstTaggedParticle(float value);

  /// constructor from existing TaggedParticleObj
  ConstTaggedParticle(TaggedParticleObj* obj);
  /// copy constructor
  ConstTaggedParticle(const ConstTaggedParticle& other);
  /// copy-assignment operator
  ConstTaggedParticle& operator=(const ConstTaggedParticle& other);
  /// support cloning (deep-copy)
  ConstTaggedParticle clone() const;
  /// destructor
  ~ConstTaggedParticle();


public:

  /// Access the  the value of the tag
  const float& value() const;
  /// Access the  Reference to the Particle
  const fcc::ConstParticle particle() const;



  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from TaggedParticleObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const ConstTaggedParticle& other) const {
       return (m_obj==other.m_obj);
  }

  bool operator==(const TaggedParticle& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const TaggedParticle& p1,
//       const TaggedParticle& p2 );
  bool operator<(const ConstTaggedParticle& other) const { return m_obj < other.m_obj  ; }

  const podio::ObjectID getObjectID() const;

private:
  TaggedParticleObj* m_obj;

};
} // namespace fcc

#endif
