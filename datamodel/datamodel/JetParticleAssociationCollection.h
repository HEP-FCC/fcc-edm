//AUTOMATICALLY GENERATED - DO NOT EDIT

#ifndef JetParticleAssociationCollection_H
#define  JetParticleAssociationCollection_H

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
#include "JetParticleAssociationData.h"
#include "JetParticleAssociation.h"
#include "JetParticleAssociationObj.h"

namespace fcc {
typedef std::vector<JetParticleAssociationData> JetParticleAssociationDataContainer;
typedef std::deque<JetParticleAssociationObj*> JetParticleAssociationObjPointerContainer;

class JetParticleAssociationCollectionIterator {

  public:
    JetParticleAssociationCollectionIterator(int index, const JetParticleAssociationObjPointerContainer* collection) : m_index(index), m_object(nullptr), m_collection(collection) {}

    bool operator!=(const JetParticleAssociationCollectionIterator& x) const {
      return m_index != x.m_index; //TODO: may not be complete
    }

    const JetParticleAssociation operator*() const;
    const JetParticleAssociation* operator->() const;
    const JetParticleAssociationCollectionIterator& operator++() const;

  private:
    mutable int m_index;
    mutable JetParticleAssociation m_object;
    const JetParticleAssociationObjPointerContainer* m_collection;
};

/**
A Collection is identified by an ID.
*/

class JetParticleAssociationCollection : public podio::CollectionBase {

public:
  typedef const JetParticleAssociationCollectionIterator const_iterator;

  JetParticleAssociationCollection();
//  JetParticleAssociationCollection(const JetParticleAssociationCollection& ) = delete; // deletion doesn't work w/ ROOT IO ! :-(
//  JetParticleAssociationCollection(JetParticleAssociationVector* data, int collectionID);
  ~JetParticleAssociationCollection(){};

  void clear();
  /// Append a new object to the collection, and return this object.
  JetParticleAssociation create();

  /// Append a new object to the collection, and return this object.
  /// Initialized with the parameters given
  template<typename... Args>
  JetParticleAssociation create(Args&&... args);
  int size() const;

  /// Returns the object of given index
  const JetParticleAssociation operator[](unsigned int index) const;
  /// Returns the object of given index
  const JetParticleAssociation at(unsigned int index) const;


  /// Append object to the collection
  void push_back(ConstJetParticleAssociation object);

  void prepareForWrite();
  void prepareAfterRead();
  void setBuffer(void* address);
  bool setReferences(const podio::ICollectionProvider* collectionProvider);

  podio::CollRefCollection* referenceCollections() { return m_refCollections;};

  void setID(unsigned ID){
    m_collectionID = ID;
    std::for_each(m_entries.begin(),m_entries.end(),
                 [ID](JetParticleAssociationObj* obj){obj->id = {obj->id.index,static_cast<int>(ID)}; }
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
  std::vector<JetParticleAssociationData>* _getBuffer() { return m_data;};

   

private:
  int m_collectionID;
  JetParticleAssociationObjPointerContainer m_entries;
  // members to handle 1-to-N-relations
  std::vector<::fcc::ConstJet>* m_rel_Jet; //relation buffer for r/w
  std::vector<::fcc::ConstParticle>* m_rel_Particle; //relation buffer for r/w

  // members to handle streaming
  podio::CollRefCollection* m_refCollections;
  JetParticleAssociationDataContainer* m_data;
};

template<typename... Args>
JetParticleAssociation  JetParticleAssociationCollection::create(Args&&... args){
  int size = m_entries.size();
  auto obj = new JetParticleAssociationObj({size,m_collectionID},{args...});
  m_entries.push_back(obj);
  return JetParticleAssociation(obj);
}


} // namespace fcc
#endif
