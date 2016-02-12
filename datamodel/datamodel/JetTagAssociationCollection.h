//AUTOMATICALLY GENERATED - DO NOT EDIT

#ifndef JetTagAssociationCollection_H
#define  JetTagAssociationCollection_H

#include <string>
#include <vector>
#include <deque>
#include <array>

// podio specific includes
#include "podio/ICollectionProvider.h"
#include "podio/CollectionBase.h"
#include "podio/CollectionIDTable.h"

// datamodel specific includes
#include "JetTagAssociationData.h"
#include "JetTagAssociation.h"
#include "JetTagAssociationObj.h"

namespace fcc {
typedef std::vector<JetTagAssociationData> JetTagAssociationDataContainer;
typedef std::deque<JetTagAssociationObj*> JetTagAssociationObjPointerContainer;

class JetTagAssociationCollectionIterator {

  public:
    JetTagAssociationCollectionIterator(int index, const JetTagAssociationObjPointerContainer* collection) : m_index(index), m_object(nullptr), m_collection(collection) {}

    bool operator!=(const JetTagAssociationCollectionIterator& x) const {
      return m_index != x.m_index; //TODO: may not be complete
    }

    const JetTagAssociation operator*() const;
    const JetTagAssociation* operator->() const;
    const JetTagAssociationCollectionIterator& operator++() const;

  private:
    mutable int m_index;
    mutable JetTagAssociation m_object;
    const JetTagAssociationObjPointerContainer* m_collection;
};

/**
A Collection is identified by an ID.
*/

class JetTagAssociationCollection : public podio::CollectionBase {

public:
  typedef const JetTagAssociationCollectionIterator const_iterator;

  JetTagAssociationCollection();
//  JetTagAssociationCollection(const JetTagAssociationCollection& ) = delete; // deletion doesn't work w/ ROOT IO ! :-(
//  JetTagAssociationCollection(JetTagAssociationVector* data, int collectionID);
  ~JetTagAssociationCollection(){};

  void clear();
  /// Append a new object to the collection, and return this object.
  JetTagAssociation create();

  /// Append a new object to the collection, and return this object.
  /// Initialized with the parameters given
  template<typename... Args>
  JetTagAssociation create(Args&&... args);
  int size() const;

  /// Returns the object of given index
  const JetTagAssociation operator[](unsigned int index) const;
  /// Returns the object of given index
  const JetTagAssociation at(unsigned int index) const;


  /// Append object to the collection
  void push_back(ConstJetTagAssociation object);

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
  std::vector<JetTagAssociationData>* _getBuffer() { return m_data;};

   

private:
  int m_collectionID;
  JetTagAssociationObjPointerContainer m_entries;
  // members to handle 1-to-N-relations
  std::vector<::fcc::ConstJet>* m_rel_Jet; //relation buffer for r/w
  std::vector<::fcc::ConstTag>* m_rel_Tag; //relation buffer for r/w

  // members to handle streaming
  podio::CollRefCollection* m_refCollections;
  JetTagAssociationDataContainer* m_data;
};

template<typename... Args>
JetTagAssociation  JetTagAssociationCollection::create(Args&&... args){
  int size = m_entries.size();
  auto obj = new JetTagAssociationObj({size,m_collectionID},{args...});
  m_entries.push_back(obj);
  return JetTagAssociation(obj);
}


} // namespace fcc
#endif
