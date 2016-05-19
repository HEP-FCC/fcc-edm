#ifndef Tag_H
#define Tag_H
#include "TagData.h"
#include <vector>
#include "podio/ObjectID.h"

// Float tag information for studied type
// author: C. Bernet, Z. Drasal

//forward declarations


#include "TagConst.h"
#include "TagObj.h"

namespace fcc {

class TagCollection;
class TagCollectionIterator;
class ConstTag;

class Tag {

  friend TagCollection;
  friend TagCollectionIterator;
  friend ConstTag;

public:

  /// default constructor
  Tag();
  Tag(float Value);

  /// constructor from existing TagObj
  Tag(TagObj* obj);
  /// copy constructor
  Tag(const Tag& other);
  /// copy-assignment operator
  Tag& operator=(const Tag& other);
  /// support cloning (deep-copy)
  Tag clone() const;
  /// destructor
  ~Tag();

  /// conversion to const object
  operator ConstTag () const;

public:

  const float& Value() const;

  void Value(float value);




  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from TagObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const Tag& other) const {
    return (m_obj==other.m_obj);
  }

  bool operator==(const ConstTag& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const Tag& p1,
//       const Tag& p2 );
  bool operator<(const Tag& other) const { return m_obj < other.m_obj  ; }

  const podio::ObjectID getObjectID() const;

private:
  TagObj* m_obj;

};

} // namespace fcc

#endif
