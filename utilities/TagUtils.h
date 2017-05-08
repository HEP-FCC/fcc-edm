#ifndef UTILITIES_JET_UTILS
#define UTILITIES_JET_UTILS

#include "podio/CollectionIDTable.h"
#include <stdexcept>

namespace tagutils {

/** Find a tag from collection with id associated to object taggedObject.
  * @param[in] taggedObject - the EDM object whose tag associations are searched
  * @param[in] tagName - name of collection of the tag we are looking for
  * @returns the tag in case of success and nullptr if tag is not associated
  * */
template <class T>
const fcc::ConstTag* tag(const T& taggedObject, int id)  {
  auto it = std::find_if(taggedObject.tags_begin(),
    taggedObject.tags_end(),
    [id](const fcc::ConstTag& lTag) {
      return bool(lTag.getObjectID().collectionID == id);
  });
  if (it == taggedObject.tags_end()) {
    return nullptr;
  }
  return &(*it);
}

class TagUtils {
 public:
  /// Constructor, CollectionIdTable should be taken from podio reader
  explicit TagUtils(const podio::CollectionIDTable& idMap) : m_idTable(idMap) {}
  ~TagUtils() {}

  /** Find a tag from collection tagName associated to object taggedObject.
    * WARNING: Assumes that tagName is a valid collection name, check before first use with
    * CollectionIdTable::present(tagName)!
    * @param[in] taggedObject - the EDM object whose tag associations are searched
    * @param[in] tagName - name of collection of the tag we are looking for
    * @returns the tag in case of success and nullptr if tag is not associated
    * */
  template <class T>
  const fcc::ConstTag* tag(const T& taggedObject, const std::string& tagName) const {
    int id = m_idTable.collectionID(tagName);
    return tagutils::tag(taggedObject, id);
  }

 private:
  /// Reference to the collection registry to associate names with IDs
  const podio::CollectionIDTable& m_idTable;
};
}

#endif
