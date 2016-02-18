//AUTOMATICALLY GENERATED - DO NOT EDIT

#ifndef TrackStateCollection_H
#define  TrackStateCollection_H

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
#include "TrackStateData.h"
#include "TrackState.h"
#include "TrackStateObj.h"

namespace fcc {
typedef std::vector<TrackStateData> TrackStateDataContainer;
typedef std::deque<TrackStateObj*> TrackStateObjPointerContainer;

class TrackStateCollectionIterator {

  public:
    TrackStateCollectionIterator(int index, const TrackStateObjPointerContainer* collection) : m_index(index), m_object(nullptr), m_collection(collection) {}

    bool operator!=(const TrackStateCollectionIterator& x) const {
      return m_index != x.m_index; //TODO: may not be complete
    }

    const TrackState operator*() const;
    const TrackState* operator->() const;
    const TrackStateCollectionIterator& operator++() const;

  private:
    mutable int m_index;
    mutable TrackState m_object;
    const TrackStateObjPointerContainer* m_collection;
};

/**
A Collection is identified by an ID.
*/

class TrackStateCollection : public podio::CollectionBase {

public:
  typedef const TrackStateCollectionIterator const_iterator;

  TrackStateCollection();
//  TrackStateCollection(const TrackStateCollection& ) = delete; // deletion doesn't work w/ ROOT IO ! :-(
//  TrackStateCollection(TrackStateVector* data, int collectionID);
  ~TrackStateCollection(){};

  void clear();
  /// Append a new object to the collection, and return this object.
  TrackState create();

  /// Append a new object to the collection, and return this object.
  /// Initialized with the parameters given
  template<typename... Args>
  TrackState create(Args&&... args);
  int size() const;

  /// Returns the object of given index
  const TrackState operator[](unsigned int index) const;
  /// Returns the object of given index
  const TrackState at(unsigned int index) const;


  /// Append object to the collection
  void push_back(ConstTrackState object);

  void prepareForWrite();
  void prepareAfterRead();
  void setBuffer(void* address);
  bool setReferences(const podio::ICollectionProvider* collectionProvider);

  podio::CollRefCollection* referenceCollections() { return m_refCollections;};

  void setID(unsigned ID){
    m_collectionID = ID;
    std::for_each(m_entries.begin(),m_entries.end(),
                 [ID](TrackStateObj* obj){obj->id = {obj->id.index,static_cast<int>(ID)}; }
    );
  };

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
  std::vector<TrackStateData>* _getBuffer() { return m_data;};

     template<size_t arraysize>  
  const std::array<float,arraysize> Location() const;
  template<size_t arraysize>  
  const std::array<float,arraysize> Omega() const;
  template<size_t arraysize>  
  const std::array<float,arraysize> D0() const;
  template<size_t arraysize>  
  const std::array<float,arraysize> Z0() const;


private:
  int m_collectionID;
  TrackStateObjPointerContainer m_entries;
  // members to handle 1-to-N-relations

  // members to handle streaming
  podio::CollRefCollection* m_refCollections;
  TrackStateDataContainer* m_data;
};

template<typename... Args>
TrackState  TrackStateCollection::create(Args&&... args){
  int size = m_entries.size();
  auto obj = new TrackStateObj({size,m_collectionID},{args...});
  m_entries.push_back(obj);
  return TrackState(obj);
}

template<size_t arraysize>
const std::array<float,arraysize> TrackStateCollection::Location() const {
  std::array<float,arraysize> tmp;
  auto valid_size = std::min(arraysize,m_entries.size());
  for (unsigned i = 0; i<valid_size; ++i){
    tmp[i] = m_entries[i]->data.Location;
 }
 return tmp;
}
template<size_t arraysize>
const std::array<float,arraysize> TrackStateCollection::Omega() const {
  std::array<float,arraysize> tmp;
  auto valid_size = std::min(arraysize,m_entries.size());
  for (unsigned i = 0; i<valid_size; ++i){
    tmp[i] = m_entries[i]->data.Omega;
 }
 return tmp;
}
template<size_t arraysize>
const std::array<float,arraysize> TrackStateCollection::D0() const {
  std::array<float,arraysize> tmp;
  auto valid_size = std::min(arraysize,m_entries.size());
  for (unsigned i = 0; i<valid_size; ++i){
    tmp[i] = m_entries[i]->data.D0;
 }
 return tmp;
}
template<size_t arraysize>
const std::array<float,arraysize> TrackStateCollection::Z0() const {
  std::array<float,arraysize> tmp;
  auto valid_size = std::min(arraysize,m_entries.size());
  for (unsigned i = 0; i<valid_size; ++i){
    tmp[i] = m_entries[i]->data.Z0;
 }
 return tmp;
}

} // namespace fcc
#endif
