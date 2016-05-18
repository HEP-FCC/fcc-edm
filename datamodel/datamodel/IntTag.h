#ifndef IntTag_H
#define IntTag_H
#include "IntTagData.h"
#include <vector>
#include "podio/ObjectID.h"

// Integer tag information for studied type
// author: C. Bernet, Z. Drasal, C. Helsens

//forward declarations


#include "IntTagConst.h"
#include "IntTagObj.h"

namespace fcc {

class IntTagCollection;
class IntTagCollectionIterator;
class ConstIntTag;

class IntTag {

  friend IntTagCollection;
  friend IntTagCollectionIterator;
  friend ConstIntTag;

public:

  /// default constructor
  IntTag();
  IntTag(int Value);

  /// constructor from existing IntTagObj
  IntTag(IntTagObj* obj);
  /// copy constructor
  IntTag(const IntTag& other);
  /// copy-assignment operator
  IntTag& operator=(const IntTag& other);
  /// support cloning (deep-copy)
  IntTag clone() const;
  /// destructor
  ~IntTag();

  /// conversion to const object
  operator ConstIntTag () const;

public:

  const int& Value() const;

  void Value(int value);




  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from IntTagObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const IntTag& other) const {
    return (m_obj==other.m_obj);
  }

  bool operator==(const ConstIntTag& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const IntTag& p1,
//       const IntTag& p2 );
  bool operator<(const IntTag& other) const { return m_obj < other.m_obj  ; }

  const podio::ObjectID getObjectID() const;

private:
  IntTagObj* m_obj;

};

} // namespace fcc

#endif
