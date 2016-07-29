#ifndef TaggedJet_H
#define TaggedJet_H
#include "TaggedJetData.h"
#include <vector>
#include "podio/ObjectID.h"

//forward declarations
namespace fcc {
class Jet;
class ConstJet;
}


#include "TaggedJetConst.h"
#include "TaggedJetObj.h"

namespace fcc {

class TaggedJetCollection;
class TaggedJetCollectionIterator;
class ConstTaggedJet;

/** @class TaggedJet
 *  Association between a Jet and arbitrary Tag information
 *  @author: C. Bernet, Z. Drasal, J. Lingemann
 */
class TaggedJet {

  friend TaggedJetCollection;
  friend TaggedJetCollectionIterator;
  friend ConstTaggedJet;

public:

  /// default constructor
  TaggedJet();
  TaggedJet(float tag);

  /// constructor from existing TaggedJetObj
  TaggedJet(TaggedJetObj* obj);
  /// copy constructor
  TaggedJet(const TaggedJet& other);
  /// copy-assignment operator
  TaggedJet& operator=(const TaggedJet& other);
  /// support cloning (deep-copy)
  TaggedJet clone() const;
  /// destructor
  ~TaggedJet();

  /// conversion to const object
  operator ConstTaggedJet () const;

public:

  /// Access the  Result of the tagging algorithm
  const float& tag() const;
  /// Access the  Reference to the jet
  const fcc::ConstJet jet() const;

  /// Set the  Result of the tagging algorithm
  void tag(float value);

  /// Set the  Reference to the jet
  void jet(fcc::ConstJet value);



  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from TaggedJetObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const TaggedJet& other) const {
    return (m_obj==other.m_obj);
  }

  bool operator==(const ConstTaggedJet& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const TaggedJet& p1,
//       const TaggedJet& p2 );
  bool operator<(const TaggedJet& other) const { return m_obj < other.m_obj  ; }

  const podio::ObjectID getObjectID() const;

private:
  TaggedJetObj* m_obj;

};

} // namespace fcc

#endif
