//AUTOMATICALLY GENERATED - DO NOT EDIT

#ifndef MCParticleAssociationCollection_H
#define  MCParticleAssociationCollection_H

#include <string>
#include <vector>
#include <deque>
#include <array>

// podio specific includes
#include "podio/ICollectionProvider.h"
#include "podio/CollectionBase.h"
#include "podio/CollectionIDTable.h"

// datamodel specific includes
#include "MCParticleAssociationData.h"
#include "MCParticleAssociation.h"
#include "MCParticleAssociationObj.h"

namespace fcc {
typedef std::vector<MCParticleAssociationData> MCParticleAssociationDataContainer;
typedef std::deque<MCParticleAssociationObj*> MCParticleAssociationObjPointerContainer;

class MCParticleAssociationCollectionIterator {

  public:
    MCParticleAssociationCollectionIterator(int index, const MCParticleAssociationObjPointerContainer* collection) : m_index(index), m_object(nullptr), m_collection(collection) {}

    bool operator!=(const MCParticleAssociationCollectionIterator& x) const {
      return m_index != x.m_index; //TODO: may not be complete
    }

    const MCParticleAssociation operator*() const;
    const MCParticleAssociation* operator->() const;
    const MCParticleAssociationCollectionIterator& operator++() const;

  private:
    mutable int m_index;
    mutable MCParticleAssociation m_object;
    const MCParticleAssociationObjPointerContainer* m_collection;
};

/**
A Collection is identified by an ID.
*/

class MCParticleAssociationCollection : public podio::CollectionBase {

public:
  typedef const MCParticleAssociationCollectionIterator const_iterator;

  MCParticleAssociationCollection();
//  MCParticleAssociationCollection(const MCParticleAssociationCollection& ) = delete; // deletion doesn't work w/ ROOT IO ! :-(
//  MCParticleAssociationCollection(MCParticleAssociationVector* data, int collectionID);
  ~MCParticleAssociationCollection(){};

  void clear();
  /// Append a new object to the collection, and return this object.
  MCParticleAssociation create();

  /// Append a new object to the collection, and return this object.
  /// Initialized with the parameters given
  template<typename... Args>
  MCParticleAssociation create(Args&&... args);
  int size() const;

  /// Returns the object of given index
  const MCParticleAssociation operator[](unsigned int index) const;
  /// Returns the object of given index
  const MCParticleAssociation at(unsigned int index) const;


  /// Append object to the collection
  void push_back(ConstMCParticleAssociation object);

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
  std::vector<MCParticleAssociationData>* _getBuffer() { return m_data;};

   

private:
  int m_collectionID;
  MCParticleAssociationObjPointerContainer m_entries;
  // members to handle 1-to-N-relations
  std::vector<::fcc::ConstMCParticle>* m_rel_Mother; //relation buffer for r/w
  std::vector<::fcc::ConstMCParticle>* m_rel_Daughter; //relation buffer for r/w

  // members to handle streaming
  podio::CollRefCollection* m_refCollections;
  MCParticleAssociationDataContainer* m_data;
};

template<typename... Args>
MCParticleAssociation  MCParticleAssociationCollection::create(Args&&... args){
  int size = m_entries.size();
  auto obj = new MCParticleAssociationObj({size,m_collectionID},{args...});
  m_entries.push_back(obj);
  return MCParticleAssociation(obj);
}


} // namespace fcc
#endif
