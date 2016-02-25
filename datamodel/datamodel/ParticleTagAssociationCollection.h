//AUTOMATICALLY GENERATED - DO NOT EDIT

#ifndef ParticleTagAssociationCollection_H
#define  ParticleTagAssociationCollection_H

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
#include "ParticleTagAssociationData.h"
#include "ParticleTagAssociation.h"
#include "ParticleTagAssociationObj.h"

namespace fcc {
typedef std::vector<ParticleTagAssociationData> ParticleTagAssociationDataContainer;
typedef std::deque<ParticleTagAssociationObj*> ParticleTagAssociationObjPointerContainer;

class ParticleTagAssociationCollectionIterator {

  public:
    ParticleTagAssociationCollectionIterator(int index, const ParticleTagAssociationObjPointerContainer* collection) : m_index(index), m_object(nullptr), m_collection(collection) {}

    bool operator!=(const ParticleTagAssociationCollectionIterator& x) const {
      return m_index != x.m_index; //TODO: may not be complete
    }

    const ParticleTagAssociation operator*() const;
    const ParticleTagAssociation* operator->() const;
    const ParticleTagAssociationCollectionIterator& operator++() const;

  private:
    mutable int m_index;
    mutable ParticleTagAssociation m_object;
    const ParticleTagAssociationObjPointerContainer* m_collection;
};

/**
A Collection is identified by an ID.
*/

class ParticleTagAssociationCollection : public podio::CollectionBase {

public:
  typedef const ParticleTagAssociationCollectionIterator const_iterator;

  ParticleTagAssociationCollection();
//  ParticleTagAssociationCollection(const ParticleTagAssociationCollection& ) = delete; // deletion doesn't work w/ ROOT IO ! :-(
//  ParticleTagAssociationCollection(ParticleTagAssociationVector* data, int collectionID);
  ~ParticleTagAssociationCollection(){};

  void clear();
  /// Append a new object to the collection, and return this object.
  ParticleTagAssociation create();

  /// Append a new object to the collection, and return this object.
  /// Initialized with the parameters given
  template<typename... Args>
  ParticleTagAssociation create(Args&&... args);
  int size() const;

  /// Returns the object of given index
  const ParticleTagAssociation operator[](unsigned int index) const;
  /// Returns the object of given index
  const ParticleTagAssociation at(unsigned int index) const;


  /// Append object to the collection
  void push_back(ConstParticleTagAssociation object);

  void prepareForWrite();
  void prepareAfterRead();
  void setBuffer(void* address);
  bool setReferences(const podio::ICollectionProvider* collectionProvider);

  podio::CollRefCollection* referenceCollections() { return m_refCollections;};

  void setID(unsigned ID){
    m_collectionID = ID;
    std::for_each(m_entries.begin(),m_entries.end(),
                 [ID](ParticleTagAssociationObj* obj){obj->id = {obj->id.index,static_cast<int>(ID)}; }
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
  std::vector<ParticleTagAssociationData>* _getBuffer() { return m_data;};

   

private:
  int m_collectionID;
  ParticleTagAssociationObjPointerContainer m_entries;
  // members to handle 1-to-N-relations
  std::vector<::fcc::ConstParticle>* m_rel_Particle; //relation buffer for r/w
  std::vector<::fcc::ConstTag>* m_rel_Tag; //relation buffer for r/w

  // members to handle streaming
  podio::CollRefCollection* m_refCollections;
  ParticleTagAssociationDataContainer* m_data;
};

template<typename... Args>
ParticleTagAssociation  ParticleTagAssociationCollection::create(Args&&... args){
  int size = m_entries.size();
  auto obj = new ParticleTagAssociationObj({size,m_collectionID},{args...});
  m_entries.push_back(obj);
  return ParticleTagAssociation(obj);
}


} // namespace fcc
#endif
