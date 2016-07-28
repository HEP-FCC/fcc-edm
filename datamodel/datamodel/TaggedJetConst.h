#ifndef ConstTaggedJet_H
#define ConstTaggedJet_H
#include "TaggedJetData.h"
#include <vector>
#include "podio/ObjectID.h"

//forward declarations
namespace fcc {
class Jet;
class ConstJet;
}


#include "TaggedJetObj.h"

namespace fcc {

class TaggedJetObj;
class TaggedJet;
class TaggedJetCollection;
class TaggedJetCollectionIterator;

/** @class ConstTaggedJet
 *  Association between a Jet and arbitrary Tag information
 *  @author: C. Bernet, Z. Drasal, J. Lingemann
 */

class ConstTaggedJet {

  friend TaggedJet;
  friend TaggedJetCollection;
  friend TaggedJetCollectionIterator;

public:

  /// default constructor
  ConstTaggedJet();
  ConstTaggedJet(float tag);

  /// constructor from existing TaggedJetObj
  ConstTaggedJet(TaggedJetObj* obj);
  /// copy constructor
  ConstTaggedJet(const ConstTaggedJet& other);
  /// copy-assignment operator
  ConstTaggedJet& operator=(const ConstTaggedJet& other);
  /// support cloning (deep-copy)
  ConstTaggedJet clone() const;
  /// destructor
  ~ConstTaggedJet();


public:

  /// Access the  Result of the tagging algorithm
  const float& tag() const;
  /// Access the  Reference to the jet
  const fcc::ConstJet jet() const;



  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from TaggedJetObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const ConstTaggedJet& other) const {
       return (m_obj==other.m_obj);
  }

  bool operator==(const TaggedJet& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const TaggedJet& p1,
//       const TaggedJet& p2 );
  bool operator<(const ConstTaggedJet& other) const { return m_obj < other.m_obj  ; }

  const podio::ObjectID getObjectID() const;

private:
  TaggedJetObj* m_obj;

};
} // namespace fcc

#endif
