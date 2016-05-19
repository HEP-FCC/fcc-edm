//AUTOMATICALLY GENERATED - DO NOT EDIT

#ifndef ParticleClusterAssociationCollection_H
#define  ParticleClusterAssociationCollection_H

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
#include "ParticleClusterAssociationData.h"
#include "ParticleClusterAssociation.h"
#include "ParticleClusterAssociationObj.h"

namespace fcc {
typedef std::vector<ParticleClusterAssociationData> ParticleClusterAssociationDataContainer;
typedef std::deque<ParticleClusterAssociationObj*> ParticleClusterAssociationObjPointerContainer;

class ParticleClusterAssociationCollectionIterator {

  public:
    ParticleClusterAssociationCollectionIterator(int index, const ParticleClusterAssociationObjPointerContainer* collection) : m_index(index), m_object(nullptr), m_collection(collection) {}

    bool operator!=(const ParticleClusterAssociationCollectionIterator& x) const {
      return m_index != x.m_index; //TODO: may not be complete
    }

    const ParticleClusterAssociation operator*() const;
    const ParticleClusterAssociation* operator->() const;
    const ParticleClusterAssociationCollectionIterator& operator++() const;

  private:
    mutable int m_index;
    mutable ParticleClusterAssociation m_object;
    const ParticleClusterAssociationObjPointerContainer* m_collection;
};

/**
A Collection is identified by an ID.
*/

class ParticleClusterAssociationCollection : public podio::CollectionBase {

public:
  typedef const ParticleClusterAssociationCollectionIterator const_iterator;

  ParticleClusterAssociationCollection();
//  ParticleClusterAssociationCollection(const ParticleClusterAssociationCollection& ) = delete; // deletion doesn't work w/ ROOT IO ! :-(
//  ParticleClusterAssociationCollection(ParticleClusterAssociationVector* data, int collectionID);
  ~ParticleClusterAssociationCollection();

  void clear();
  /// Append a new object to the collection, and return this object.
  ParticleClusterAssociation create();

  /// Append a new object to the collection, and return this object.
  /// Initialized with the parameters given
  template<typename... Args>
  ParticleClusterAssociation create(Args&&... args);
  int size() const;

  /// Returns the object of given index
  const ParticleClusterAssociation operator[](unsigned int index) const;
  /// Returns the object of given index
  const ParticleClusterAssociation at(unsigned int index) const;


  /// Append object to the collection
  void push_back(ConstParticleClusterAssociation object);

  void prepareForWrite();
  void prepareAfterRead();
  void setBuffer(void* address);
  bool setReferences(const podio::ICollectionProvider* collectionProvider);

  podio::CollRefCollection* referenceCollections() { return &m_refCollections;};

  void setID(unsigned ID){
    m_collectionID = ID;
    std::for_each(m_entries.begin(),m_entries.end(),
                 [ID](ParticleClusterAssociationObj* obj){obj->id = {obj->id.index,static_cast<int>(ID)}; }
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
  std::vector<ParticleClusterAssociationData>* _getBuffer() { return m_data;};

   

private:
  bool m_isValid;
  int m_collectionID;
  ParticleClusterAssociationObjPointerContainer m_entries;
  // members to handle 1-to-N-relations
  std::vector<fcc::ConstParticle>* m_rel_Particle; ///< Relation buffer for read / write
  std::vector<fcc::ConstCaloCluster>* m_rel_Cluster; ///< Relation buffer for read / write

  // members to handle streaming
  podio::CollRefCollection m_refCollections;
  ParticleClusterAssociationDataContainer* m_data;
};

template<typename... Args>
ParticleClusterAssociation  ParticleClusterAssociationCollection::create(Args&&... args){
  int size = m_entries.size();
  auto obj = new ParticleClusterAssociationObj({size,m_collectionID},{args...});
  m_entries.push_back(obj);
  return ParticleClusterAssociation(obj);
}


} // namespace fcc
#endif
