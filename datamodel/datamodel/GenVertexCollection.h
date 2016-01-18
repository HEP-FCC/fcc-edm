//AUTOMATICALLY GENERATED - DO NOT EDIT

#ifndef GenVertexCollection_H
#define  GenVertexCollection_H

#include <string>
#include <vector>
#include <deque>
#include <array>

// podio specific includes
#include "podio/ICollectionProvider.h"
#include "podio/CollectionBase.h"
#include "podio/CollectionIDTable.h"

// datamodel specific includes
#include "GenVertexData.h"
#include "GenVertex.h"
#include "GenVertexObj.h"


typedef std::vector<GenVertexData> GenVertexDataContainer;
typedef std::deque<GenVertexObj*> GenVertexObjPointerContainer;

class GenVertexCollectionIterator {

  public:
    GenVertexCollectionIterator(int index, const GenVertexObjPointerContainer* collection) : m_index(index), m_object(nullptr), m_collection(collection) {}

    bool operator!=(const GenVertexCollectionIterator& x) const {
      return m_index != x.m_index; //TODO: may not be complete
    }

    const GenVertex operator*() const;
    const GenVertex* operator->() const;
    const GenVertexCollectionIterator& operator++() const;

  private:
    mutable int m_index;
    mutable GenVertex m_object;
    const GenVertexObjPointerContainer* m_collection;
};

/**
A Collection is identified by an ID.
*/

class GenVertexCollection : public podio::CollectionBase {

public:
  typedef const GenVertexCollectionIterator const_iterator;

  GenVertexCollection();
//  GenVertexCollection(const GenVertexCollection& ) = delete; // deletion doesn't work w/ ROOT IO ! :-(
//  GenVertexCollection(GenVertexVector* data, int collectionID);
  ~GenVertexCollection(){};

  void clear();
  /// Append a new object to the collection, and return this object.
  GenVertex create();

  /// Append a new object to the collection, and return this object.
  /// Initialized with the parameters given
  template<typename... Args>
  GenVertex create(Args&&... args);
  int size() const;

  /// Returns the object of given index
  const GenVertex operator[](unsigned int index) const;
  /// Returns the object of given index
  const GenVertex at(unsigned int index) const;


  /// Append object to the collection
  void push_back(ConstGenVertex object);

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
  std::vector<GenVertexData>* _getBuffer() { return m_data;};

     template<size_t arraysize>  
  const std::array<Point,arraysize> Position() const;
  template<size_t arraysize>  
  const std::array<float,arraysize> Ctau() const;


private:
  int m_collectionID;
  GenVertexObjPointerContainer m_entries;
  // members to handle 1-to-N-relations

  // members to handle streaming
  podio::CollRefCollection* m_refCollections;
  GenVertexDataContainer* m_data;
};

template<typename... Args>
GenVertex  GenVertexCollection::create(Args&&... args){
  int size = m_entries.size();
  auto obj = new GenVertexObj({size,m_collectionID},{args...});
  m_entries.push_back(obj);
  return GenVertex(obj);
}

template<size_t arraysize>
const std::array<class Point,arraysize> GenVertexCollection::Position() const {
  std::array<class Point,arraysize> tmp;
  auto valid_size = std::min(arraysize,m_entries.size());
  for (unsigned i = 0; i<valid_size; ++i){
    tmp[i] = m_entries[i]->data.Position;
 }
 return tmp;
}
template<size_t arraysize>
const std::array<float,arraysize> GenVertexCollection::Ctau() const {
  std::array<float,arraysize> tmp;
  auto valid_size = std::min(arraysize,m_entries.size());
  for (unsigned i = 0; i<valid_size; ++i){
    tmp[i] = m_entries[i]->data.Ctau;
 }
 return tmp;
}


#endif
