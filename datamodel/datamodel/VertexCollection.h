//AUTOMATICALLY GENERATED - DO NOT EDIT

#ifndef VertexCollection_H
#define  VertexCollection_H

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
#include "VertexData.h"
#include "Vertex.h"
#include "VertexObj.h"

namespace fcc {
typedef std::vector<VertexData> VertexDataContainer;
typedef std::deque<VertexObj*> VertexObjPointerContainer;

class VertexCollectionIterator {

  public:
    VertexCollectionIterator(int index, const VertexObjPointerContainer* collection) : m_index(index), m_object(nullptr), m_collection(collection) {}

    bool operator!=(const VertexCollectionIterator& x) const {
      return m_index != x.m_index; //TODO: may not be complete
    }

    const Vertex operator*() const;
    const Vertex* operator->() const;
    const VertexCollectionIterator& operator++() const;

  private:
    mutable int m_index;
    mutable Vertex m_object;
    const VertexObjPointerContainer* m_collection;
};

/**
A Collection is identified by an ID.
*/

class VertexCollection : public podio::CollectionBase {

public:
  typedef const VertexCollectionIterator const_iterator;

  VertexCollection();
//  VertexCollection(const VertexCollection& ) = delete; // deletion doesn't work w/ ROOT IO ! :-(
//  VertexCollection(VertexVector* data, int collectionID);
  ~VertexCollection();

  void clear();
  /// Append a new object to the collection, and return this object.
  Vertex create();

  /// Append a new object to the collection, and return this object.
  /// Initialized with the parameters given
  template<typename... Args>
  Vertex create(Args&&... args);
  int size() const;

  /// Returns the object of given index
  const Vertex operator[](unsigned int index) const;
  /// Returns the object of given index
  const Vertex at(unsigned int index) const;


  /// Append object to the collection
  void push_back(ConstVertex object);

  void prepareForWrite();
  void prepareAfterRead();
  void setBuffer(void* address);
  bool setReferences(const podio::ICollectionProvider* collectionProvider);

  podio::CollRefCollection* referenceCollections() { return &m_refCollections;};

  void setID(unsigned ID){
    m_collectionID = ID;
    std::for_each(m_entries.begin(),m_entries.end(),
                 [ID](VertexObj* obj){obj->id = {obj->id.index,static_cast<int>(ID)}; }
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
  std::vector<VertexData>* _getBuffer() { return m_data;};

    template<size_t arraysize>
  const std::array<float,arraysize> chi2() const;
  template<size_t arraysize>
  const std::array<unsigned,arraysize> ndf() const;
  template<size_t arraysize>
  const std::array<fcc::Point,arraysize> position() const;
  template<size_t arraysize>
  const std::array<unsigned,arraysize> bits() const;


private:
  bool m_isValid;
  int m_collectionID;
  VertexObjPointerContainer m_entries;
  // members to handle 1-to-N-relations
  std::vector<fcc::ConstWeightedTrack>* m_rel_tracks; ///< Relation buffer for read / write
  std::vector<std::vector<fcc::ConstWeightedTrack>*> m_rel_tracks_tmp; ///< Relation buffer for internal book-keeping

  // members to handle streaming
  podio::CollRefCollection m_refCollections;
  VertexDataContainer* m_data;
};

template<typename... Args>
Vertex  VertexCollection::create(Args&&... args){
  int size = m_entries.size();
  auto obj = new VertexObj({size,m_collectionID},{args...});
  m_entries.push_back(obj);
  return Vertex(obj);
}

template<size_t arraysize>
const std::array<float,arraysize> VertexCollection::chi2() const {
  std::array<float,arraysize> tmp;
  auto valid_size = std::min(arraysize,m_entries.size());
  for (unsigned i = 0; i<valid_size; ++i){
    tmp[i] = m_entries[i]->data.chi2;
 }
 return tmp;
}
template<size_t arraysize>
const std::array<unsigned,arraysize> VertexCollection::ndf() const {
  std::array<unsigned,arraysize> tmp;
  auto valid_size = std::min(arraysize,m_entries.size());
  for (unsigned i = 0; i<valid_size; ++i){
    tmp[i] = m_entries[i]->data.ndf;
 }
 return tmp;
}
template<size_t arraysize>
const std::array<class fcc::Point,arraysize> VertexCollection::position() const {
  std::array<class fcc::Point,arraysize> tmp;
  auto valid_size = std::min(arraysize,m_entries.size());
  for (unsigned i = 0; i<valid_size; ++i){
    tmp[i] = m_entries[i]->data.position;
 }
 return tmp;
}
template<size_t arraysize>
const std::array<unsigned,arraysize> VertexCollection::bits() const {
  std::array<unsigned,arraysize> tmp;
  auto valid_size = std::min(arraysize,m_entries.size());
  for (unsigned i = 0; i<valid_size; ++i){
    tmp[i] = m_entries[i]->data.bits;
 }
 return tmp;
}

} // namespace fcc
#endif
