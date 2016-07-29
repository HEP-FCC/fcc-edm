//AUTOMATICALLY GENERATED - DO NOT EDIT

#ifndef CaloHitAssociationCollection_H
#define  CaloHitAssociationCollection_H

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
#include "CaloHitAssociationData.h"
#include "CaloHitAssociation.h"
#include "CaloHitAssociationObj.h"

namespace fcc {
typedef std::vector<CaloHitAssociationData> CaloHitAssociationDataContainer;
typedef std::deque<CaloHitAssociationObj*> CaloHitAssociationObjPointerContainer;

class CaloHitAssociationCollectionIterator {

  public:
    CaloHitAssociationCollectionIterator(int index, const CaloHitAssociationObjPointerContainer* collection) : m_index(index), m_object(nullptr), m_collection(collection) {}

    bool operator!=(const CaloHitAssociationCollectionIterator& x) const {
      return m_index != x.m_index; //TODO: may not be complete
    }

    const CaloHitAssociation operator*() const;
    const CaloHitAssociation* operator->() const;
    const CaloHitAssociationCollectionIterator& operator++() const;

  private:
    mutable int m_index;
    mutable CaloHitAssociation m_object;
    const CaloHitAssociationObjPointerContainer* m_collection;
};

/**
A Collection is identified by an ID.
*/

class CaloHitAssociationCollection : public podio::CollectionBase {

public:
  typedef const CaloHitAssociationCollectionIterator const_iterator;

  CaloHitAssociationCollection();
//  CaloHitAssociationCollection(const CaloHitAssociationCollection& ) = delete; // deletion doesn't work w/ ROOT IO ! :-(
//  CaloHitAssociationCollection(CaloHitAssociationVector* data, int collectionID);
  ~CaloHitAssociationCollection();

  void clear();
  /// Append a new object to the collection, and return this object.
  CaloHitAssociation create();

  /// Append a new object to the collection, and return this object.
  /// Initialized with the parameters given
  template<typename... Args>
  CaloHitAssociation create(Args&&... args);
  int size() const;

  /// Returns the object of given index
  const CaloHitAssociation operator[](unsigned int index) const;
  /// Returns the object of given index
  const CaloHitAssociation at(unsigned int index) const;


  /// Append object to the collection
  void push_back(ConstCaloHitAssociation object);

  void prepareForWrite();
  void prepareAfterRead();
  void setBuffer(void* address);
  bool setReferences(const podio::ICollectionProvider* collectionProvider);

  podio::CollRefCollection* referenceCollections() { return &m_refCollections;};

  void setID(unsigned ID){
    m_collectionID = ID;
    std::for_each(m_entries.begin(),m_entries.end(),
                 [ID](CaloHitAssociationObj* obj){obj->id = {obj->id.index,static_cast<int>(ID)}; }
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
  std::vector<CaloHitAssociationData>* _getBuffer() { return m_data;};

   

private:
  bool m_isValid;
  int m_collectionID;
  CaloHitAssociationObjPointerContainer m_entries;
  // members to handle 1-to-N-relations
  std::vector<fcc::ConstCaloHit>* m_rel_rec; ///< Relation buffer for read / write
  std::vector<fcc::ConstCaloHit>* m_rel_sim; ///< Relation buffer for read / write

  // members to handle streaming
  podio::CollRefCollection m_refCollections;
  CaloHitAssociationDataContainer* m_data;
};

template<typename... Args>
CaloHitAssociation  CaloHitAssociationCollection::create(Args&&... args){
  int size = m_entries.size();
  auto obj = new CaloHitAssociationObj({size,m_collectionID},{args...});
  m_entries.push_back(obj);
  return CaloHitAssociation(obj);
}


} // namespace fcc
#endif
