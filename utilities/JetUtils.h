#ifndef UTILITIES_JET_UTILS
#define UTILITIES_JET_UTILS

#include "podio/CollectionIDTable.h"

namespace jetutils {

class JetUtils {
 public:
  JetUtils(const podio::CollectionIDTable& idMap) : m_idMap(idMap) {}
  ~JetUtils() {}

  template <class T>
  fcc::ConstTag tag(const T& taggedObject, const std::string& tagName) const {
      int id = m_idMap.collectionID(tagName);
      auto it = std::find_if(taggedObject.tags_begin(),
        taggedObject.tags_end(),
        [id](const fcc::ConstTag& tag) {
          return bool(tag.getObjectID().collectionID == id);
        });
      return *it;
  }

 private:
  const podio::CollectionIDTable& m_idMap;
};
}

#endif