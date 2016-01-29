//AUTOMATICALLY GENERATED - DO NOT EDIT

#ifndef SimCaloHitCollection_H
#define  SimCaloHitCollection_H

#include <string>
#include <vector>
#include <deque>
#include <array>

// podio specific includes
#include "podio/ICollectionProvider.h"
#include "podio/CollectionBase.h"
#include "podio/CollectionIDTable.h"

// datamodel specific includes
#include "SimCaloHitData.h"
#include "SimCaloHit.h"
#include "SimCaloHitObj.h"

namespace fcc {
typedef std::vector<SimCaloHitData> SimCaloHitDataContainer;
typedef std::deque<SimCaloHitObj*> SimCaloHitObjPointerContainer;

class SimCaloHitCollectionIterator {

  public:
    SimCaloHitCollectionIterator(int index, const SimCaloHitObjPointerContainer* collection) : m_index(index), m_object(nullptr), m_collection(collection) {}

    bool operator!=(const SimCaloHitCollectionIterator& x) const {
      return m_index != x.m_index; //TODO: may not be complete
    }

    const SimCaloHit operator*() const;
    const SimCaloHit* operator->() const;
    const SimCaloHitCollectionIterator& operator++() const;

  private:
    mutable int m_index;
    mutable SimCaloHit m_object;
    const SimCaloHitObjPointerContainer* m_collection;
};

/**
A Collection is identified by an ID.
*/

class SimCaloHitCollection : public podio::CollectionBase {

public:
  typedef const SimCaloHitCollectionIterator const_iterator;

  SimCaloHitCollection();
//  SimCaloHitCollection(const SimCaloHitCollection& ) = delete; // deletion doesn't work w/ ROOT IO ! :-(
//  SimCaloHitCollection(SimCaloHitVector* data, int collectionID);
  ~SimCaloHitCollection(){};

  void clear();
  /// Append a new object to the collection, and return this object.
  SimCaloHit create();

  /// Append a new object to the collection, and return this object.
  /// Initialized with the parameters given
  template<typename... Args>
  SimCaloHit create(Args&&... args);
  int size() const;

  /// Returns the object of given index
  const SimCaloHit operator[](unsigned int index) const;
  /// Returns the object of given index
  const SimCaloHit at(unsigned int index) const;


  /// Append object to the collection
  void push_back(ConstSimCaloHit object);

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
  std::vector<SimCaloHitData>* _getBuffer() { return m_data;};

     template<size_t arraysize>  
  const std::array<fcc::BareHit,arraysize> Core() const;


private:
  int m_collectionID;
  SimCaloHitObjPointerContainer m_entries;
  // members to handle 1-to-N-relations

  // members to handle streaming
  podio::CollRefCollection* m_refCollections;
  SimCaloHitDataContainer* m_data;
};

template<typename... Args>
SimCaloHit  SimCaloHitCollection::create(Args&&... args){
  int size = m_entries.size();
  auto obj = new SimCaloHitObj({size,m_collectionID},{args...});
  m_entries.push_back(obj);
  return SimCaloHit(obj);
}

template<size_t arraysize>
const std::array<class fcc::BareHit,arraysize> SimCaloHitCollection::Core() const {
  std::array<class fcc::BareHit,arraysize> tmp;
  auto valid_size = std::min(arraysize,m_entries.size());
  for (unsigned i = 0; i<valid_size; ++i){
    tmp[i] = m_entries[i]->data.Core;
 }
 return tmp;
}

} // namespace fcc
#endif
