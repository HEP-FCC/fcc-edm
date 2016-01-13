//AUTOMATICALLY GENERATED - DO NOT EDIT

#ifndef ParticleMCParticleAssociationCollection_H
#define  ParticleMCParticleAssociationCollection_H

#include <string>
#include <vector>
#include <deque>

// albers specific includes
#include "albers/Registry.h"
#include "albers/CollectionBase.h"

// datamodel specific includes
#include "datamodel/ParticleMCParticleAssociation.h"
#include "datamodel/ParticleMCParticleAssociationHandle.h"

typedef std::vector<ParticleMCParticleAssociation> ParticleMCParticleAssociationVector;
typedef std::vector<ParticleMCParticleAssociationHandle> ParticleMCParticleAssociationHandleContainer;

class ParticleMCParticleAssociationCollectionIterator {

  public:
    ParticleMCParticleAssociationCollectionIterator(int index, const ParticleMCParticleAssociationCollection* collection) : m_index(index), m_collection(collection) {}

    bool operator!=(const ParticleMCParticleAssociationCollectionIterator& x) const {
      return m_index != x.m_index; //TODO: may not be complete
    }

    const ParticleMCParticleAssociationHandle operator*() const;

    const ParticleMCParticleAssociationCollectionIterator& operator++() const {
      ++m_index;
      return *this;
    }

  private:
    mutable int m_index;
    const ParticleMCParticleAssociationCollection* m_collection;
};

/**
A Collection is identified by an ID.
*/

class ParticleMCParticleAssociationCollection : public albers::CollectionBase {

public:
  typedef const ParticleMCParticleAssociationCollectionIterator const_iterator;

  ParticleMCParticleAssociationCollection();
//  ParticleMCParticleAssociationCollection(ParticleMCParticleAssociationVector* data, int collectionID);
  ~ParticleMCParticleAssociationCollection(){};

  void clear();

  /// Append a new object to the collection, and return a Handle to this object.
  ParticleMCParticleAssociationHandle create();

  /// Insert an existing handle into the collection. 
  /// In this operation, the data pointed by the handle is copied.
  ParticleMCParticleAssociationHandle insert(const ParticleMCParticleAssociationHandle& origin);  
  
  /// Returns a Handle to the object at position index in the collection
  const ParticleMCParticleAssociationHandle& get(int index) const;

  /// Currently does nothing
  void prepareForWrite(const albers::Registry* registry);
  void prepareAfterRead(albers::Registry* registry);
  void setPODsAddress(const void* address);

  void setID(unsigned ID){m_collectionID = ID;};

  // support for the iterator protocol
  const const_iterator begin() const {
    return const_iterator(0, this);
  }
  const	const_iterator end() const {
    return const_iterator(m_handles.size(), this);
  }

//  std::vector<std::pair<std::string,albers::CollectionBase*>>& referenceCollections();

  /// returns the address of the pointer to the data buffer
  void* _getRawBuffer() { return (void*)&m_data;};

  /// returns the pointer to the data buffer
  std::vector<ParticleMCParticleAssociation>* _getBuffer() { return m_data;};

  /// returns the collection of Handles
  const ParticleMCParticleAssociationHandleContainer& getHandles() { return m_handles; }

  /// print some information
  void print() const;


private:
  unsigned m_collectionID;
  ParticleMCParticleAssociationVector* m_data;
  ParticleMCParticleAssociationHandleContainer m_handles;
  // members to handle 1-to-N-relations
  
};

#endif