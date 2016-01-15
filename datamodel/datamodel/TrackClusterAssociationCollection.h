//AUTOMATICALLY GENERATED - DO NOT EDIT

#ifndef TrackClusterAssociationCollection_H
#define  TrackClusterAssociationCollection_H

#include <string>
#include <vector>
#include <deque>
#include <array>

// podio specific includes
#include "podio/ICollectionProvider.h"
#include "podio/CollectionBase.h"
#include "podio/CollectionIDTable.h"

// datamodel specific includes
#include "TrackClusterAssociationData.h"
#include "TrackClusterAssociation.h"
#include "TrackClusterAssociationObj.h"


typedef std::vector<TrackClusterAssociationData> TrackClusterAssociationDataContainer;
typedef std::deque<TrackClusterAssociationObj*> TrackClusterAssociationObjPointerContainer;

class TrackClusterAssociationCollectionIterator {

  public:
    TrackClusterAssociationCollectionIterator(int index, const TrackClusterAssociationObjPointerContainer* collection) : m_index(index), m_object(nullptr), m_collection(collection) {}

    bool operator!=(const TrackClusterAssociationCollectionIterator& x) const {
      return m_index != x.m_index; //TODO: may not be complete
    }

    const TrackClusterAssociation operator*() const;
    const TrackClusterAssociation* operator->() const;
    const TrackClusterAssociationCollectionIterator& operator++() const;

  private:
    mutable int m_index;
    mutable TrackClusterAssociation m_object;
    const TrackClusterAssociationObjPointerContainer* m_collection;
};

/**
A Collection is identified by an ID.
*/

class TrackClusterAssociationCollection : public podio::CollectionBase {

public:
  typedef const TrackClusterAssociationCollectionIterator const_iterator;

  TrackClusterAssociationCollection();
//  TrackClusterAssociationCollection(const TrackClusterAssociationCollection& ) = delete; // deletion doesn't work w/ ROOT IO ! :-(
//  TrackClusterAssociationCollection(TrackClusterAssociationVector* data, int collectionID);
  ~TrackClusterAssociationCollection(){};

  void clear();
  /// Append a new object to the collection, and return this object.
  TrackClusterAssociation create();

  /// Append a new object to the collection, and return this object.
  /// Initialized with the parameters given
  template<typename... Args>
  TrackClusterAssociation create(Args&&... args);
  int size() const;

  /// Returns the object of given index
  const TrackClusterAssociation operator[](unsigned int index) const;
  /// Returns the object of given index
  const TrackClusterAssociation at(unsigned int index) const;


  /// Append object to the collection
  void push_back(ConstTrackClusterAssociation object);

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
  std::vector<TrackClusterAssociationData>* _getBuffer() { return m_data;};

   

private:
  int m_collectionID;
  TrackClusterAssociationObjPointerContainer m_entries;
  // members to handle 1-to-N-relations
  std::vector<ConstTrack>* m_rel_Track; //relation buffer for r/w
  std::vector<ConstTrackCluster>* m_rel_Cluster; //relation buffer for r/w

  // members to handle streaming
  podio::CollRefCollection* m_refCollections;
  TrackClusterAssociationDataContainer* m_data;
};

template<typename... Args>
TrackClusterAssociation  TrackClusterAssociationCollection::create(Args&&... args){
  int size = m_entries.size();
  auto obj = new TrackClusterAssociationObj({size,m_collectionID},{args...});
  m_entries.push_back(obj);
  return TrackClusterAssociation(obj);
}



#endif
