//AUTOMATICALLY GENERATED - DO NOT EDIT

#ifndef TrackHitCollection_H
#define  TrackHitCollection_H

#include <string>
#include <vector>
#include <deque>
#include <array>

// podio specific includes
#include "podio/ICollectionProvider.h"
#include "podio/CollectionBase.h"
#include "podio/CollectionIDTable.h"

// datamodel specific includes
#include "TrackHitData.h"
#include "TrackHit.h"
#include "TrackHitObj.h"


typedef std::vector<TrackHitData> TrackHitDataContainer;
typedef std::deque<TrackHitObj*> TrackHitObjPointerContainer;

class TrackHitCollectionIterator {

  public:
    TrackHitCollectionIterator(int index, const TrackHitObjPointerContainer* collection) : m_index(index), m_object(nullptr), m_collection(collection) {}

    bool operator!=(const TrackHitCollectionIterator& x) const {
      return m_index != x.m_index; //TODO: may not be complete
    }

    const TrackHit operator*() const;
    const TrackHit* operator->() const;
    const TrackHitCollectionIterator& operator++() const;

  private:
    mutable int m_index;
    mutable TrackHit m_object;
    const TrackHitObjPointerContainer* m_collection;
};

/**
A Collection is identified by an ID.
*/

class TrackHitCollection : public podio::CollectionBase {

public:
  typedef const TrackHitCollectionIterator const_iterator;

  TrackHitCollection();
//  TrackHitCollection(const TrackHitCollection& ) = delete; // deletion doesn't work w/ ROOT IO ! :-(
//  TrackHitCollection(TrackHitVector* data, int collectionID);
  ~TrackHitCollection(){};

  void clear();
  /// Append a new object to the collection, and return this object.
  TrackHit create();

  /// Append a new object to the collection, and return this object.
  /// Initialized with the parameters given
  template<typename... Args>
  TrackHit create(Args&&... args);
  int size() const;

  /// Returns the object of given index
  const TrackHit operator[](unsigned int index) const;
  /// Returns the object of given index
  const TrackHit at(unsigned int index) const;


  /// Append object to the collection
  void push_back(ConstTrackHit object);

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
  std::vector<TrackHitData>* _getBuffer() { return m_data;};

     template<size_t arraysize>  
  const std::array<BareHit,arraysize> Core() const;


private:
  int m_collectionID;
  TrackHitObjPointerContainer m_entries;
  // members to handle 1-to-N-relations

  // members to handle streaming
  podio::CollRefCollection* m_refCollections;
  TrackHitDataContainer* m_data;
};

template<typename... Args>
TrackHit  TrackHitCollection::create(Args&&... args){
  int size = m_entries.size();
  auto obj = new TrackHitObj({size,m_collectionID},{args...});
  m_entries.push_back(obj);
  return TrackHit(obj);
}

template<size_t arraysize>
const std::array<class BareHit,arraysize> TrackHitCollection::Core() const {
  std::array<class BareHit,arraysize> tmp;
  auto valid_size = std::min(arraysize,m_entries.size());
  for (unsigned i = 0; i<valid_size; ++i){
    tmp[i] = m_entries[i]->data.Core;
 }
 return tmp;
}


#endif
