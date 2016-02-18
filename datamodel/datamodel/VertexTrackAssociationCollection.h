//AUTOMATICALLY GENERATED - DO NOT EDIT

#ifndef VertexTrackAssociationCollection_H
#define  VertexTrackAssociationCollection_H

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
#include "VertexTrackAssociationData.h"
#include "VertexTrackAssociation.h"
#include "VertexTrackAssociationObj.h"

namespace fcc {
typedef std::vector<VertexTrackAssociationData> VertexTrackAssociationDataContainer;
typedef std::deque<VertexTrackAssociationObj*> VertexTrackAssociationObjPointerContainer;

class VertexTrackAssociationCollectionIterator {

  public:
    VertexTrackAssociationCollectionIterator(int index, const VertexTrackAssociationObjPointerContainer* collection) : m_index(index), m_object(nullptr), m_collection(collection) {}

    bool operator!=(const VertexTrackAssociationCollectionIterator& x) const {
      return m_index != x.m_index; //TODO: may not be complete
    }

    const VertexTrackAssociation operator*() const;
    const VertexTrackAssociation* operator->() const;
    const VertexTrackAssociationCollectionIterator& operator++() const;

  private:
    mutable int m_index;
    mutable VertexTrackAssociation m_object;
    const VertexTrackAssociationObjPointerContainer* m_collection;
};

/**
A Collection is identified by an ID.
*/

class VertexTrackAssociationCollection : public podio::CollectionBase {

public:
  typedef const VertexTrackAssociationCollectionIterator const_iterator;

  VertexTrackAssociationCollection();
//  VertexTrackAssociationCollection(const VertexTrackAssociationCollection& ) = delete; // deletion doesn't work w/ ROOT IO ! :-(
//  VertexTrackAssociationCollection(VertexTrackAssociationVector* data, int collectionID);
  ~VertexTrackAssociationCollection(){};

  void clear();
  /// Append a new object to the collection, and return this object.
  VertexTrackAssociation create();

  /// Append a new object to the collection, and return this object.
  /// Initialized with the parameters given
  template<typename... Args>
  VertexTrackAssociation create(Args&&... args);
  int size() const;

  /// Returns the object of given index
  const VertexTrackAssociation operator[](unsigned int index) const;
  /// Returns the object of given index
  const VertexTrackAssociation at(unsigned int index) const;


  /// Append object to the collection
  void push_back(ConstVertexTrackAssociation object);

  void prepareForWrite();
  void prepareAfterRead();
  void setBuffer(void* address);
  bool setReferences(const podio::ICollectionProvider* collectionProvider);

  podio::CollRefCollection* referenceCollections() { return m_refCollections;};

  void setID(unsigned ID){
    m_collectionID = ID;
    std::for_each(m_entries.begin(),m_entries.end(),
                 [ID](VertexTrackAssociationObj* obj){obj->id = {obj->id.index,static_cast<int>(ID)}; }
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
  std::vector<VertexTrackAssociationData>* _getBuffer() { return m_data;};

     template<size_t arraysize>  
  const std::array<float,arraysize> Weight() const;


private:
  int m_collectionID;
  VertexTrackAssociationObjPointerContainer m_entries;
  // members to handle 1-to-N-relations
  std::vector<::fcc::ConstTrack>* m_rel_Track; //relation buffer for r/w
  std::vector<::fcc::ConstVertex>* m_rel_Vertex; //relation buffer for r/w

  // members to handle streaming
  podio::CollRefCollection* m_refCollections;
  VertexTrackAssociationDataContainer* m_data;
};

template<typename... Args>
VertexTrackAssociation  VertexTrackAssociationCollection::create(Args&&... args){
  int size = m_entries.size();
  auto obj = new VertexTrackAssociationObj({size,m_collectionID},{args...});
  m_entries.push_back(obj);
  return VertexTrackAssociation(obj);
}

template<size_t arraysize>
const std::array<float,arraysize> VertexTrackAssociationCollection::Weight() const {
  std::array<float,arraysize> tmp;
  auto valid_size = std::min(arraysize,m_entries.size());
  for (unsigned i = 0; i<valid_size; ++i){
    tmp[i] = m_entries[i]->data.Weight;
 }
 return tmp;
}

} // namespace fcc
#endif
