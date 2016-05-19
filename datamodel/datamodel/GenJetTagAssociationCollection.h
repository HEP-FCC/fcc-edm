//AUTOMATICALLY GENERATED - DO NOT EDIT

#ifndef GenJetTagAssociationCollection_H
#define  GenJetTagAssociationCollection_H

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
#include "GenJetTagAssociationData.h"
#include "GenJetTagAssociation.h"
#include "GenJetTagAssociationObj.h"

namespace fcc {
typedef std::vector<GenJetTagAssociationData> GenJetTagAssociationDataContainer;
typedef std::deque<GenJetTagAssociationObj*> GenJetTagAssociationObjPointerContainer;

class GenJetTagAssociationCollectionIterator {

  public:
    GenJetTagAssociationCollectionIterator(int index, const GenJetTagAssociationObjPointerContainer* collection) : m_index(index), m_object(nullptr), m_collection(collection) {}

    bool operator!=(const GenJetTagAssociationCollectionIterator& x) const {
      return m_index != x.m_index; //TODO: may not be complete
    }

    const GenJetTagAssociation operator*() const;
    const GenJetTagAssociation* operator->() const;
    const GenJetTagAssociationCollectionIterator& operator++() const;

  private:
    mutable int m_index;
    mutable GenJetTagAssociation m_object;
    const GenJetTagAssociationObjPointerContainer* m_collection;
};

/**
A Collection is identified by an ID.
*/

class GenJetTagAssociationCollection : public podio::CollectionBase {

public:
  typedef const GenJetTagAssociationCollectionIterator const_iterator;

  GenJetTagAssociationCollection();
//  GenJetTagAssociationCollection(const GenJetTagAssociationCollection& ) = delete; // deletion doesn't work w/ ROOT IO ! :-(
//  GenJetTagAssociationCollection(GenJetTagAssociationVector* data, int collectionID);
  ~GenJetTagAssociationCollection();

  void clear();
  /// Append a new object to the collection, and return this object.
  GenJetTagAssociation create();

  /// Append a new object to the collection, and return this object.
  /// Initialized with the parameters given
  template<typename... Args>
  GenJetTagAssociation create(Args&&... args);
  int size() const;

  /// Returns the object of given index
  const GenJetTagAssociation operator[](unsigned int index) const;
  /// Returns the object of given index
  const GenJetTagAssociation at(unsigned int index) const;


  /// Append object to the collection
  void push_back(ConstGenJetTagAssociation object);

  void prepareForWrite();
  void prepareAfterRead();
  void setBuffer(void* address);
  bool setReferences(const podio::ICollectionProvider* collectionProvider);

  podio::CollRefCollection* referenceCollections() { return &m_refCollections;};

  void setID(unsigned ID){
    m_collectionID = ID;
    std::for_each(m_entries.begin(),m_entries.end(),
                 [ID](GenJetTagAssociationObj* obj){obj->id = {obj->id.index,static_cast<int>(ID)}; }
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
  std::vector<GenJetTagAssociationData>* _getBuffer() { return m_data;};

   

private:
  bool m_isValid;
  int m_collectionID;
  GenJetTagAssociationObjPointerContainer m_entries;
  // members to handle 1-to-N-relations
  std::vector<fcc::ConstGenJet>* m_rel_Jet; ///< Relation buffer for read / write
  std::vector<fcc::ConstTag>* m_rel_Tag; ///< Relation buffer for read / write

  // members to handle streaming
  podio::CollRefCollection m_refCollections;
  GenJetTagAssociationDataContainer* m_data;
};

template<typename... Args>
GenJetTagAssociation  GenJetTagAssociationCollection::create(Args&&... args){
  int size = m_entries.size();
  auto obj = new GenJetTagAssociationObj({size,m_collectionID},{args...});
  m_entries.push_back(obj);
  return GenJetTagAssociation(obj);
}


} // namespace fcc
#endif
