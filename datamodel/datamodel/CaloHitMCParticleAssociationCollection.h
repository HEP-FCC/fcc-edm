//AUTOMATICALLY GENERATED - DO NOT EDIT

#ifndef CaloHitMCParticleAssociationCollection_H
#define  CaloHitMCParticleAssociationCollection_H

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
#include "CaloHitMCParticleAssociationData.h"
#include "CaloHitMCParticleAssociation.h"
#include "CaloHitMCParticleAssociationObj.h"

namespace fcc {
typedef std::vector<CaloHitMCParticleAssociationData> CaloHitMCParticleAssociationDataContainer;
typedef std::deque<CaloHitMCParticleAssociationObj*> CaloHitMCParticleAssociationObjPointerContainer;

class CaloHitMCParticleAssociationCollectionIterator {

  public:
    CaloHitMCParticleAssociationCollectionIterator(int index, const CaloHitMCParticleAssociationObjPointerContainer* collection) : m_index(index), m_object(nullptr), m_collection(collection) {}

    bool operator!=(const CaloHitMCParticleAssociationCollectionIterator& x) const {
      return m_index != x.m_index; //TODO: may not be complete
    }

    const CaloHitMCParticleAssociation operator*() const;
    const CaloHitMCParticleAssociation* operator->() const;
    const CaloHitMCParticleAssociationCollectionIterator& operator++() const;

  private:
    mutable int m_index;
    mutable CaloHitMCParticleAssociation m_object;
    const CaloHitMCParticleAssociationObjPointerContainer* m_collection;
};

/**
A Collection is identified by an ID.
*/

class CaloHitMCParticleAssociationCollection : public podio::CollectionBase {

public:
  typedef const CaloHitMCParticleAssociationCollectionIterator const_iterator;

  CaloHitMCParticleAssociationCollection();
//  CaloHitMCParticleAssociationCollection(const CaloHitMCParticleAssociationCollection& ) = delete; // deletion doesn't work w/ ROOT IO ! :-(
//  CaloHitMCParticleAssociationCollection(CaloHitMCParticleAssociationVector* data, int collectionID);
  ~CaloHitMCParticleAssociationCollection();

  void clear();
  /// Append a new object to the collection, and return this object.
  CaloHitMCParticleAssociation create();

  /// Append a new object to the collection, and return this object.
  /// Initialized with the parameters given
  template<typename... Args>
  CaloHitMCParticleAssociation create(Args&&... args);
  int size() const;

  /// Returns the object of given index
  const CaloHitMCParticleAssociation operator[](unsigned int index) const;
  /// Returns the object of given index
  const CaloHitMCParticleAssociation at(unsigned int index) const;


  /// Append object to the collection
  void push_back(ConstCaloHitMCParticleAssociation object);

  void prepareForWrite();
  void prepareAfterRead();
  void setBuffer(void* address);
  bool setReferences(const podio::ICollectionProvider* collectionProvider);

  podio::CollRefCollection* referenceCollections() { return &m_refCollections;};

  void setID(unsigned ID){
    m_collectionID = ID;
    std::for_each(m_entries.begin(),m_entries.end(),
                 [ID](CaloHitMCParticleAssociationObj* obj){obj->id = {obj->id.index,static_cast<int>(ID)}; }
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
  std::vector<CaloHitMCParticleAssociationData>* _getBuffer() { return m_data;};

    template<size_t arraysize>
  const std::array<float,arraysize> fraction() const;


private:
  bool m_isValid;
  int m_collectionID;
  CaloHitMCParticleAssociationObjPointerContainer m_entries;
  // members to handle 1-to-N-relations
  std::vector<fcc::ConstCaloHit>* m_rel_hit; ///< Relation buffer for read / write
  std::vector<fcc::ConstMCParticle>* m_rel_particle; ///< Relation buffer for read / write

  // members to handle streaming
  podio::CollRefCollection m_refCollections;
  CaloHitMCParticleAssociationDataContainer* m_data;
};

template<typename... Args>
CaloHitMCParticleAssociation  CaloHitMCParticleAssociationCollection::create(Args&&... args){
  int size = m_entries.size();
  auto obj = new CaloHitMCParticleAssociationObj({size,m_collectionID},{args...});
  m_entries.push_back(obj);
  return CaloHitMCParticleAssociation(obj);
}

template<size_t arraysize>
const std::array<float,arraysize> CaloHitMCParticleAssociationCollection::fraction() const {
  std::array<float,arraysize> tmp;
  auto valid_size = std::min(arraysize,m_entries.size());
  for (unsigned i = 0; i<valid_size; ++i){
    tmp[i] = m_entries[i]->data.fraction;
 }
 return tmp;
}

} // namespace fcc
#endif
