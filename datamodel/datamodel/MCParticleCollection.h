//AUTOMATICALLY GENERATED - DO NOT EDIT

#ifndef MCParticleCollection_H
#define  MCParticleCollection_H

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
#include "MCParticleData.h"
#include "MCParticle.h"
#include "MCParticleObj.h"

namespace fcc {
typedef std::vector<MCParticleData> MCParticleDataContainer;
typedef std::deque<MCParticleObj*> MCParticleObjPointerContainer;

class MCParticleCollectionIterator {

  public:
    MCParticleCollectionIterator(int index, const MCParticleObjPointerContainer* collection) : m_index(index), m_object(nullptr), m_collection(collection) {}

    bool operator!=(const MCParticleCollectionIterator& x) const {
      return m_index != x.m_index; //TODO: may not be complete
    }

    const MCParticle operator*() const;
    const MCParticle* operator->() const;
    const MCParticleCollectionIterator& operator++() const;

  private:
    mutable int m_index;
    mutable MCParticle m_object;
    const MCParticleObjPointerContainer* m_collection;
};

/**
A Collection is identified by an ID.
*/

class MCParticleCollection : public podio::CollectionBase {

public:
  typedef const MCParticleCollectionIterator const_iterator;

  MCParticleCollection();
//  MCParticleCollection(const MCParticleCollection& ) = delete; // deletion doesn't work w/ ROOT IO ! :-(
//  MCParticleCollection(MCParticleVector* data, int collectionID);
  ~MCParticleCollection();

  void clear();
  /// Append a new object to the collection, and return this object.
  MCParticle create();

  /// Append a new object to the collection, and return this object.
  /// Initialized with the parameters given
  template<typename... Args>
  MCParticle create(Args&&... args);
  int size() const;

  /// Returns the object of given index
  const MCParticle operator[](unsigned int index) const;
  /// Returns the object of given index
  const MCParticle at(unsigned int index) const;


  /// Append object to the collection
  void push_back(ConstMCParticle object);

  void prepareForWrite();
  void prepareAfterRead();
  void setBuffer(void* address);
  bool setReferences(const podio::ICollectionProvider* collectionProvider);

  podio::CollRefCollection* referenceCollections() { return &m_refCollections;};

  void setID(unsigned ID){
    m_collectionID = ID;
    std::for_each(m_entries.begin(),m_entries.end(),
                 [ID](MCParticleObj* obj){obj->id = {obj->id.index,static_cast<int>(ID)}; }
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
  std::vector<MCParticleData>* _getBuffer() { return m_data;};

    template<size_t arraysize>
  const std::array<fcc::BareParticle,arraysize> core() const;


private:
  bool m_isValid;
  int m_collectionID;
  MCParticleObjPointerContainer m_entries;
  // members to handle 1-to-N-relations
  std::vector<fcc::ConstGenVertex>* m_rel_startVertex; ///< Relation buffer for read / write
  std::vector<fcc::ConstGenVertex>* m_rel_endVertex; ///< Relation buffer for read / write

  // members to handle streaming
  podio::CollRefCollection m_refCollections;
  MCParticleDataContainer* m_data;
};

template<typename... Args>
MCParticle  MCParticleCollection::create(Args&&... args){
  int size = m_entries.size();
  auto obj = new MCParticleObj({size,m_collectionID},{args...});
  m_entries.push_back(obj);
  return MCParticle(obj);
}

template<size_t arraysize>
const std::array<class fcc::BareParticle,arraysize> MCParticleCollection::core() const {
  std::array<class fcc::BareParticle,arraysize> tmp;
  auto valid_size = std::min(arraysize,m_entries.size());
  for (unsigned i = 0; i<valid_size; ++i){
    tmp[i] = m_entries[i]->data.core;
 }
 return tmp;
}

} // namespace fcc
#endif
