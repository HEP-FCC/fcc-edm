#ifndef TagOBJ_H
#define TagOBJ_H

// std includes
#include <atomic>
#include <iostream>

// data model specific includes
#include "podio/ObjBase.h"
#include "TagData.h"



// forward declarations
class Tag;
class ConstTag;


namespace fcc {
class TagObj : public podio::ObjBase {
public:
  /// constructor
  TagObj();
  /// copy constructor (does a deep-copy of relation containers)
  TagObj(const TagObj&);
  /// constructor from ObjectID and TagData
  /// does not initialize the internal relation containers
  TagObj(const podio::ObjectID id, TagData data);
  virtual ~TagObj();

public:
  TagData data;


};
} // namespace fcc


#endif
