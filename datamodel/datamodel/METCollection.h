//AUTOMATICALLY GENERATED - DO NOT EDIT

#ifndef METCollection_H
#define  METCollection_H

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
#include "METData.h"
#include "MET.h"
#include "METObj.h"

namespace fcc {
typedef std::vector<METData> METDataContainer;
typedef std::deque<METObj*> METObjPointerContainer;

class METCollectionIterator {

  public:
    METCollectionIterator(int index, const METObjPointerContainer* collection) : m_index(index), m_object(nullptr), m_collection(collection) {}

    bool operator!=(const METCollectionIterator& x) const {
      return m_index != x.m_index; //TODO: may not be complete
    }

    const MET operator*() const;
    const MET* operator->() const;
    const METCollectionIterator& operator++() const;

  private:
    mutable int m_index;
    mutable MET m_object;
    const METObjPointerContainer* m_collection;
};

/**
A Collection is identified by an ID.
*/

class METCollection : public podio::CollectionBase {

public:
  typedef const METCollectionIterator const_iterator;

  METCollection();
//  METCollection(const METCollection& ) = delete; // deletion doesn't work w/ ROOT IO ! :-(
//  METCollection(METVector* data, int collectionID);
  ~METCollection();

  void clear();
  /// Append a new object to the collection, and return this object.
  MET create();

  /// Append a new object to the collection, and return this object.
  /// Initialized with the parameters given
  template<typename... Args>
  MET create(Args&&... args);
  int size() const;

  /// Returns the object of given index
  const MET operator[](unsigned int index) const;
  /// Returns the object of given index
  const MET at(unsigned int index) const;


  /// Append object to the collection
  void push_back(ConstMET object);

  void prepareForWrite();
  void prepareAfterRead();
  void setBuffer(void* address);
  bool setReferences(const podio::ICollectionProvider* collectionProvider);

  podio::CollRefCollection* referenceCollections() { return &m_refCollections;};

  void setID(unsigned ID){
    m_collectionID = ID;
    std::for_each(m_entries.begin(),m_entries.end(),
                 [ID](METObj* obj){obj->id = {obj->id.index,static_cast<int>(ID)}; }
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
  std::vector<METData>* _getBuffer() { return m_data;};

    template<size_t arraysize>
  const std::array<float,arraysize> magnitude() const;
  template<size_t arraysize>
  const std::array<float,arraysize> phi() const;
  template<size_t arraysize>
  const std::array<float,arraysize> scalarSum() const;


private:
  bool m_isValid;
  int m_collectionID;
  METObjPointerContainer m_entries;
  // members to handle 1-to-N-relations

  // members to handle streaming
  podio::CollRefCollection m_refCollections;
  METDataContainer* m_data;
};

template<typename... Args>
MET  METCollection::create(Args&&... args){
  int size = m_entries.size();
  auto obj = new METObj({size,m_collectionID},{args...});
  m_entries.push_back(obj);
  return MET(obj);
}

template<size_t arraysize>
const std::array<float,arraysize> METCollection::magnitude() const {
  std::array<float,arraysize> tmp;
  auto valid_size = std::min(arraysize,m_entries.size());
  for (unsigned i = 0; i<valid_size; ++i){
    tmp[i] = m_entries[i]->data.magnitude;
 }
 return tmp;
}
template<size_t arraysize>
const std::array<float,arraysize> METCollection::phi() const {
  std::array<float,arraysize> tmp;
  auto valid_size = std::min(arraysize,m_entries.size());
  for (unsigned i = 0; i<valid_size; ++i){
    tmp[i] = m_entries[i]->data.phi;
 }
 return tmp;
}
template<size_t arraysize>
const std::array<float,arraysize> METCollection::scalarSum() const {
  std::array<float,arraysize> tmp;
  auto valid_size = std::min(arraysize,m_entries.size());
  for (unsigned i = 0; i<valid_size; ++i){
    tmp[i] = m_entries[i]->data.scalarSum;
 }
 return tmp;
}

} // namespace fcc
#endif
