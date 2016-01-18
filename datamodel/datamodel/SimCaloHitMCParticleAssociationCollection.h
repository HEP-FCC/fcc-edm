//AUTOMATICALLY GENERATED - DO NOT EDIT

#ifndef SimCaloHitMCParticleAssociationCollection_H
#define  SimCaloHitMCParticleAssociationCollection_H

#include <string>
#include <vector>
#include <deque>
#include <array>

// podio specific includes
#include "podio/ICollectionProvider.h"
#include "podio/CollectionBase.h"
#include "podio/CollectionIDTable.h"

// datamodel specific includes
#include "SimCaloHitMCParticleAssociationData.h"
#include "SimCaloHitMCParticleAssociation.h"
#include "SimCaloHitMCParticleAssociationObj.h"


typedef std::vector<SimCaloHitMCParticleAssociationData> SimCaloHitMCParticleAssociationDataContainer;
typedef std::deque<SimCaloHitMCParticleAssociationObj*> SimCaloHitMCParticleAssociationObjPointerContainer;

class SimCaloHitMCParticleAssociationCollectionIterator {

  public:
    SimCaloHitMCParticleAssociationCollectionIterator(int index, const SimCaloHitMCParticleAssociationObjPointerContainer* collection) : m_index(index), m_object(nullptr), m_collection(collection) {}

    bool operator!=(const SimCaloHitMCParticleAssociationCollectionIterator& x) const {
      return m_index != x.m_index; //TODO: may not be complete
    }

    const SimCaloHitMCParticleAssociation operator*() const;
    const SimCaloHitMCParticleAssociation* operator->() const;
    const SimCaloHitMCParticleAssociationCollectionIterator& operator++() const;

  private:
    mutable int m_index;
    mutable SimCaloHitMCParticleAssociation m_object;
    const SimCaloHitMCParticleAssociationObjPointerContainer* m_collection;
};

/**
A Collection is identified by an ID.
*/

class SimCaloHitMCParticleAssociationCollection : public podio::CollectionBase {

public:
  typedef const SimCaloHitMCParticleAssociationCollectionIterator const_iterator;

  SimCaloHitMCParticleAssociationCollection();
//  SimCaloHitMCParticleAssociationCollection(const SimCaloHitMCParticleAssociationCollection& ) = delete; // deletion doesn't work w/ ROOT IO ! :-(
//  SimCaloHitMCParticleAssociationCollection(SimCaloHitMCParticleAssociationVector* data, int collectionID);
  ~SimCaloHitMCParticleAssociationCollection(){};

  void clear();
  /// Append a new object to the collection, and return this object.
  SimCaloHitMCParticleAssociation create();

  /// Append a new object to the collection, and return this object.
  /// Initialized with the parameters given
  template<typename... Args>
  SimCaloHitMCParticleAssociation create(Args&&... args);
  int size() const;

  /// Returns the object of given index
  const SimCaloHitMCParticleAssociation operator[](unsigned int index) const;
  /// Returns the object of given index
  const SimCaloHitMCParticleAssociation at(unsigned int index) const;


  /// Append object to the collection
  void push_back(ConstSimCaloHitMCParticleAssociation object);

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
  std::vector<SimCaloHitMCParticleAssociationData>* _getBuffer() { return m_data;};

     template<size_t arraysize>  
  const std::array<float,arraysize> Fraction() const;


private:
  int m_collectionID;
  SimCaloHitMCParticleAssociationObjPointerContainer m_entries;
  // members to handle 1-to-N-relations
  std::vector<ConstSimCaloHit>* m_rel_Hit; //relation buffer for r/w
  std::vector<ConstMCParticle>* m_rel_Particle; //relation buffer for r/w

  // members to handle streaming
  podio::CollRefCollection* m_refCollections;
  SimCaloHitMCParticleAssociationDataContainer* m_data;
};

template<typename... Args>
SimCaloHitMCParticleAssociation  SimCaloHitMCParticleAssociationCollection::create(Args&&... args){
  int size = m_entries.size();
  auto obj = new SimCaloHitMCParticleAssociationObj({size,m_collectionID},{args...});
  m_entries.push_back(obj);
  return SimCaloHitMCParticleAssociation(obj);
}

template<size_t arraysize>
const std::array<float,arraysize> SimCaloHitMCParticleAssociationCollection::Fraction() const {
  std::array<float,arraysize> tmp;
  auto valid_size = std::min(arraysize,m_entries.size());
  for (unsigned i = 0; i<valid_size; ++i){
    tmp[i] = m_entries[i]->data.Fraction;
 }
 return tmp;
}


#endif
