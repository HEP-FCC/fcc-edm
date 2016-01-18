//AUTOMATICALLY GENERATED - DO NOT EDIT

#ifndef CaloHitCollection_H
#define  CaloHitCollection_H

#include <string>
#include <vector>
#include <deque>
#include <array>

// podio specific includes
#include "podio/ICollectionProvider.h"
#include "podio/CollectionBase.h"
#include "podio/CollectionIDTable.h"

// datamodel specific includes
#include "CaloHitData.h"
#include "CaloHit.h"
#include "CaloHitObj.h"


typedef std::vector<CaloHitData> CaloHitDataContainer;
typedef std::deque<CaloHitObj*> CaloHitObjPointerContainer;

class CaloHitCollectionIterator {

  public:
    CaloHitCollectionIterator(int index, const CaloHitObjPointerContainer* collection) : m_index(index), m_object(nullptr), m_collection(collection) {}

    bool operator!=(const CaloHitCollectionIterator& x) const {
      return m_index != x.m_index; //TODO: may not be complete
    }

    const CaloHit operator*() const;
    const CaloHit* operator->() const;
    const CaloHitCollectionIterator& operator++() const;

  private:
    mutable int m_index;
    mutable CaloHit m_object;
    const CaloHitObjPointerContainer* m_collection;
};

/**
A Collection is identified by an ID.
*/

class CaloHitCollection : public podio::CollectionBase {

public:
  typedef const CaloHitCollectionIterator const_iterator;

  CaloHitCollection();
//  CaloHitCollection(const CaloHitCollection& ) = delete; // deletion doesn't work w/ ROOT IO ! :-(
//  CaloHitCollection(CaloHitVector* data, int collectionID);
  ~CaloHitCollection(){};

  void clear();
  /// Append a new object to the collection, and return this object.
  CaloHit create();

  /// Append a new object to the collection, and return this object.
  /// Initialized with the parameters given
  template<typename... Args>
  CaloHit create(Args&&... args);
  int size() const;

  /// Returns the object of given index
  const CaloHit operator[](unsigned int index) const;
  /// Returns the object of given index
  const CaloHit at(unsigned int index) const;


  /// Append object to the collection
  void push_back(ConstCaloHit object);

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
  std::vector<CaloHitData>* _getBuffer() { return m_data;};

     template<size_t arraysize>  
  const std::array<BareHit,arraysize> Core() const;


private:
  int m_collectionID;
  CaloHitObjPointerContainer m_entries;
  // members to handle 1-to-N-relations

  // members to handle streaming
  podio::CollRefCollection* m_refCollections;
  CaloHitDataContainer* m_data;
};

template<typename... Args>
CaloHit  CaloHitCollection::create(Args&&... args){
  int size = m_entries.size();
  auto obj = new CaloHitObj({size,m_collectionID},{args...});
  m_entries.push_back(obj);
  return CaloHit(obj);
}

template<size_t arraysize>
const std::array<class BareHit,arraysize> CaloHitCollection::Core() const {
  std::array<class BareHit,arraysize> tmp;
  auto valid_size = std::min(arraysize,m_entries.size());
  for (unsigned i = 0; i<valid_size; ++i){
    tmp[i] = m_entries[i]->data.Core;
 }
 return tmp;
}


#endif
