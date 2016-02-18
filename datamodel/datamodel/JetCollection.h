//AUTOMATICALLY GENERATED - DO NOT EDIT

#ifndef JetCollection_H
#define  JetCollection_H

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
#include "JetData.h"
#include "Jet.h"
#include "JetObj.h"

namespace fcc {
typedef std::vector<JetData> JetDataContainer;
typedef std::deque<JetObj*> JetObjPointerContainer;

class JetCollectionIterator {

  public:
    JetCollectionIterator(int index, const JetObjPointerContainer* collection) : m_index(index), m_object(nullptr), m_collection(collection) {}

    bool operator!=(const JetCollectionIterator& x) const {
      return m_index != x.m_index; //TODO: may not be complete
    }

    const Jet operator*() const;
    const Jet* operator->() const;
    const JetCollectionIterator& operator++() const;

  private:
    mutable int m_index;
    mutable Jet m_object;
    const JetObjPointerContainer* m_collection;
};

/**
A Collection is identified by an ID.
*/

class JetCollection : public podio::CollectionBase {

public:
  typedef const JetCollectionIterator const_iterator;

  JetCollection();
//  JetCollection(const JetCollection& ) = delete; // deletion doesn't work w/ ROOT IO ! :-(
//  JetCollection(JetVector* data, int collectionID);
  ~JetCollection(){};

  void clear();
  /// Append a new object to the collection, and return this object.
  Jet create();

  /// Append a new object to the collection, and return this object.
  /// Initialized with the parameters given
  template<typename... Args>
  Jet create(Args&&... args);
  int size() const;

  /// Returns the object of given index
  const Jet operator[](unsigned int index) const;
  /// Returns the object of given index
  const Jet at(unsigned int index) const;


  /// Append object to the collection
  void push_back(ConstJet object);

  void prepareForWrite();
  void prepareAfterRead();
  void setBuffer(void* address);
  bool setReferences(const podio::ICollectionProvider* collectionProvider);

  podio::CollRefCollection* referenceCollections() { return m_refCollections;};

  void setID(unsigned ID){
    m_collectionID = ID;
    std::for_each(m_entries.begin(),m_entries.end(),
                 [ID](JetObj* obj){obj->id = {obj->id.index,static_cast<int>(ID)}; }
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
  std::vector<JetData>* _getBuffer() { return m_data;};

     template<size_t arraysize>  
  const std::array<fcc::BareJet,arraysize> Core() const;


private:
  int m_collectionID;
  JetObjPointerContainer m_entries;
  // members to handle 1-to-N-relations

  // members to handle streaming
  podio::CollRefCollection* m_refCollections;
  JetDataContainer* m_data;
};

template<typename... Args>
Jet  JetCollection::create(Args&&... args){
  int size = m_entries.size();
  auto obj = new JetObj({size,m_collectionID},{args...});
  m_entries.push_back(obj);
  return Jet(obj);
}

template<size_t arraysize>
const std::array<class fcc::BareJet,arraysize> JetCollection::Core() const {
  std::array<class fcc::BareJet,arraysize> tmp;
  auto valid_size = std::min(arraysize,m_entries.size());
  for (unsigned i = 0; i<valid_size; ++i){
    tmp[i] = m_entries[i]->data.Core;
 }
 return tmp;
}

} // namespace fcc
#endif
