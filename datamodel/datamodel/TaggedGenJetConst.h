#ifndef ConstTaggedGenJet_H
#define ConstTaggedGenJet_H
#include "TaggedGenJetData.h"
#include <vector>
#include "podio/ObjectID.h"

//forward declarations
namespace fcc {
class GenJet;
class ConstGenJet;
}


#include "TaggedGenJetObj.h"

namespace fcc {

class TaggedGenJetObj;
class TaggedGenJet;
class TaggedGenJetCollection;
class TaggedGenJetCollectionIterator;

/** @class ConstTaggedGenJet
 *  Association between a GenJet and arbitrary Tag information
 *  @author: C. Bernet, Z. Drasal
 */

class ConstTaggedGenJet {

  friend TaggedGenJet;
  friend TaggedGenJetCollection;
  friend TaggedGenJetCollectionIterator;

public:

  /// default constructor
  ConstTaggedGenJet();
  ConstTaggedGenJet(float tag);

  /// constructor from existing TaggedGenJetObj
  ConstTaggedGenJet(TaggedGenJetObj* obj);
  /// copy constructor
  ConstTaggedGenJet(const ConstTaggedGenJet& other);
  /// copy-assignment operator
  ConstTaggedGenJet& operator=(const ConstTaggedGenJet& other);
  /// support cloning (deep-copy)
  ConstTaggedGenJet clone() const;
  /// destructor
  ~ConstTaggedGenJet();


public:

  /// Access the  Result of the tagging algorithm
  const float& tag() const;
  /// Access the  Reference to the gen jet
  const fcc::ConstGenJet jet() const;



  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from TaggedGenJetObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const ConstTaggedGenJet& other) const {
       return (m_obj==other.m_obj);
  }

  bool operator==(const TaggedGenJet& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const TaggedGenJet& p1,
//       const TaggedGenJet& p2 );
  bool operator<(const ConstTaggedGenJet& other) const { return m_obj < other.m_obj  ; }

  const podio::ObjectID getObjectID() const;

private:
  TaggedGenJetObj* m_obj;

};
} // namespace fcc

#endif
