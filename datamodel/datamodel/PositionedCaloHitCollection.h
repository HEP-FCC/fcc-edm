//AUTOMATICALLY GENERATED - DO NOT EDIT

#ifndef PositionedCaloHitCollection_H
#define  PositionedCaloHitCollection_H

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
#include "PositionedCaloHitData.h"
#include "PositionedCaloHit.h"
#include "PositionedCaloHitObj.h"

namespace fcc {
typedef std::vector<PositionedCaloHitData> PositionedCaloHitDataContainer;
typedef std::deque<PositionedCaloHitObj*> PositionedCaloHitObjPointerContainer;

class PositionedCaloHitCollectionIterator {

  public:
    PositionedCaloHitCollectionIterator(int index, const PositionedCaloHitObjPointerContainer* collection) : m_index(index), m_object(nullptr), m_collection(collection) {}

    bool operator!=(const PositionedCaloHitCollectionIterator& x) const {
      return m_index != x.m_index; //TODO: may not be complete
    }

    const PositionedCaloHit operator*() const;
    const PositionedCaloHit* operator->() const;
    const PositionedCaloHitCollectionIterator& operator++() const;

  private:
    mutable int m_index;
    mutable PositionedCaloHit m_object;
    const PositionedCaloHitObjPointerContainer* m_collection;
};

/**
A Collection is identified by an ID.
*/

class PositionedCaloHitCollection : public podio::CollectionBase {

public:
  typedef const PositionedCaloHitCollectionIterator const_iterator;

  PositionedCaloHitCollection();
//  PositionedCaloHitCollection(const PositionedCaloHitCollection& ) = delete; // deletion doesn't work w/ ROOT IO ! :-(
//  PositionedCaloHitCollection(PositionedCaloHitVector* data, int collectionID);
  ~PositionedCaloHitCollection();

  void clear();
  /// Append a new object to the collection, and return this object.
  PositionedCaloHit create();

  /// Append a new object to the collection, and return this object.
  /// Initialized with the parameters given
  template<typename... Args>
  PositionedCaloHit create(Args&&... args);
  int size() const;

  /// Returns the object of given index
  const PositionedCaloHit operator[](unsigned int index) const;
  /// Returns the object of given index
  const PositionedCaloHit at(unsigned int index) const;


  /// Append object to the collection
  void push_back(ConstPositionedCaloHit object);

  void prepareForWrite();
  void prepareAfterRead();
  void setBuffer(void* address);
  bool setReferences(const podio::ICollectionProvider* collectionProvider);

  podio::CollRefCollection* referenceCollections() { return &m_refCollections;};

  void setID(unsigned ID){
    m_collectionID = ID;
    std::for_each(m_entries.begin(),m_entries.end(),
                 [ID](PositionedCaloHitObj* obj){obj->id = {obj->id.index,static_cast<int>(ID)}; }
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
  std::vector<PositionedCaloHitData>* _getBuffer() { return m_data;};

    template<size_t arraysize>
  const std::array<fcc::Point,arraysize> position() const;
  template<size_t arraysize>
  const std::array<fcc::BareHit,arraysize> core() const;


private:
  bool m_isValid;
  int m_collectionID;
  PositionedCaloHitObjPointerContainer m_entries;
  // members to handle 1-to-N-relations

  // members to handle streaming
  podio::CollRefCollection m_refCollections;
  PositionedCaloHitDataContainer* m_data;
};

template<typename... Args>
PositionedCaloHit  PositionedCaloHitCollection::create(Args&&... args){
  int size = m_entries.size();
  auto obj = new PositionedCaloHitObj({size,m_collectionID},{args...});
  m_entries.push_back(obj);
  return PositionedCaloHit(obj);
}

template<size_t arraysize>
const std::array<class fcc::Point,arraysize> PositionedCaloHitCollection::position() const {
  std::array<class fcc::Point,arraysize> tmp;
  auto valid_size = std::min(arraysize,m_entries.size());
  for (unsigned i = 0; i<valid_size; ++i){
    tmp[i] = m_entries[i]->data.position;
 }
 return tmp;
}
template<size_t arraysize>
const std::array<class fcc::BareHit,arraysize> PositionedCaloHitCollection::core() const {
  std::array<class fcc::BareHit,arraysize> tmp;
  auto valid_size = std::min(arraysize,m_entries.size());
  for (unsigned i = 0; i<valid_size; ++i){
    tmp[i] = m_entries[i]->data.core;
 }
 return tmp;
}

} // namespace fcc
#endif
