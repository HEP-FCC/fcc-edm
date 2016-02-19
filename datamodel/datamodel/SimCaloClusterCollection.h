//AUTOMATICALLY GENERATED - DO NOT EDIT

#ifndef SimCaloClusterCollection_H
#define  SimCaloClusterCollection_H

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
#include "SimCaloClusterData.h"
#include "SimCaloCluster.h"
#include "SimCaloClusterObj.h"

namespace fcc {
typedef std::vector<SimCaloClusterData> SimCaloClusterDataContainer;
typedef std::deque<SimCaloClusterObj*> SimCaloClusterObjPointerContainer;

class SimCaloClusterCollectionIterator {

  public:
    SimCaloClusterCollectionIterator(int index, const SimCaloClusterObjPointerContainer* collection) : m_index(index), m_object(nullptr), m_collection(collection) {}

    bool operator!=(const SimCaloClusterCollectionIterator& x) const {
      return m_index != x.m_index; //TODO: may not be complete
    }

    const SimCaloCluster operator*() const;
    const SimCaloCluster* operator->() const;
    const SimCaloClusterCollectionIterator& operator++() const;

  private:
    mutable int m_index;
    mutable SimCaloCluster m_object;
    const SimCaloClusterObjPointerContainer* m_collection;
};

/**
A Collection is identified by an ID.
*/

class SimCaloClusterCollection : public podio::CollectionBase {

public:
  typedef const SimCaloClusterCollectionIterator const_iterator;

  SimCaloClusterCollection();
//  SimCaloClusterCollection(const SimCaloClusterCollection& ) = delete; // deletion doesn't work w/ ROOT IO ! :-(
//  SimCaloClusterCollection(SimCaloClusterVector* data, int collectionID);
  ~SimCaloClusterCollection(){};

  void clear();
  /// Append a new object to the collection, and return this object.
  SimCaloCluster create();

  /// Append a new object to the collection, and return this object.
  /// Initialized with the parameters given
  template<typename... Args>
  SimCaloCluster create(Args&&... args);
  int size() const;

  /// Returns the object of given index
  const SimCaloCluster operator[](unsigned int index) const;
  /// Returns the object of given index
  const SimCaloCluster at(unsigned int index) const;


  /// Append object to the collection
  void push_back(ConstSimCaloCluster object);

  void prepareForWrite();
  void prepareAfterRead();
  void setBuffer(void* address);
  bool setReferences(const podio::ICollectionProvider* collectionProvider);

  podio::CollRefCollection* referenceCollections() { return m_refCollections;};

  void setID(unsigned ID){
    m_collectionID = ID;
    std::for_each(m_entries.begin(),m_entries.end(),
                 [ID](SimCaloClusterObj* obj){obj->id = {obj->id.index,static_cast<int>(ID)}; }
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
  std::vector<SimCaloClusterData>* _getBuffer() { return m_data;};

     template<size_t arraysize>  
  const std::array<fcc::BareCluster,arraysize> Core() const;


private:
  int m_collectionID;
  SimCaloClusterObjPointerContainer m_entries;
  // members to handle 1-to-N-relations

  // members to handle streaming
  podio::CollRefCollection* m_refCollections;
  SimCaloClusterDataContainer* m_data;
};

template<typename... Args>
SimCaloCluster  SimCaloClusterCollection::create(Args&&... args){
  int size = m_entries.size();
  auto obj = new SimCaloClusterObj({size,m_collectionID},{args...});
  m_entries.push_back(obj);
  return SimCaloCluster(obj);
}

template<size_t arraysize>
const std::array<class fcc::BareCluster,arraysize> SimCaloClusterCollection::Core() const {
  std::array<class fcc::BareCluster,arraysize> tmp;
  auto valid_size = std::min(arraysize,m_entries.size());
  for (unsigned i = 0; i<valid_size; ++i){
    tmp[i] = m_entries[i]->data.Core;
 }
 return tmp;
}

} // namespace fcc
#endif
