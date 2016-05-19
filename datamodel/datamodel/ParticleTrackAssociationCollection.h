//AUTOMATICALLY GENERATED - DO NOT EDIT

#ifndef ParticleTrackAssociationCollection_H
#define  ParticleTrackAssociationCollection_H

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
#include "ParticleTrackAssociationData.h"
#include "ParticleTrackAssociation.h"
#include "ParticleTrackAssociationObj.h"

namespace fcc {
typedef std::vector<ParticleTrackAssociationData> ParticleTrackAssociationDataContainer;
typedef std::deque<ParticleTrackAssociationObj*> ParticleTrackAssociationObjPointerContainer;

class ParticleTrackAssociationCollectionIterator {

  public:
    ParticleTrackAssociationCollectionIterator(int index, const ParticleTrackAssociationObjPointerContainer* collection) : m_index(index), m_object(nullptr), m_collection(collection) {}

    bool operator!=(const ParticleTrackAssociationCollectionIterator& x) const {
      return m_index != x.m_index; //TODO: may not be complete
    }

    const ParticleTrackAssociation operator*() const;
    const ParticleTrackAssociation* operator->() const;
    const ParticleTrackAssociationCollectionIterator& operator++() const;

  private:
    mutable int m_index;
    mutable ParticleTrackAssociation m_object;
    const ParticleTrackAssociationObjPointerContainer* m_collection;
};

/**
A Collection is identified by an ID.
*/

class ParticleTrackAssociationCollection : public podio::CollectionBase {

public:
  typedef const ParticleTrackAssociationCollectionIterator const_iterator;

  ParticleTrackAssociationCollection();
//  ParticleTrackAssociationCollection(const ParticleTrackAssociationCollection& ) = delete; // deletion doesn't work w/ ROOT IO ! :-(
//  ParticleTrackAssociationCollection(ParticleTrackAssociationVector* data, int collectionID);
  ~ParticleTrackAssociationCollection();

  void clear();
  /// Append a new object to the collection, and return this object.
  ParticleTrackAssociation create();

  /// Append a new object to the collection, and return this object.
  /// Initialized with the parameters given
  template<typename... Args>
  ParticleTrackAssociation create(Args&&... args);
  int size() const;

  /// Returns the object of given index
  const ParticleTrackAssociation operator[](unsigned int index) const;
  /// Returns the object of given index
  const ParticleTrackAssociation at(unsigned int index) const;


  /// Append object to the collection
  void push_back(ConstParticleTrackAssociation object);

  void prepareForWrite();
  void prepareAfterRead();
  void setBuffer(void* address);
  bool setReferences(const podio::ICollectionProvider* collectionProvider);

  podio::CollRefCollection* referenceCollections() { return &m_refCollections;};

  void setID(unsigned ID){
    m_collectionID = ID;
    std::for_each(m_entries.begin(),m_entries.end(),
                 [ID](ParticleTrackAssociationObj* obj){obj->id = {obj->id.index,static_cast<int>(ID)}; }
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
  std::vector<ParticleTrackAssociationData>* _getBuffer() { return m_data;};

   

private:
  bool m_isValid;
  int m_collectionID;
  ParticleTrackAssociationObjPointerContainer m_entries;
  // members to handle 1-to-N-relations
  std::vector<fcc::ConstParticle>* m_rel_Particle; ///< Relation buffer for read / write
  std::vector<fcc::ConstTrack>* m_rel_Track; ///< Relation buffer for read / write

  // members to handle streaming
  podio::CollRefCollection m_refCollections;
  ParticleTrackAssociationDataContainer* m_data;
};

template<typename... Args>
ParticleTrackAssociation  ParticleTrackAssociationCollection::create(Args&&... args){
  int size = m_entries.size();
  auto obj = new ParticleTrackAssociationObj({size,m_collectionID},{args...});
  m_entries.push_back(obj);
  return ParticleTrackAssociation(obj);
}


} // namespace fcc
#endif
