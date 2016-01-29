//AUTOMATICALLY GENERATED - DO NOT EDIT

#ifndef ParticleCollection_H
#define  ParticleCollection_H

#include <string>
#include <vector>
#include <deque>
#include <array>

// podio specific includes
#include "podio/ICollectionProvider.h"
#include "podio/CollectionBase.h"
#include "podio/CollectionIDTable.h"

// datamodel specific includes
#include "ParticleData.h"
#include "Particle.h"
#include "ParticleObj.h"

namespace fcc {
typedef std::vector<ParticleData> ParticleDataContainer;
typedef std::deque<ParticleObj*> ParticleObjPointerContainer;

class ParticleCollectionIterator {

  public:
    ParticleCollectionIterator(int index, const ParticleObjPointerContainer* collection) : m_index(index), m_object(nullptr), m_collection(collection) {}

    bool operator!=(const ParticleCollectionIterator& x) const {
      return m_index != x.m_index; //TODO: may not be complete
    }

    const Particle operator*() const;
    const Particle* operator->() const;
    const ParticleCollectionIterator& operator++() const;

  private:
    mutable int m_index;
    mutable Particle m_object;
    const ParticleObjPointerContainer* m_collection;
};

/**
A Collection is identified by an ID.
*/

class ParticleCollection : public podio::CollectionBase {

public:
  typedef const ParticleCollectionIterator const_iterator;

  ParticleCollection();
//  ParticleCollection(const ParticleCollection& ) = delete; // deletion doesn't work w/ ROOT IO ! :-(
//  ParticleCollection(ParticleVector* data, int collectionID);
  ~ParticleCollection(){};

  void clear();
  /// Append a new object to the collection, and return this object.
  Particle create();

  /// Append a new object to the collection, and return this object.
  /// Initialized with the parameters given
  template<typename... Args>
  Particle create(Args&&... args);
  int size() const;

  /// Returns the object of given index
  const Particle operator[](unsigned int index) const;
  /// Returns the object of given index
  const Particle at(unsigned int index) const;


  /// Append object to the collection
  void push_back(ConstParticle object);

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
  std::vector<ParticleData>* _getBuffer() { return m_data;};

     template<size_t arraysize>  
  const std::array<fcc::BareParticle,arraysize> Core() const;


private:
  int m_collectionID;
  ParticleObjPointerContainer m_entries;
  // members to handle 1-to-N-relations

  // members to handle streaming
  podio::CollRefCollection* m_refCollections;
  ParticleDataContainer* m_data;
};

template<typename... Args>
Particle  ParticleCollection::create(Args&&... args){
  int size = m_entries.size();
  auto obj = new ParticleObj({size,m_collectionID},{args...});
  m_entries.push_back(obj);
  return Particle(obj);
}

template<size_t arraysize>
const std::array<class fcc::BareParticle,arraysize> ParticleCollection::Core() const {
  std::array<class fcc::BareParticle,arraysize> tmp;
  auto valid_size = std::min(arraysize,m_entries.size());
  for (unsigned i = 0; i<valid_size; ++i){
    tmp[i] = m_entries[i]->data.Core;
 }
 return tmp;
}

} // namespace fcc
#endif
