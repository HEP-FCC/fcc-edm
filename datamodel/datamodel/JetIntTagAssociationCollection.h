//AUTOMATICALLY GENERATED - DO NOT EDIT

#ifndef JetIntTagAssociationCollection_H
#define  JetIntTagAssociationCollection_H

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
#include "JetIntTagAssociationData.h"
#include "JetIntTagAssociation.h"
#include "JetIntTagAssociationObj.h"

namespace fcc {
typedef std::vector<JetIntTagAssociationData> JetIntTagAssociationDataContainer;
typedef std::deque<JetIntTagAssociationObj*> JetIntTagAssociationObjPointerContainer;

class JetIntTagAssociationCollectionIterator {

  public:
    JetIntTagAssociationCollectionIterator(int index, const JetIntTagAssociationObjPointerContainer* collection) : m_index(index), m_object(nullptr), m_collection(collection) {}

    bool operator!=(const JetIntTagAssociationCollectionIterator& x) const {
      return m_index != x.m_index; //TODO: may not be complete
    }

    const JetIntTagAssociation operator*() const;
    const JetIntTagAssociation* operator->() const;
    const JetIntTagAssociationCollectionIterator& operator++() const;

  private:
    mutable int m_index;
    mutable JetIntTagAssociation m_object;
    const JetIntTagAssociationObjPointerContainer* m_collection;
};

/**
A Collection is identified by an ID.
*/

class JetIntTagAssociationCollection : public podio::CollectionBase {

public:
  typedef const JetIntTagAssociationCollectionIterator const_iterator;

  JetIntTagAssociationCollection();
//  JetIntTagAssociationCollection(const JetIntTagAssociationCollection& ) = delete; // deletion doesn't work w/ ROOT IO ! :-(
//  JetIntTagAssociationCollection(JetIntTagAssociationVector* data, int collectionID);
  ~JetIntTagAssociationCollection();

  void clear();
  /// Append a new object to the collection, and return this object.
  JetIntTagAssociation create();

  /// Append a new object to the collection, and return this object.
  /// Initialized with the parameters given
  template<typename... Args>
  JetIntTagAssociation create(Args&&... args);
  int size() const;

  /// Returns the object of given index
  const JetIntTagAssociation operator[](unsigned int index) const;
  /// Returns the object of given index
  const JetIntTagAssociation at(unsigned int index) const;


  /// Append object to the collection
  void push_back(ConstJetIntTagAssociation object);

  void prepareForWrite();
  void prepareAfterRead();
  void setBuffer(void* address);
  bool setReferences(const podio::ICollectionProvider* collectionProvider);

  podio::CollRefCollection* referenceCollections() { return &m_refCollections;};

  void setID(unsigned ID){
    m_collectionID = ID;
    std::for_each(m_entries.begin(),m_entries.end(),
                 [ID](JetIntTagAssociationObj* obj){obj->id = {obj->id.index,static_cast<int>(ID)}; }
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
  std::vector<JetIntTagAssociationData>* _getBuffer() { return m_data;};

   

private:
  bool m_isValid;
  int m_collectionID;
  JetIntTagAssociationObjPointerContainer m_entries;
  // members to handle 1-to-N-relations
  std::vector<fcc::ConstJet>* m_rel_Jet; ///< Relation buffer for read / write
  std::vector<fcc::ConstIntTag>* m_rel_Tag; ///< Relation buffer for read / write

  // members to handle streaming
  podio::CollRefCollection m_refCollections;
  JetIntTagAssociationDataContainer* m_data;
};

template<typename... Args>
JetIntTagAssociation  JetIntTagAssociationCollection::create(Args&&... args){
  int size = m_entries.size();
  auto obj = new JetIntTagAssociationObj({size,m_collectionID},{args...});
  m_entries.push_back(obj);
  return JetIntTagAssociation(obj);
}


} // namespace fcc
#endif
