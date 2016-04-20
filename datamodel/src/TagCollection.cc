// standard includes
#include <stdexcept>


#include "TagCollection.h"

namespace fcc {

TagCollection::TagCollection() : m_isValid(false), m_collectionID(0), m_entries() ,m_data(new TagDataContainer() ) {
  
}

TagCollection::~TagCollection() {
  clear();
  if (m_data != nullptr) delete m_data;
  
};

const Tag TagCollection::operator[](unsigned int index) const {
  return Tag(m_entries[index]);
}

const Tag TagCollection::at(unsigned int index) const {
  return Tag(m_entries.at(index));
}

int  TagCollection::size() const {
  return m_entries.size();
}

Tag TagCollection::create(){
  auto obj = new TagObj();
  m_entries.emplace_back(obj);

  obj->id = {int(m_entries.size()-1),m_collectionID};
  return Tag(obj);
}

void TagCollection::clear(){
  m_data->clear();

  for (auto& obj : m_entries) { delete obj; }
  m_entries.clear();
}

void TagCollection::prepareForWrite(){
  auto size = m_entries.size();
  m_data->reserve(size);
  for (auto& obj : m_entries) {m_data->push_back(obj->data); }
  for (auto& pointer : m_refCollections) {pointer->clear(); } 

  for(int i=0, size = m_data->size(); i != size; ++i){

  }

}

void TagCollection::prepareAfterRead(){
  int index = 0;
  for (auto& data : *m_data){
    auto obj = new TagObj({index,m_collectionID}, data);
    
    m_entries.emplace_back(obj);
    ++index;
  }
  m_isValid = true;  
}

bool TagCollection::setReferences(const podio::ICollectionProvider* collectionProvider){


  return true; //TODO: check success
}

void TagCollection::push_back(ConstTag object){
  int size = m_entries.size();
  auto obj = object.m_obj;
  if (obj->id.index == podio::ObjectID::untracked) {
      obj->id = {size,m_collectionID};
      m_entries.push_back(obj);
      
  } else {
    throw std::invalid_argument( "Object already in a collection. Cannot add it to a second collection " );
  }
}

void TagCollection::setBuffer(void* address){
  if (m_data != nullptr) delete m_data;
  m_data = static_cast<TagDataContainer*>(address);
}


const Tag TagCollectionIterator::operator* () const {
  m_object.m_obj = (*m_collection)[m_index];
  return m_object;
}

const Tag* TagCollectionIterator::operator-> () const {
  m_object.m_obj = (*m_collection)[m_index];
  return &m_object;
}

const TagCollectionIterator& TagCollectionIterator::operator++() const {
  ++m_index;
  return *this;
}

} // namespace fcc
