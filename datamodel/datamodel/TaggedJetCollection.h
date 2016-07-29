//AUTOMATICALLY GENERATED - DO NOT EDIT

#ifndef TaggedJetCollection_H
#define  TaggedJetCollection_H

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
#include "TaggedJetData.h"
#include "TaggedJet.h"
#include "TaggedJetObj.h"

namespace fcc {
typedef std::vector<TaggedJetData> TaggedJetDataContainer;
typedef std::deque<TaggedJetObj*> TaggedJetObjPointerContainer;

class TaggedJetCollectionIterator {

  public:
    TaggedJetCollectionIterator(int index, const TaggedJetObjPointerContainer* collection) : m_index(index), m_object(nullptr), m_collection(collection) {}

    bool operator!=(const TaggedJetCollectionIterator& x) const {
      return m_index != x.m_index; //TODO: may not be complete
    }

    const TaggedJet operator*() const;
    const TaggedJet* operator->() const;
    const TaggedJetCollectionIterator& operator++() const;

  private:
    mutable int m_index;
    mutable TaggedJet m_object;
    const TaggedJetObjPointerContainer* m_collection;
};

/**
A Collection is identified by an ID.
*/

class TaggedJetCollection : public podio::CollectionBase {

public:
  typedef const TaggedJetCollectionIterator const_iterator;

  TaggedJetCollection();
//  TaggedJetCollection(const TaggedJetCollection& ) = delete; // deletion doesn't work w/ ROOT IO ! :-(
//  TaggedJetCollection(TaggedJetVector* data, int collectionID);
  ~TaggedJetCollection();

  void clear();
  /// Append a new object to the collection, and return this object.
  TaggedJet create();

  /// Append a new object to the collection, and return this object.
  /// Initialized with the parameters given
  template<typename... Args>
  TaggedJet create(Args&&... args);
  int size() const;

  /// Returns the object of given index
  const TaggedJet operator[](unsigned int index) const;
  /// Returns the object of given index
  const TaggedJet at(unsigned int index) const;


  /// Append object to the collection
  void push_back(ConstTaggedJet object);

  void prepareForWrite();
  void prepareAfterRead();
  void setBuffer(void* address);
  bool setReferences(const podio::ICollectionProvider* collectionProvider);

  podio::CollRefCollection* referenceCollections() { return &m_refCollections;};

  void setID(unsigned ID){
    m_collectionID = ID;
    std::for_each(m_entries.begin(),m_entries.end(),
                 [ID](TaggedJetObj* obj){obj->id = {obj->id.index,static_cast<int>(ID)}; }
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
  std::vector<TaggedJetData>* _getBuffer() { return m_data;};

    template<size_t arraysize>
  const std::array<float,arraysize> tag() const;


private:
  bool m_isValid;
  int m_collectionID;
  TaggedJetObjPointerContainer m_entries;
  // members to handle 1-to-N-relations
  std::vector<fcc::ConstJet>* m_rel_jet; ///< Relation buffer for read / write

  // members to handle streaming
  podio::CollRefCollection m_refCollections;
  TaggedJetDataContainer* m_data;
};

template<typename... Args>
TaggedJet  TaggedJetCollection::create(Args&&... args){
  int size = m_entries.size();
  auto obj = new TaggedJetObj({size,m_collectionID},{args...});
  m_entries.push_back(obj);
  return TaggedJet(obj);
}

template<size_t arraysize>
const std::array<float,arraysize> TaggedJetCollection::tag() const {
  std::array<float,arraysize> tmp;
  auto valid_size = std::min(arraysize,m_entries.size());
  for (unsigned i = 0; i<valid_size; ++i){
    tmp[i] = m_entries[i]->data.tag;
 }
 return tmp;
}

} // namespace fcc
#endif
