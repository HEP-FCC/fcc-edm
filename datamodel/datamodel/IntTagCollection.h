//AUTOMATICALLY GENERATED - DO NOT EDIT

#ifndef IntTagCollection_H
#define  IntTagCollection_H

#include <string>
#include <vector>
#include <deque>
#include <array>
#include <algorithm>

// podio specific includes
#include "podio/ICollectionProvider.h"
#include "podio/CollectionBase.h"
#include "podio/CollectionIDTable.h"

// datamodel specific includes
#include "IntTagData.h"
#include "IntTag.h"
#include "IntTagObj.h"

namespace fcc {
typedef std::vector<IntTagData> IntTagDataContainer;
typedef std::deque<IntTagObj*> IntTagObjPointerContainer;

class IntTagCollectionIterator {

  public:
    IntTagCollectionIterator(int index, const IntTagObjPointerContainer* collection) : m_index(index), m_object(nullptr), m_collection(collection) {}

    bool operator!=(const IntTagCollectionIterator& x) const {
      return m_index != x.m_index; //TODO: may not be complete
    }

    const IntTag operator*() const;
    const IntTag* operator->() const;
    const IntTagCollectionIterator& operator++() const;

  private:
    mutable int m_index;
    mutable IntTag m_object;
    const IntTagObjPointerContainer* m_collection;
};

/**
A Collection is identified by an ID.
*/

class IntTagCollection : public podio::CollectionBase {

public:
  typedef const IntTagCollectionIterator const_iterator;

  IntTagCollection();
//  IntTagCollection(const IntTagCollection& ) = delete; // deletion doesn't work w/ ROOT IO ! :-(
//  IntTagCollection(IntTagVector* data, int collectionID);
  ~IntTagCollection();

  void clear();
  /// Append a new object to the collection, and return this object.
  IntTag create();

  /// Append a new object to the collection, and return this object.
  /// Initialized with the parameters given
  template<typename... Args>
  IntTag create(Args&&... args);
  int size() const;

  /// Returns the object of given index
  const IntTag operator[](unsigned int index) const;
  /// Returns the object of given index
  const IntTag at(unsigned int index) const;


  /// Append object to the collection
  void push_back(ConstIntTag object);

  void prepareForWrite();
  void prepareAfterRead();
  void setBuffer(void* address);
  bool setReferences(const podio::ICollectionProvider* collectionProvider);

  podio::CollRefCollection* referenceCollections() { return &m_refCollections;};

  void setID(unsigned ID){
    m_collectionID = ID;
    std::for_each(m_entries.begin(),m_entries.end(),
                 [ID](IntTagObj* obj){obj->id = {obj->id.index,static_cast<int>(ID)}; }
    );
  };

  bool isValid() const {
    return m_isValid;
  }

  // support for the iterator protocol
  const const_iterator begin() const {
    return const_iterator(0, &m_entries);
  }
  const const_iterator end() const {
    return const_iterator(m_entries.size(), &m_entries);
  }

  /// returns the address of the pointer to the data buffer
  void* getBufferAddress() { return (void*)&m_data;};

  /// returns the pointer to the data buffer
  std::vector<IntTagData>* _getBuffer() { return m_data;};

    template<size_t arraysize>
  const std::array<int,arraysize> Value() const;


private:
  bool m_isValid;
  int m_collectionID;
  IntTagObjPointerContainer m_entries;
  // members to handle 1-to-N-relations

  // members to handle streaming
  podio::CollRefCollection m_refCollections;
  IntTagDataContainer* m_data;
};

template<typename... Args>
IntTag  IntTagCollection::create(Args&&... args){
  int size = m_entries.size();
  auto obj = new IntTagObj({size,m_collectionID},{args...});
  m_entries.push_back(obj);
  return IntTag(obj);
}

template<size_t arraysize>
const std::array<int,arraysize> IntTagCollection::Value() const {
  std::array<int,arraysize> tmp;
  auto valid_size = std::min(arraysize,m_entries.size());
  for (unsigned i = 0; i<valid_size; ++i){
    tmp[i] = m_entries[i]->data.Value;
 }
 return tmp;
}

} // namespace fcc
#endif
