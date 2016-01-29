//AUTOMATICALLY GENERATED - DO NOT EDIT

#ifndef TrackCollection_H
#define  TrackCollection_H

#include <string>
#include <vector>
#include <deque>
#include <array>

// podio specific includes
#include "podio/ICollectionProvider.h"
#include "podio/CollectionBase.h"
#include "podio/CollectionIDTable.h"

// datamodel specific includes
#include "TrackData.h"
#include "Track.h"
#include "TrackObj.h"

namespace fcc {
typedef std::vector<TrackData> TrackDataContainer;
typedef std::deque<TrackObj*> TrackObjPointerContainer;

class TrackCollectionIterator {

  public:
    TrackCollectionIterator(int index, const TrackObjPointerContainer* collection) : m_index(index), m_object(nullptr), m_collection(collection) {}

    bool operator!=(const TrackCollectionIterator& x) const {
      return m_index != x.m_index; //TODO: may not be complete
    }

    const Track operator*() const;
    const Track* operator->() const;
    const TrackCollectionIterator& operator++() const;

  private:
    mutable int m_index;
    mutable Track m_object;
    const TrackObjPointerContainer* m_collection;
};

/**
A Collection is identified by an ID.
*/

class TrackCollection : public podio::CollectionBase {

public:
  typedef const TrackCollectionIterator const_iterator;

  TrackCollection();
//  TrackCollection(const TrackCollection& ) = delete; // deletion doesn't work w/ ROOT IO ! :-(
//  TrackCollection(TrackVector* data, int collectionID);
  ~TrackCollection(){};

  void clear();
  /// Append a new object to the collection, and return this object.
  Track create();

  /// Append a new object to the collection, and return this object.
  /// Initialized with the parameters given
  template<typename... Args>
  Track create(Args&&... args);
  int size() const;

  /// Returns the object of given index
  const Track operator[](unsigned int index) const;
  /// Returns the object of given index
  const Track at(unsigned int index) const;


  /// Append object to the collection
  void push_back(ConstTrack object);

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
  std::vector<TrackData>* _getBuffer() { return m_data;};

     template<size_t arraysize>  
  const std::array<float,arraysize> Chi2() const;
  template<size_t arraysize>  
  const std::array<unsigned,arraysize> Ndf() const;
  template<size_t arraysize>  
  const std::array<unsigned,arraysize> Bits() const;


private:
  int m_collectionID;
  TrackObjPointerContainer m_entries;
  // members to handle 1-to-N-relations

  // members to handle streaming
  podio::CollRefCollection* m_refCollections;
  TrackDataContainer* m_data;
};

template<typename... Args>
Track  TrackCollection::create(Args&&... args){
  int size = m_entries.size();
  auto obj = new TrackObj({size,m_collectionID},{args...});
  m_entries.push_back(obj);
  return Track(obj);
}

template<size_t arraysize>
const std::array<float,arraysize> TrackCollection::Chi2() const {
  std::array<float,arraysize> tmp;
  auto valid_size = std::min(arraysize,m_entries.size());
  for (unsigned i = 0; i<valid_size; ++i){
    tmp[i] = m_entries[i]->data.Chi2;
 }
 return tmp;
}
template<size_t arraysize>
const std::array<unsigned,arraysize> TrackCollection::Ndf() const {
  std::array<unsigned,arraysize> tmp;
  auto valid_size = std::min(arraysize,m_entries.size());
  for (unsigned i = 0; i<valid_size; ++i){
    tmp[i] = m_entries[i]->data.Ndf;
 }
 return tmp;
}
template<size_t arraysize>
const std::array<unsigned,arraysize> TrackCollection::Bits() const {
  std::array<unsigned,arraysize> tmp;
  auto valid_size = std::min(arraysize,m_entries.size());
  for (unsigned i = 0; i<valid_size; ++i){
    tmp[i] = m_entries[i]->data.Bits;
 }
 return tmp;
}

} // namespace fcc
#endif
