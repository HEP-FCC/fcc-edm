//AUTOMATICALLY GENERATED - DO NOT EDIT

#ifndef TagCollection_H
#define  TagCollection_H

#include <string>
#include <vector>
#include <deque>
#include <array>

// podio specific includes
#include "podio/ICollectionProvider.h"
#include "podio/CollectionBase.h"
#include "podio/CollectionIDTable.h"

// datamodel specific includes
#include "TagData.h"
#include "Tag.h"
#include "TagObj.h"

namespace fcc {
typedef std::vector<TagData> TagDataContainer;
typedef std::deque<TagObj*> TagObjPointerContainer;

class TagCollectionIterator {

  public:
    TagCollectionIterator(int index, const TagObjPointerContainer* collection) : m_index(index), m_object(nullptr), m_collection(collection) {}

    bool operator!=(const TagCollectionIterator& x) const {
      return m_index != x.m_index; //TODO: may not be complete
    }

    const Tag operator*() const;
    const Tag* operator->() const;
    const TagCollectionIterator& operator++() const;

  private:
    mutable int m_index;
    mutable Tag m_object;
    const TagObjPointerContainer* m_collection;
};

/**
A Collection is identified by an ID.
*/

class TagCollection : public podio::CollectionBase {

public:
  typedef const TagCollectionIterator const_iterator;

  TagCollection();
//  TagCollection(const TagCollection& ) = delete; // deletion doesn't work w/ ROOT IO ! :-(
//  TagCollection(TagVector* data, int collectionID);
  ~TagCollection(){};

  void clear();
  /// Append a new object to the collection, and return this object.
  Tag create();

  /// Append a new object to the collection, and return this object.
  /// Initialized with the parameters given
  template<typename... Args>
  Tag create(Args&&... args);
  int size() const;

  /// Returns the object of given index
  const Tag operator[](unsigned int index) const;
  /// Returns the object of given index
  const Tag at(unsigned int index) const;


  /// Append object to the collection
  void push_back(ConstTag object);

  void prepareForWrite();
  void prepareAfterRead();
  void setBuffer(void* address);
  bool setReferences(const podio::ICollectionProvider* collectionProvider);

  podio::CollRefCollection* referenceCollections() { return m_refCollections;};

  void setID(unsigned ID){m_collectionID = ID;};

  // support for the iterator protocol
  const const_iterator begin() const {
    return const_iterator(0, &m_entries);
  }
  const	const_iterator end() const {
    return const_iterator(m_entries.size(), &m_entries);
  }

  /// returns the address of the pointer to the data buffer
  void* getBufferAddress() { return (void*)&m_data;};

  /// returns the pointer to the data buffer
  std::vector<TagData>* _getBuffer() { return m_data;};

     template<size_t arraysize>  
  const std::array<float,arraysize> Value() const;


private:
  int m_collectionID;
  TagObjPointerContainer m_entries;
  // members to handle 1-to-N-relations

  // members to handle streaming
  podio::CollRefCollection* m_refCollections;
  TagDataContainer* m_data;
};

template<typename... Args>
Tag  TagCollection::create(Args&&... args){
  int size = m_entries.size();
  auto obj = new TagObj({size,m_collectionID},{args...});
  m_entries.push_back(obj);
  return Tag(obj);
}

template<size_t arraysize>
const std::array<float,arraysize> TagCollection::Value() const {
  std::array<float,arraysize> tmp;
  auto valid_size = std::min(arraysize,m_entries.size());
  for (unsigned i = 0; i<valid_size; ++i){
    tmp[i] = m_entries[i]->data.Value;
 }
 return tmp;
}

} // namespace fcc
#endif
