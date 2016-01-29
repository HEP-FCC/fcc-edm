//AUTOMATICALLY GENERATED - DO NOT EDIT

#ifndef TrackStateAssociationCollection_H
#define  TrackStateAssociationCollection_H

#include <string>
#include <vector>
#include <deque>
#include <array>

// podio specific includes
#include "podio/ICollectionProvider.h"
#include "podio/CollectionBase.h"
#include "podio/CollectionIDTable.h"

// datamodel specific includes
#include "TrackStateAssociationData.h"
#include "TrackStateAssociation.h"
#include "TrackStateAssociationObj.h"

namespace fcc {
typedef std::vector<TrackStateAssociationData> TrackStateAssociationDataContainer;
typedef std::deque<TrackStateAssociationObj*> TrackStateAssociationObjPointerContainer;

class TrackStateAssociationCollectionIterator {

  public:
    TrackStateAssociationCollectionIterator(int index, const TrackStateAssociationObjPointerContainer* collection) : m_index(index), m_object(nullptr), m_collection(collection) {}

    bool operator!=(const TrackStateAssociationCollectionIterator& x) const {
      return m_index != x.m_index; //TODO: may not be complete
    }

    const TrackStateAssociation operator*() const;
    const TrackStateAssociation* operator->() const;
    const TrackStateAssociationCollectionIterator& operator++() const;

  private:
    mutable int m_index;
    mutable TrackStateAssociation m_object;
    const TrackStateAssociationObjPointerContainer* m_collection;
};

/**
A Collection is identified by an ID.
*/

class TrackStateAssociationCollection : public podio::CollectionBase {

public:
  typedef const TrackStateAssociationCollectionIterator const_iterator;

  TrackStateAssociationCollection();
//  TrackStateAssociationCollection(const TrackStateAssociationCollection& ) = delete; // deletion doesn't work w/ ROOT IO ! :-(
//  TrackStateAssociationCollection(TrackStateAssociationVector* data, int collectionID);
  ~TrackStateAssociationCollection(){};

  void clear();
  /// Append a new object to the collection, and return this object.
  TrackStateAssociation create();

  /// Append a new object to the collection, and return this object.
  /// Initialized with the parameters given
  template<typename... Args>
  TrackStateAssociation create(Args&&... args);
  int size() const;

  /// Returns the object of given index
  const TrackStateAssociation operator[](unsigned int index) const;
  /// Returns the object of given index
  const TrackStateAssociation at(unsigned int index) const;


  /// Append object to the collection
  void push_back(ConstTrackStateAssociation object);

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
  std::vector<TrackStateAssociationData>* _getBuffer() { return m_data;};

   

private:
  int m_collectionID;
  TrackStateAssociationObjPointerContainer m_entries;
  // members to handle 1-to-N-relations
  std::vector<::fcc::ConstTrack>* m_rel_Track; //relation buffer for r/w
  std::vector<::fcc::ConstTrackState>* m_rel_State; //relation buffer for r/w

  // members to handle streaming
  podio::CollRefCollection* m_refCollections;
  TrackStateAssociationDataContainer* m_data;
};

template<typename... Args>
TrackStateAssociation  TrackStateAssociationCollection::create(Args&&... args){
  int size = m_entries.size();
  auto obj = new TrackStateAssociationObj({size,m_collectionID},{args...});
  m_entries.push_back(obj);
  return TrackStateAssociation(obj);
}


} // namespace fcc
#endif
