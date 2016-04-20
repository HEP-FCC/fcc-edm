#ifndef ConstTag_H
#define ConstTag_H
#include "TagData.h"
#include <vector>
#include "podio/ObjectID.h"

// Float tag information for studied type
// author: C. Bernet, Z. Drasal

//forward declarations


#include "TagObj.h"

namespace fcc {

class TagObj;
class Tag;
class TagCollection;
class TagCollectionIterator;

class ConstTag {

  friend Tag;
  friend TagCollection;
  friend TagCollectionIterator;

public:

  /// default constructor
  ConstTag();
  ConstTag(float Value);

  /// constructor from existing TagObj
  ConstTag(TagObj* obj);
  /// copy constructor
  ConstTag(const ConstTag& other);
  /// copy-assignment operator
  ConstTag& operator=(const ConstTag& other);
  /// support cloning (deep-copy)
  ConstTag clone() const;
  /// destructor
  ~ConstTag();


public:

  const float& Value() const;



  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from TagObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const ConstTag& other) const {
       return (m_obj==other.m_obj);
  }

  bool operator==(const Tag& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const Tag& p1,
//       const Tag& p2 );

  const podio::ObjectID getObjectID() const;

private:
  TagObj* m_obj;

};
} // namespace fcc

#endif
