//AUTOMATICALLY GENERATED - DO NOT EDIT

#ifndef SimCaloClusterHitAssociationCollection_H
#define  SimCaloClusterHitAssociationCollection_H

#include <string>
#include <vector>
#include <deque>
#include <array>

// podio specific includes
#include "podio/ICollectionProvider.h"
#include "podio/CollectionBase.h"
#include "podio/CollectionIDTable.h"

// datamodel specific includes
#include "SimCaloClusterHitAssociationData.h"
#include "SimCaloClusterHitAssociation.h"
#include "SimCaloClusterHitAssociationObj.h"

namespace fcc {
typedef std::vector<SimCaloClusterHitAssociationData> SimCaloClusterHitAssociationDataContainer;
typedef std::deque<SimCaloClusterHitAssociationObj*> SimCaloClusterHitAssociationObjPointerContainer;

class SimCaloClusterHitAssociationCollectionIterator {

  public:
    SimCaloClusterHitAssociationCollectionIterator(int index, const SimCaloClusterHitAssociationObjPointerContainer* collection) : m_index(index), m_object(nullptr), m_collection(collection) {}

    bool operator!=(const SimCaloClusterHitAssociationCollectionIterator& x) const {
      return m_index != x.m_index; //TODO: may not be complete
    }

    const SimCaloClusterHitAssociation operator*() const;
    const SimCaloClusterHitAssociation* operator->() const;
    const SimCaloClusterHitAssociationCollectionIterator& operator++() const;

  private:
    mutable int m_index;
    mutable SimCaloClusterHitAssociation m_object;
    const SimCaloClusterHitAssociationObjPointerContainer* m_collection;
};

/**
A Collection is identified by an ID.
*/

class SimCaloClusterHitAssociationCollection : public podio::CollectionBase {

public:
  typedef const SimCaloClusterHitAssociationCollectionIterator const_iterator;

  SimCaloClusterHitAssociationCollection();
//  SimCaloClusterHitAssociationCollection(const SimCaloClusterHitAssociationCollection& ) = delete; // deletion doesn't work w/ ROOT IO ! :-(
//  SimCaloClusterHitAssociationCollection(SimCaloClusterHitAssociationVector* data, int collectionID);
  ~SimCaloClusterHitAssociationCollection(){};

  void clear();
  /// Append a new object to the collection, and return this object.
  SimCaloClusterHitAssociation create();

  /// Append a new object to the collection, and return this object.
  /// Initialized with the parameters given
  template<typename... Args>
  SimCaloClusterHitAssociation create(Args&&... args);
  int size() const;

  /// Returns the object of given index
  const SimCaloClusterHitAssociation operator[](unsigned int index) const;
  /// Returns the object of given index
  const SimCaloClusterHitAssociation at(unsigned int index) const;


  /// Append object to the collection
  void push_back(ConstSimCaloClusterHitAssociation object);

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
  std::vector<SimCaloClusterHitAssociationData>* _getBuffer() { return m_data;};

   

private:
  int m_collectionID;
  SimCaloClusterHitAssociationObjPointerContainer m_entries;
  // members to handle 1-to-N-relations
  std::vector<::fcc::ConstSimCaloCluster>* m_rel_Cluster; //relation buffer for r/w
  std::vector<::fcc::ConstSimCaloHit>* m_rel_Hit; //relation buffer for r/w

  // members to handle streaming
  podio::CollRefCollection* m_refCollections;
  SimCaloClusterHitAssociationDataContainer* m_data;
};

template<typename... Args>
SimCaloClusterHitAssociation  SimCaloClusterHitAssociationCollection::create(Args&&... args){
  int size = m_entries.size();
  auto obj = new SimCaloClusterHitAssociationObj({size,m_collectionID},{args...});
  m_entries.push_back(obj);
  return SimCaloClusterHitAssociation(obj);
}


} // namespace fcc
#endif
