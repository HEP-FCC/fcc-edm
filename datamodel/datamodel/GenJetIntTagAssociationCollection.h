//AUTOMATICALLY GENERATED - DO NOT EDIT

#ifndef GenJetIntTagAssociationCollection_H
#define  GenJetIntTagAssociationCollection_H

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
#include "GenJetIntTagAssociationData.h"
#include "GenJetIntTagAssociation.h"
#include "GenJetIntTagAssociationObj.h"

namespace fcc {
typedef std::vector<GenJetIntTagAssociationData> GenJetIntTagAssociationDataContainer;
typedef std::deque<GenJetIntTagAssociationObj*> GenJetIntTagAssociationObjPointerContainer;

class GenJetIntTagAssociationCollectionIterator {

  public:
    GenJetIntTagAssociationCollectionIterator(int index, const GenJetIntTagAssociationObjPointerContainer* collection) : m_index(index), m_object(nullptr), m_collection(collection) {}

    bool operator!=(const GenJetIntTagAssociationCollectionIterator& x) const {
      return m_index != x.m_index; //TODO: may not be complete
    }

    const GenJetIntTagAssociation operator*() const;
    const GenJetIntTagAssociation* operator->() const;
    const GenJetIntTagAssociationCollectionIterator& operator++() const;

  private:
    mutable int m_index;
    mutable GenJetIntTagAssociation m_object;
    const GenJetIntTagAssociationObjPointerContainer* m_collection;
};

/**
A Collection is identified by an ID.
*/

class GenJetIntTagAssociationCollection : public podio::CollectionBase {

public:
  typedef const GenJetIntTagAssociationCollectionIterator const_iterator;

  GenJetIntTagAssociationCollection();
//  GenJetIntTagAssociationCollection(const GenJetIntTagAssociationCollection& ) = delete; // deletion doesn't work w/ ROOT IO ! :-(
//  GenJetIntTagAssociationCollection(GenJetIntTagAssociationVector* data, int collectionID);
  ~GenJetIntTagAssociationCollection(){};

  void clear();
  /// Append a new object to the collection, and return this object.
  GenJetIntTagAssociation create();

  /// Append a new object to the collection, and return this object.
  /// Initialized with the parameters given
  template<typename... Args>
  GenJetIntTagAssociation create(Args&&... args);
  int size() const;

  /// Returns the object of given index
  const GenJetIntTagAssociation operator[](unsigned int index) const;
  /// Returns the object of given index
  const GenJetIntTagAssociation at(unsigned int index) const;


  /// Append object to the collection
  void push_back(ConstGenJetIntTagAssociation object);

  void prepareForWrite();
  void prepareAfterRead();
  void setBuffer(void* address);
  bool setReferences(const podio::ICollectionProvider* collectionProvider);

  podio::CollRefCollection* referenceCollections() { return m_refCollections;};

  void setID(unsigned ID){
    m_collectionID = ID;
    std::for_each(m_entries.begin(),m_entries.end(),
                 [ID](GenJetIntTagAssociationObj* obj){obj->id = {obj->id.index,static_cast<int>(ID)}; }
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
  std::vector<GenJetIntTagAssociationData>* _getBuffer() { return m_data;};

   

private:
  int m_collectionID;
  GenJetIntTagAssociationObjPointerContainer m_entries;
  // members to handle 1-to-N-relations
  std::vector<::fcc::ConstGenJet>* m_rel_Jet; //relation buffer for r/w
  std::vector<::fcc::ConstIntTag>* m_rel_Tag; //relation buffer for r/w

  // members to handle streaming
  podio::CollRefCollection* m_refCollections;
  GenJetIntTagAssociationDataContainer* m_data;
};

template<typename... Args>
GenJetIntTagAssociation  GenJetIntTagAssociationCollection::create(Args&&... args){
  int size = m_entries.size();
  auto obj = new GenJetIntTagAssociationObj({size,m_collectionID},{args...});
  m_entries.push_back(obj);
  return GenJetIntTagAssociation(obj);
}


} // namespace fcc
#endif
