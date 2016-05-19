//AUTOMATICALLY GENERATED - DO NOT EDIT

#ifndef GenJetParticleAssociationCollection_H
#define  GenJetParticleAssociationCollection_H

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
#include "GenJetParticleAssociationData.h"
#include "GenJetParticleAssociation.h"
#include "GenJetParticleAssociationObj.h"

namespace fcc {
typedef std::vector<GenJetParticleAssociationData> GenJetParticleAssociationDataContainer;
typedef std::deque<GenJetParticleAssociationObj*> GenJetParticleAssociationObjPointerContainer;

class GenJetParticleAssociationCollectionIterator {

  public:
    GenJetParticleAssociationCollectionIterator(int index, const GenJetParticleAssociationObjPointerContainer* collection) : m_index(index), m_object(nullptr), m_collection(collection) {}

    bool operator!=(const GenJetParticleAssociationCollectionIterator& x) const {
      return m_index != x.m_index; //TODO: may not be complete
    }

    const GenJetParticleAssociation operator*() const;
    const GenJetParticleAssociation* operator->() const;
    const GenJetParticleAssociationCollectionIterator& operator++() const;

  private:
    mutable int m_index;
    mutable GenJetParticleAssociation m_object;
    const GenJetParticleAssociationObjPointerContainer* m_collection;
};

/**
A Collection is identified by an ID.
*/

class GenJetParticleAssociationCollection : public podio::CollectionBase {

public:
  typedef const GenJetParticleAssociationCollectionIterator const_iterator;

  GenJetParticleAssociationCollection();
//  GenJetParticleAssociationCollection(const GenJetParticleAssociationCollection& ) = delete; // deletion doesn't work w/ ROOT IO ! :-(
//  GenJetParticleAssociationCollection(GenJetParticleAssociationVector* data, int collectionID);
  ~GenJetParticleAssociationCollection();

  void clear();
  /// Append a new object to the collection, and return this object.
  GenJetParticleAssociation create();

  /// Append a new object to the collection, and return this object.
  /// Initialized with the parameters given
  template<typename... Args>
  GenJetParticleAssociation create(Args&&... args);
  int size() const;

  /// Returns the object of given index
  const GenJetParticleAssociation operator[](unsigned int index) const;
  /// Returns the object of given index
  const GenJetParticleAssociation at(unsigned int index) const;


  /// Append object to the collection
  void push_back(ConstGenJetParticleAssociation object);

  void prepareForWrite();
  void prepareAfterRead();
  void setBuffer(void* address);
  bool setReferences(const podio::ICollectionProvider* collectionProvider);

  podio::CollRefCollection* referenceCollections() { return &m_refCollections;};

  void setID(unsigned ID){
    m_collectionID = ID;
    std::for_each(m_entries.begin(),m_entries.end(),
                 [ID](GenJetParticleAssociationObj* obj){obj->id = {obj->id.index,static_cast<int>(ID)}; }
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
  std::vector<GenJetParticleAssociationData>* _getBuffer() { return m_data;};

   

private:
  bool m_isValid;
  int m_collectionID;
  GenJetParticleAssociationObjPointerContainer m_entries;
  // members to handle 1-to-N-relations
  std::vector<fcc::ConstGenJet>* m_rel_Jet; ///< Relation buffer for read / write
  std::vector<fcc::ConstMCParticle>* m_rel_Particle; ///< Relation buffer for read / write

  // members to handle streaming
  podio::CollRefCollection m_refCollections;
  GenJetParticleAssociationDataContainer* m_data;
};

template<typename... Args>
GenJetParticleAssociation  GenJetParticleAssociationCollection::create(Args&&... args){
  int size = m_entries.size();
  auto obj = new GenJetParticleAssociationObj({size,m_collectionID},{args...});
  m_entries.push_back(obj);
  return GenJetParticleAssociation(obj);
}


} // namespace fcc
#endif
