//AUTOMATICALLY GENERATED - DO NOT EDIT

#ifndef ParticleMCParticleAssociationCollection_H
#define  ParticleMCParticleAssociationCollection_H

#include <string>
#include <vector>
#include <deque>
#include <array>

// podio specific includes
#include "podio/ICollectionProvider.h"
#include "podio/CollectionBase.h"
#include "podio/CollectionIDTable.h"

// datamodel specific includes
#include "ParticleMCParticleAssociationData.h"
#include "ParticleMCParticleAssociation.h"
#include "ParticleMCParticleAssociationObj.h"

namespace fcc {
typedef std::vector<ParticleMCParticleAssociationData> ParticleMCParticleAssociationDataContainer;
typedef std::deque<ParticleMCParticleAssociationObj*> ParticleMCParticleAssociationObjPointerContainer;

class ParticleMCParticleAssociationCollectionIterator {

  public:
    ParticleMCParticleAssociationCollectionIterator(int index, const ParticleMCParticleAssociationObjPointerContainer* collection) : m_index(index), m_object(nullptr), m_collection(collection) {}

    bool operator!=(const ParticleMCParticleAssociationCollectionIterator& x) const {
      return m_index != x.m_index; //TODO: may not be complete
    }

    const ParticleMCParticleAssociation operator*() const;
    const ParticleMCParticleAssociation* operator->() const;
    const ParticleMCParticleAssociationCollectionIterator& operator++() const;

  private:
    mutable int m_index;
    mutable ParticleMCParticleAssociation m_object;
    const ParticleMCParticleAssociationObjPointerContainer* m_collection;
};

/**
A Collection is identified by an ID.
*/

class ParticleMCParticleAssociationCollection : public podio::CollectionBase {

public:
  typedef const ParticleMCParticleAssociationCollectionIterator const_iterator;

  ParticleMCParticleAssociationCollection();
//  ParticleMCParticleAssociationCollection(const ParticleMCParticleAssociationCollection& ) = delete; // deletion doesn't work w/ ROOT IO ! :-(
//  ParticleMCParticleAssociationCollection(ParticleMCParticleAssociationVector* data, int collectionID);
  ~ParticleMCParticleAssociationCollection(){};

  void clear();
  /// Append a new object to the collection, and return this object.
  ParticleMCParticleAssociation create();

  /// Append a new object to the collection, and return this object.
  /// Initialized with the parameters given
  template<typename... Args>
  ParticleMCParticleAssociation create(Args&&... args);
  int size() const;

  /// Returns the object of given index
  const ParticleMCParticleAssociation operator[](unsigned int index) const;
  /// Returns the object of given index
  const ParticleMCParticleAssociation at(unsigned int index) const;


  /// Append object to the collection
  void push_back(ConstParticleMCParticleAssociation object);

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
  std::vector<ParticleMCParticleAssociationData>* _getBuffer() { return m_data;};

   

private:
  int m_collectionID;
  ParticleMCParticleAssociationObjPointerContainer m_entries;
  // members to handle 1-to-N-relations
  std::vector<::fcc::ConstParticle>* m_rel_Rec; //relation buffer for r/w
  std::vector<::fcc::ConstMCParticle>* m_rel_Sim; //relation buffer for r/w

  // members to handle streaming
  podio::CollRefCollection* m_refCollections;
  ParticleMCParticleAssociationDataContainer* m_data;
};

template<typename... Args>
ParticleMCParticleAssociation  ParticleMCParticleAssociationCollection::create(Args&&... args){
  int size = m_entries.size();
  auto obj = new ParticleMCParticleAssociationObj({size,m_collectionID},{args...});
  m_entries.push_back(obj);
  return ParticleMCParticleAssociation(obj);
}


} // namespace fcc
#endif
