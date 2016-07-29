#ifndef TaggedGenJet_H
#define TaggedGenJet_H
#include "TaggedGenJetData.h"
#include <vector>
#include "podio/ObjectID.h"

//forward declarations
namespace fcc {
class GenJet;
class ConstGenJet;
}


#include "TaggedGenJetConst.h"
#include "TaggedGenJetObj.h"

namespace fcc {

class TaggedGenJetCollection;
class TaggedGenJetCollectionIterator;
class ConstTaggedGenJet;

/** @class TaggedGenJet
 *  Association between a GenJet and arbitrary Tag information
 *  @author: C. Bernet, Z. Drasal
 */
class TaggedGenJet {

  friend TaggedGenJetCollection;
  friend TaggedGenJetCollectionIterator;
  friend ConstTaggedGenJet;

public:

  /// default constructor
  TaggedGenJet();
  TaggedGenJet(float tag);

  /// constructor from existing TaggedGenJetObj
  TaggedGenJet(TaggedGenJetObj* obj);
  /// copy constructor
  TaggedGenJet(const TaggedGenJet& other);
  /// copy-assignment operator
  TaggedGenJet& operator=(const TaggedGenJet& other);
  /// support cloning (deep-copy)
  TaggedGenJet clone() const;
  /// destructor
  ~TaggedGenJet();

  /// conversion to const object
  operator ConstTaggedGenJet () const;

public:

  /// Access the  Result of the tagging algorithm
  const float& tag() const;
  /// Access the  Reference to the gen jet
  const fcc::ConstGenJet jet() const;

  /// Set the  Result of the tagging algorithm
  void tag(float value);

  /// Set the  Reference to the gen jet
  void jet(fcc::ConstGenJet value);



  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from TaggedGenJetObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const TaggedGenJet& other) const {
    return (m_obj==other.m_obj);
  }

  bool operator==(const ConstTaggedGenJet& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const TaggedGenJet& p1,
//       const TaggedGenJet& p2 );
  bool operator<(const TaggedGenJet& other) const { return m_obj < other.m_obj  ; }

  const podio::ObjectID getObjectID() const;

private:
  TaggedGenJetObj* m_obj;

};

} // namespace fcc

#endif
