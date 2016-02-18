//AUTOMATICALLY GENERATED - DO NOT EDIT

#ifndef TrackClusterCollection_H
#define  TrackClusterCollection_H

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
#include "TrackClusterData.h"
#include "TrackCluster.h"
#include "TrackClusterObj.h"

namespace fcc {
typedef std::vector<TrackClusterData> TrackClusterDataContainer;
typedef std::deque<TrackClusterObj*> TrackClusterObjPointerContainer;

class TrackClusterCollectionIterator {

  public:
    TrackClusterCollectionIterator(int index, const TrackClusterObjPointerContainer* collection) : m_index(index), m_object(nullptr), m_collection(collection) {}

    bool operator!=(const TrackClusterCollectionIterator& x) const {
      return m_index != x.m_index; //TODO: may not be complete
    }

    const TrackCluster operator*() const;
    const TrackCluster* operator->() const;
    const TrackClusterCollectionIterator& operator++() const;

  private:
    mutable int m_index;
    mutable TrackCluster m_object;
    const TrackClusterObjPointerContainer* m_collection;
};

/**
A Collection is identified by an ID.
*/

class TrackClusterCollection : public podio::CollectionBase {

public:
  typedef const TrackClusterCollectionIterator const_iterator;

  TrackClusterCollection();
//  TrackClusterCollection(const TrackClusterCollection& ) = delete; // deletion doesn't work w/ ROOT IO ! :-(
//  TrackClusterCollection(TrackClusterVector* data, int collectionID);
  ~TrackClusterCollection(){};

  void clear();
  /// Append a new object to the collection, and return this object.
  TrackCluster create();

  /// Append a new object to the collection, and return this object.
  /// Initialized with the parameters given
  template<typename... Args>
  TrackCluster create(Args&&... args);
  int size() const;

  /// Returns the object of given index
  const TrackCluster operator[](unsigned int index) const;
  /// Returns the object of given index
  const TrackCluster at(unsigned int index) const;


  /// Append object to the collection
  void push_back(ConstTrackCluster object);

  void prepareForWrite();
  void prepareAfterRead();
  void setBuffer(void* address);
  bool setReferences(const podio::ICollectionProvider* collectionProvider);

  podio::CollRefCollection* referenceCollections() { return m_refCollections;};

  void setID(unsigned ID){
    m_collectionID = ID;
    std::for_each(m_entries.begin(),m_entries.end(),
                 [ID](TrackClusterObj* obj){obj->id = {obj->id.index,static_cast<int>(ID)}; }
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
  std::vector<TrackClusterData>* _getBuffer() { return m_data;};

     template<size_t arraysize>  
  const std::array<fcc::BareCluster,arraysize> Core() const;


private:
  int m_collectionID;
  TrackClusterObjPointerContainer m_entries;
  // members to handle 1-to-N-relations

  // members to handle streaming
  podio::CollRefCollection* m_refCollections;
  TrackClusterDataContainer* m_data;
};

template<typename... Args>
TrackCluster  TrackClusterCollection::create(Args&&... args){
  int size = m_entries.size();
  auto obj = new TrackClusterObj({size,m_collectionID},{args...});
  m_entries.push_back(obj);
  return TrackCluster(obj);
}

template<size_t arraysize>
const std::array<class fcc::BareCluster,arraysize> TrackClusterCollection::Core() const {
  std::array<class fcc::BareCluster,arraysize> tmp;
  auto valid_size = std::min(arraysize,m_entries.size());
  for (unsigned i = 0; i<valid_size; ++i){
    tmp[i] = m_entries[i]->data.Core;
 }
 return tmp;
}

} // namespace fcc
#endif
