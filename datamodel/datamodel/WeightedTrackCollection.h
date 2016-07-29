//AUTOMATICALLY GENERATED - DO NOT EDIT

#ifndef WeightedTrackCollection_H
#define  WeightedTrackCollection_H

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
#include "WeightedTrackData.h"
#include "WeightedTrack.h"
#include "WeightedTrackObj.h"

namespace fcc {
typedef std::vector<WeightedTrackData> WeightedTrackDataContainer;
typedef std::deque<WeightedTrackObj*> WeightedTrackObjPointerContainer;

class WeightedTrackCollectionIterator {

  public:
    WeightedTrackCollectionIterator(int index, const WeightedTrackObjPointerContainer* collection) : m_index(index), m_object(nullptr), m_collection(collection) {}

    bool operator!=(const WeightedTrackCollectionIterator& x) const {
      return m_index != x.m_index; //TODO: may not be complete
    }

    const WeightedTrack operator*() const;
    const WeightedTrack* operator->() const;
    const WeightedTrackCollectionIterator& operator++() const;

  private:
    mutable int m_index;
    mutable WeightedTrack m_object;
    const WeightedTrackObjPointerContainer* m_collection;
};

/**
A Collection is identified by an ID.
*/

class WeightedTrackCollection : public podio::CollectionBase {

public:
  typedef const WeightedTrackCollectionIterator const_iterator;

  WeightedTrackCollection();
//  WeightedTrackCollection(const WeightedTrackCollection& ) = delete; // deletion doesn't work w/ ROOT IO ! :-(
//  WeightedTrackCollection(WeightedTrackVector* data, int collectionID);
  ~WeightedTrackCollection();

  void clear();
  /// Append a new object to the collection, and return this object.
  WeightedTrack create();

  /// Append a new object to the collection, and return this object.
  /// Initialized with the parameters given
  template<typename... Args>
  WeightedTrack create(Args&&... args);
  int size() const;

  /// Returns the object of given index
  const WeightedTrack operator[](unsigned int index) const;
  /// Returns the object of given index
  const WeightedTrack at(unsigned int index) const;


  /// Append object to the collection
  void push_back(ConstWeightedTrack object);

  void prepareForWrite();
  void prepareAfterRead();
  void setBuffer(void* address);
  bool setReferences(const podio::ICollectionProvider* collectionProvider);

  podio::CollRefCollection* referenceCollections() { return &m_refCollections;};

  void setID(unsigned ID){
    m_collectionID = ID;
    std::for_each(m_entries.begin(),m_entries.end(),
                 [ID](WeightedTrackObj* obj){obj->id = {obj->id.index,static_cast<int>(ID)}; }
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
  std::vector<WeightedTrackData>* _getBuffer() { return m_data;};

    template<size_t arraysize>
  const std::array<float,arraysize> weight() const;


private:
  bool m_isValid;
  int m_collectionID;
  WeightedTrackObjPointerContainer m_entries;
  // members to handle 1-to-N-relations
  std::vector<fcc::ConstTrack>* m_rel_track; ///< Relation buffer for read / write

  // members to handle streaming
  podio::CollRefCollection m_refCollections;
  WeightedTrackDataContainer* m_data;
};

template<typename... Args>
WeightedTrack  WeightedTrackCollection::create(Args&&... args){
  int size = m_entries.size();
  auto obj = new WeightedTrackObj({size,m_collectionID},{args...});
  m_entries.push_back(obj);
  return WeightedTrack(obj);
}

template<size_t arraysize>
const std::array<float,arraysize> WeightedTrackCollection::weight() const {
  std::array<float,arraysize> tmp;
  auto valid_size = std::min(arraysize,m_entries.size());
  for (unsigned i = 0; i<valid_size; ++i){
    tmp[i] = m_entries[i]->data.weight;
 }
 return tmp;
}

} // namespace fcc
#endif
