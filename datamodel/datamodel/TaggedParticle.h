#ifndef TaggedParticle_H
#define TaggedParticle_H
#include "TaggedParticleData.h"
#include <vector>
#include "podio/ObjectID.h"

//forward declarations
namespace fcc {
class Particle;
class ConstParticle;
}


#include "TaggedParticleConst.h"
#include "TaggedParticleObj.h"

namespace fcc {

class TaggedParticleCollection;
class TaggedParticleCollectionIterator;
class ConstTaggedParticle;

/** @class TaggedParticle
 *  Association between a Particle and some arbitrary Tag information
 *  @author: C. Helsens, J. Lingemann
 */
class TaggedParticle {

  friend TaggedParticleCollection;
  friend TaggedParticleCollectionIterator;
  friend ConstTaggedParticle;

public:

  /// default constructor
  TaggedParticle();
  TaggedParticle(float value);

  /// constructor from existing TaggedParticleObj
  TaggedParticle(TaggedParticleObj* obj);
  /// copy constructor
  TaggedParticle(const TaggedParticle& other);
  /// copy-assignment operator
  TaggedParticle& operator=(const TaggedParticle& other);
  /// support cloning (deep-copy)
  TaggedParticle clone() const;
  /// destructor
  ~TaggedParticle();

  /// conversion to const object
  operator ConstTaggedParticle () const;

public:

  /// Access the  the value of the tag
  const float& value() const;
  /// Access the  Reference to the Particle
  const fcc::ConstParticle particle() const;

  /// Set the  the value of the tag
  void value(float value);

  /// Set the  Reference to the Particle
  void particle(fcc::ConstParticle value);



  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from TaggedParticleObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const TaggedParticle& other) const {
    return (m_obj==other.m_obj);
  }

  bool operator==(const ConstTaggedParticle& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const TaggedParticle& p1,
//       const TaggedParticle& p2 );
  bool operator<(const TaggedParticle& other) const { return m_obj < other.m_obj  ; }

  const podio::ObjectID getObjectID() const;

private:
  TaggedParticleObj* m_obj;

};

} // namespace fcc

#endif
