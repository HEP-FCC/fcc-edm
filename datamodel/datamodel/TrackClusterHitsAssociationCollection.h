//AUTOMATICALLY GENERATED - DO NOT EDIT

#ifndef TrackClusterHitsAssociationCollection_H
#define  TrackClusterHitsAssociationCollection_H

#include <string>
#include <vector>
#include <deque>
#include <array>

// podio specific includes
#include "podio/ICollectionProvider.h"
#include "podio/CollectionBase.h"
#include "podio/CollectionIDTable.h"

// datamodel specific includes
#include "TrackClusterHitsAssociationData.h"
#include "TrackClusterHitsAssociation.h"
#include "TrackClusterHitsAssociationObj.h"

namespace fcc {
typedef std::vector<TrackClusterHitsAssociationData> TrackClusterHitsAssociationDataContainer;
typedef std::deque<TrackClusterHitsAssociationObj*> TrackClusterHitsAssociationObjPointerContainer;

class TrackClusterHitsAssociationCollectionIterator {

  public:
    TrackClusterHitsAssociationCollectionIterator(int index, const TrackClusterHitsAssociationObjPointerContainer* collection) : m_index(index), m_object(nullptr), m_collection(collection) {}

    bool operator!=(const TrackClusterHitsAssociationCollectionIterator& x) const {
      return m_index != x.m_index; //TODO: may not be complete
    }

    const TrackClusterHitsAssociation operator*() const;
    const TrackClusterHitsAssociation* operator->() const;
    const TrackClusterHitsAssociationCollectionIterator& operator++() const;

  private:
    mutable int m_index;
    mutable TrackClusterHitsAssociation m_object;
    const TrackClusterHitsAssociationObjPointerContainer* m_collection;
};

/**
A Collection is identified by an ID.
*/

class TrackClusterHitsAssociationCollection : public podio::CollectionBase {

public:
  typedef const TrackClusterHitsAssociationCollectionIterator const_iterator;

  TrackClusterHitsAssociationCollection();
//  TrackClusterHitsAssociationCollection(const TrackClusterHitsAssociationCollection& ) = delete; // deletion doesn't work w/ ROOT IO ! :-(
//  TrackClusterHitsAssociationCollection(TrackClusterHitsAssociationVector* data, int collectionID);
  ~TrackClusterHitsAssociationCollection(){};

  void clear();
  /// Append a new object to the collection, and return this object.
  TrackClusterHitsAssociation create();

  /// Append a new object to the collection, and return this object.
  /// Initialized with the parameters given
  template<typename... Args>
  TrackClusterHitsAssociation create(Args&&... args);
  int size() const;

  /// Returns the object of given index
  const TrackClusterHitsAssociation operator[](unsigned int index) const;
  /// Returns the object of given index
  const TrackClusterHitsAssociation at(unsigned int index) const;


  /// Append object to the collection
  void push_back(ConstTrackClusterHitsAssociation object);

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
  std::vector<TrackClusterHitsAssociationData>* _getBuffer() { return m_data;};

   

private:
  int m_collectionID;
  TrackClusterHitsAssociationObjPointerContainer m_entries;
  // members to handle 1-to-N-relations
  std::vector<::fcc::ConstTrackCluster>* m_rel_Cluster; //relation buffer for r/w
  std::vector<::fcc::ConstTrackHit>* m_rel_Hit; //relation buffer for r/w

  // members to handle streaming
  podio::CollRefCollection* m_refCollections;
  TrackClusterHitsAssociationDataContainer* m_data;
};

template<typename... Args>
TrackClusterHitsAssociation  TrackClusterHitsAssociationCollection::create(Args&&... args){
  int size = m_entries.size();
  auto obj = new TrackClusterHitsAssociationObj({size,m_collectionID},{args...});
  m_entries.push_back(obj);
  return TrackClusterHitsAssociation(obj);
}


} // namespace fcc
#endif
