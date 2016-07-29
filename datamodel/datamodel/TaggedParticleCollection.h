//AUTOMATICALLY GENERATED - DO NOT EDIT

#ifndef TaggedParticleCollection_H
#define  TaggedParticleCollection_H

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
#include "TaggedParticleData.h"
#include "TaggedParticle.h"
#include "TaggedParticleObj.h"

namespace fcc {
typedef std::vector<TaggedParticleData> TaggedParticleDataContainer;
typedef std::deque<TaggedParticleObj*> TaggedParticleObjPointerContainer;

class TaggedParticleCollectionIterator {

  public:
    TaggedParticleCollectionIterator(int index, const TaggedParticleObjPointerContainer* collection) : m_index(index), m_object(nullptr), m_collection(collection) {}

    bool operator!=(const TaggedParticleCollectionIterator& x) const {
      return m_index != x.m_index; //TODO: may not be complete
    }

    const TaggedParticle operator*() const;
    const TaggedParticle* operator->() const;
    const TaggedParticleCollectionIterator& operator++() const;

  private:
    mutable int m_index;
    mutable TaggedParticle m_object;
    const TaggedParticleObjPointerContainer* m_collection;
};

/**
A Collection is identified by an ID.
*/

class TaggedParticleCollection : public podio::CollectionBase {

public:
  typedef const TaggedParticleCollectionIterator const_iterator;

  TaggedParticleCollection();
//  TaggedParticleCollection(const TaggedParticleCollection& ) = delete; // deletion doesn't work w/ ROOT IO ! :-(
//  TaggedParticleCollection(TaggedParticleVector* data, int collectionID);
  ~TaggedParticleCollection();

  void clear();
  /// Append a new object to the collection, and return this object.
  TaggedParticle create();

  /// Append a new object to the collection, and return this object.
  /// Initialized with the parameters given
  template<typename... Args>
  TaggedParticle create(Args&&... args);
  int size() const;

  /// Returns the object of given index
  const TaggedParticle operator[](unsigned int index) const;
  /// Returns the object of given index
  const TaggedParticle at(unsigned int index) const;


  /// Append object to the collection
  void push_back(ConstTaggedParticle object);

  void prepareForWrite();
  void prepareAfterRead();
  void setBuffer(void* address);
  bool setReferences(const podio::ICollectionProvider* collectionProvider);

  podio::CollRefCollection* referenceCollections() { return &m_refCollections;};

  void setID(unsigned ID){
    m_collectionID = ID;
    std::for_each(m_entries.begin(),m_entries.end(),
                 [ID](TaggedParticleObj* obj){obj->id = {obj->id.index,static_cast<int>(ID)}; }
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
  std::vector<TaggedParticleData>* _getBuffer() { return m_data;};

    template<size_t arraysize>
  const std::array<float,arraysize> value() const;


private:
  bool m_isValid;
  int m_collectionID;
  TaggedParticleObjPointerContainer m_entries;
  // members to handle 1-to-N-relations
  std::vector<fcc::ConstParticle>* m_rel_particle; ///< Relation buffer for read / write

  // members to handle streaming
  podio::CollRefCollection m_refCollections;
  TaggedParticleDataContainer* m_data;
};

template<typename... Args>
TaggedParticle  TaggedParticleCollection::create(Args&&... args){
  int size = m_entries.size();
  auto obj = new TaggedParticleObj({size,m_collectionID},{args...});
  m_entries.push_back(obj);
  return TaggedParticle(obj);
}

template<size_t arraysize>
const std::array<float,arraysize> TaggedParticleCollection::value() const {
  std::array<float,arraysize> tmp;
  auto valid_size = std::min(arraysize,m_entries.size());
  for (unsigned i = 0; i<valid_size; ++i){
    tmp[i] = m_entries[i]->data.value;
 }
 return tmp;
}

} // namespace fcc
#endif
