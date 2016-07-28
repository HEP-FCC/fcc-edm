//AUTOMATICALLY GENERATED - DO NOT EDIT

#ifndef CaloClusterCollection_H
#define  CaloClusterCollection_H

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
#include "CaloClusterData.h"
#include "CaloCluster.h"
#include "CaloClusterObj.h"

namespace fcc {
typedef std::vector<CaloClusterData> CaloClusterDataContainer;
typedef std::deque<CaloClusterObj*> CaloClusterObjPointerContainer;

class CaloClusterCollectionIterator {

  public:
    CaloClusterCollectionIterator(int index, const CaloClusterObjPointerContainer* collection) : m_index(index), m_object(nullptr), m_collection(collection) {}

    bool operator!=(const CaloClusterCollectionIterator& x) const {
      return m_index != x.m_index; //TODO: may not be complete
    }

    const CaloCluster operator*() const;
    const CaloCluster* operator->() const;
    const CaloClusterCollectionIterator& operator++() const;

  private:
    mutable int m_index;
    mutable CaloCluster m_object;
    const CaloClusterObjPointerContainer* m_collection;
};

/**
A Collection is identified by an ID.
*/

class CaloClusterCollection : public podio::CollectionBase {

public:
  typedef const CaloClusterCollectionIterator const_iterator;

  CaloClusterCollection();
//  CaloClusterCollection(const CaloClusterCollection& ) = delete; // deletion doesn't work w/ ROOT IO ! :-(
//  CaloClusterCollection(CaloClusterVector* data, int collectionID);
  ~CaloClusterCollection();

  void clear();
  /// Append a new object to the collection, and return this object.
  CaloCluster create();

  /// Append a new object to the collection, and return this object.
  /// Initialized with the parameters given
  template<typename... Args>
  CaloCluster create(Args&&... args);
  int size() const;

  /// Returns the object of given index
  const CaloCluster operator[](unsigned int index) const;
  /// Returns the object of given index
  const CaloCluster at(unsigned int index) const;


  /// Append object to the collection
  void push_back(ConstCaloCluster object);

  void prepareForWrite();
  void prepareAfterRead();
  void setBuffer(void* address);
  bool setReferences(const podio::ICollectionProvider* collectionProvider);

  podio::CollRefCollection* referenceCollections() { return &m_refCollections;};

  void setID(unsigned ID){
    m_collectionID = ID;
    std::for_each(m_entries.begin(),m_entries.end(),
                 [ID](CaloClusterObj* obj){obj->id = {obj->id.index,static_cast<int>(ID)}; }
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
  std::vector<CaloClusterData>* _getBuffer() { return m_data;};

    template<size_t arraysize>
  const std::array<fcc::BareCluster,arraysize> core() const;


private:
  bool m_isValid;
  int m_collectionID;
  CaloClusterObjPointerContainer m_entries;
  // members to handle 1-to-N-relations
  std::vector<fcc::ConstCaloHit>* m_rel_hits; ///< Relation buffer for read / write
  std::vector<std::vector<fcc::ConstCaloHit>*> m_rel_hits_tmp; ///< Relation buffer for internal book-keeping

  // members to handle streaming
  podio::CollRefCollection m_refCollections;
  CaloClusterDataContainer* m_data;
};

template<typename... Args>
CaloCluster  CaloClusterCollection::create(Args&&... args){
  int size = m_entries.size();
  auto obj = new CaloClusterObj({size,m_collectionID},{args...});
  m_entries.push_back(obj);
  return CaloCluster(obj);
}

template<size_t arraysize>
const std::array<class fcc::BareCluster,arraysize> CaloClusterCollection::core() const {
  std::array<class fcc::BareCluster,arraysize> tmp;
  auto valid_size = std::min(arraysize,m_entries.size());
  for (unsigned i = 0; i<valid_size; ++i){
    tmp[i] = m_entries[i]->data.core;
 }
 return tmp;
}

} // namespace fcc
#endif
