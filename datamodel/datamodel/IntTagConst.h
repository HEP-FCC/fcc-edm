#ifndef ConstIntTag_H
#define ConstIntTag_H
#include "IntTagData.h"
#include <vector>
#include "podio/ObjectID.h"

// Integer tag information for studied type
// author: C. Bernet, Z. Drasal, C. Helsens

//forward declarations


#include "IntTagObj.h"

namespace fcc {

class IntTagObj;
class IntTag;
class IntTagCollection;
class IntTagCollectionIterator;

class ConstIntTag {

  friend IntTag;
  friend IntTagCollection;
  friend IntTagCollectionIterator;

public:

  /// default constructor
  ConstIntTag();
  ConstIntTag(int Value);

  /// constructor from existing IntTagObj
  ConstIntTag(IntTagObj* obj);
  /// copy constructor
  ConstIntTag(const ConstIntTag& other);
  /// copy-assignment operator
  ConstIntTag& operator=(const ConstIntTag& other);
  /// support cloning (deep-copy)
  ConstIntTag clone() const;
  /// destructor
  ~ConstIntTag();


public:

  const int& Value() const;



  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from IntTagObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const ConstIntTag& other) const {
       return (m_obj==other.m_obj);
  }

  bool operator==(const IntTag& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const IntTag& p1,
//       const IntTag& p2 );

  const podio::ObjectID getObjectID() const;

private:
  IntTagObj* m_obj;

};
} // namespace fcc

#endif
