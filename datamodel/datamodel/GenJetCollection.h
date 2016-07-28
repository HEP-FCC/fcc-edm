//AUTOMATICALLY GENERATED - DO NOT EDIT

#ifndef GenJetCollection_H
#define  GenJetCollection_H

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
#include "GenJetData.h"
#include "GenJet.h"
#include "GenJetObj.h"

namespace fcc {
typedef std::vector<GenJetData> GenJetDataContainer;
typedef std::deque<GenJetObj*> GenJetObjPointerContainer;

class GenJetCollectionIterator {

  public:
    GenJetCollectionIterator(int index, const GenJetObjPointerContainer* collection) : m_index(index), m_object(nullptr), m_collection(collection) {}

    bool operator!=(const GenJetCollectionIterator& x) const {
      return m_index != x.m_index; //TODO: may not be complete
    }

    const GenJet operator*() const;
    const GenJet* operator->() const;
    const GenJetCollectionIterator& operator++() const;

  private:
    mutable int m_index;
    mutable GenJet m_object;
    const GenJetObjPointerContainer* m_collection;
};

/**
A Collection is identified by an ID.
*/

class GenJetCollection : public podio::CollectionBase {

public:
  typedef const GenJetCollectionIterator const_iterator;

  GenJetCollection();
//  GenJetCollection(const GenJetCollection& ) = delete; // deletion doesn't work w/ ROOT IO ! :-(
//  GenJetCollection(GenJetVector* data, int collectionID);
  ~GenJetCollection();

  void clear();
  /// Append a new object to the collection, and return this object.
  GenJet create();

  /// Append a new object to the collection, and return this object.
  /// Initialized with the parameters given
  template<typename... Args>
  GenJet create(Args&&... args);
  int size() const;

  /// Returns the object of given index
  const GenJet operator[](unsigned int index) const;
  /// Returns the object of given index
  const GenJet at(unsigned int index) const;


  /// Append object to the collection
  void push_back(ConstGenJet object);

  void prepareForWrite();
  void prepareAfterRead();
  void setBuffer(void* address);
  bool setReferences(const podio::ICollectionProvider* collectionProvider);

  podio::CollRefCollection* referenceCollections() { return &m_refCollections;};

  void setID(unsigned ID){
    m_collectionID = ID;
    std::for_each(m_entries.begin(),m_entries.end(),
                 [ID](GenJetObj* obj){obj->id = {obj->id.index,static_cast<int>(ID)}; }
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
  std::vector<GenJetData>* _getBuffer() { return m_data;};

    template<size_t arraysize>
  const std::array<fcc::BareJet,arraysize> core() const;


private:
  bool m_isValid;
  int m_collectionID;
  GenJetObjPointerContainer m_entries;
  // members to handle 1-to-N-relations
  std::vector<fcc::ConstMCParticle>* m_rel_particles; ///< Relation buffer for read / write
  std::vector<std::vector<fcc::ConstMCParticle>*> m_rel_particles_tmp; ///< Relation buffer for internal book-keeping

  // members to handle streaming
  podio::CollRefCollection m_refCollections;
  GenJetDataContainer* m_data;
};

template<typename... Args>
GenJet  GenJetCollection::create(Args&&... args){
  int size = m_entries.size();
  auto obj = new GenJetObj({size,m_collectionID},{args...});
  m_entries.push_back(obj);
  return GenJet(obj);
}

template<size_t arraysize>
const std::array<class fcc::BareJet,arraysize> GenJetCollection::core() const {
  std::array<class fcc::BareJet,arraysize> tmp;
  auto valid_size = std::min(arraysize,m_entries.size());
  for (unsigned i = 0; i<valid_size; ++i){
    tmp[i] = m_entries[i]->data.core;
 }
 return tmp;
}

} // namespace fcc
#endif
