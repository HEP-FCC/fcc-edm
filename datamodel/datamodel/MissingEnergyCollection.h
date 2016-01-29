//AUTOMATICALLY GENERATED - DO NOT EDIT

#ifndef MissingEnergyCollection_H
#define  MissingEnergyCollection_H

#include <string>
#include <vector>
#include <deque>
#include <array>

// podio specific includes
#include "podio/ICollectionProvider.h"
#include "podio/CollectionBase.h"
#include "podio/CollectionIDTable.h"

// datamodel specific includes
#include "MissingEnergyData.h"
#include "MissingEnergy.h"
#include "MissingEnergyObj.h"

namespace fcc {
typedef std::vector<MissingEnergyData> MissingEnergyDataContainer;
typedef std::deque<MissingEnergyObj*> MissingEnergyObjPointerContainer;

class MissingEnergyCollectionIterator {

  public:
    MissingEnergyCollectionIterator(int index, const MissingEnergyObjPointerContainer* collection) : m_index(index), m_object(nullptr), m_collection(collection) {}

    bool operator!=(const MissingEnergyCollectionIterator& x) const {
      return m_index != x.m_index; //TODO: may not be complete
    }

    const MissingEnergy operator*() const;
    const MissingEnergy* operator->() const;
    const MissingEnergyCollectionIterator& operator++() const;

  private:
    mutable int m_index;
    mutable MissingEnergy m_object;
    const MissingEnergyObjPointerContainer* m_collection;
};

/**
A Collection is identified by an ID.
*/

class MissingEnergyCollection : public podio::CollectionBase {

public:
  typedef const MissingEnergyCollectionIterator const_iterator;

  MissingEnergyCollection();
//  MissingEnergyCollection(const MissingEnergyCollection& ) = delete; // deletion doesn't work w/ ROOT IO ! :-(
//  MissingEnergyCollection(MissingEnergyVector* data, int collectionID);
  ~MissingEnergyCollection(){};

  void clear();
  /// Append a new object to the collection, and return this object.
  MissingEnergy create();

  /// Append a new object to the collection, and return this object.
  /// Initialized with the parameters given
  template<typename... Args>
  MissingEnergy create(Args&&... args);
  int size() const;

  /// Returns the object of given index
  const MissingEnergy operator[](unsigned int index) const;
  /// Returns the object of given index
  const MissingEnergy at(unsigned int index) const;


  /// Append object to the collection
  void push_back(ConstMissingEnergy object);

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
  std::vector<MissingEnergyData>* _getBuffer() { return m_data;};

     template<size_t arraysize>  
  const std::array<float,arraysize> Energy() const;
  template<size_t arraysize>  
  const std::array<float,arraysize> Phi() const;


private:
  int m_collectionID;
  MissingEnergyObjPointerContainer m_entries;
  // members to handle 1-to-N-relations

  // members to handle streaming
  podio::CollRefCollection* m_refCollections;
  MissingEnergyDataContainer* m_data;
};

template<typename... Args>
MissingEnergy  MissingEnergyCollection::create(Args&&... args){
  int size = m_entries.size();
  auto obj = new MissingEnergyObj({size,m_collectionID},{args...});
  m_entries.push_back(obj);
  return MissingEnergy(obj);
}

template<size_t arraysize>
const std::array<float,arraysize> MissingEnergyCollection::Energy() const {
  std::array<float,arraysize> tmp;
  auto valid_size = std::min(arraysize,m_entries.size());
  for (unsigned i = 0; i<valid_size; ++i){
    tmp[i] = m_entries[i]->data.Energy;
 }
 return tmp;
}
template<size_t arraysize>
const std::array<float,arraysize> MissingEnergyCollection::Phi() const {
  std::array<float,arraysize> tmp;
  auto valid_size = std::min(arraysize,m_entries.size());
  for (unsigned i = 0; i<valid_size; ++i){
    tmp[i] = m_entries[i]->data.Phi;
 }
 return tmp;
}

} // namespace fcc
#endif
