//AUTOMATICALLY GENERATED - DO NOT EDIT

#ifndef GenVertexCollection_H
#define  GenVertexCollection_H

#include <string>
#include <vector>
#include <deque>

// albers specific includes
#include "albers/Registry.h"
#include "albers/CollectionBase.h"

// datamodel specific includes
#include "datamodel/GenVertex.h"
#include "datamodel/GenVertexHandle.h"

typedef std::vector<GenVertex> GenVertexVector;
typedef std::vector<GenVertexHandle> GenVertexHandleContainer;

class GenVertexCollectionIterator {

  public:
    GenVertexCollectionIterator(int index, const GenVertexCollection* collection) : m_index(index), m_collection(collection) {}

    bool operator!=(const GenVertexCollectionIterator& x) const {
      return m_index != x.m_index; //TODO: may not be complete
    }

    const GenVertexHandle operator*() const;

    const GenVertexCollectionIterator& operator++() const {
      ++m_index;
      return *this;
    }

  private:
    mutable int m_index;
    const GenVertexCollection* m_collection;
};

/**
A Collection is identified by an ID.
*/

class GenVertexCollection : public albers::CollectionBase {

public:
  typedef const GenVertexCollectionIterator const_iterator;

  GenVertexCollection();
//  GenVertexCollection(GenVertexVector* data, int collectionID);
  ~GenVertexCollection(){};

  void clear();

  /// Append a new object to the collection, and return a Handle to this object.
  GenVertexHandle create();

  /// Insert an existing handle into the collection. 
  /// In this operation, the data pointed by the handle is copied.
  GenVertexHandle insert(const GenVertexHandle& origin);  
  
  /// Returns a Handle to the object at position index in the collection
  const GenVertexHandle& get(int index) const;

  /// Currently does nothing
  void prepareForWrite(const albers::Registry* registry);
  void prepareAfterRead(albers::Registry* registry);
  void setPODsAddress(const void* address);

  void setID(unsigned ID){m_collectionID = ID;};

  // support for the iterator protocol
  const const_iterator begin() const {
    return const_iterator(0, this);
  }
  const	const_iterator end() const {
    return const_iterator(m_handles.size(), this);
  }

//  std::vector<std::pair<std::string,albers::CollectionBase*>>& referenceCollections();

  /// returns the address of the pointer to the data buffer
  void* _getRawBuffer() { return (void*)&m_data;};

  /// returns the pointer to the data buffer
  std::vector<GenVertex>* _getBuffer() { return m_data;};

  /// returns the collection of Handles
  const GenVertexHandleContainer& getHandles() { return m_handles; }

  /// print some information
  void print() const;


private:
  unsigned m_collectionID;
  GenVertexVector* m_data;
  GenVertexHandleContainer m_handles;
  // members to handle 1-to-N-relations
  
};

#endif