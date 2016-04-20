// standard includes
#include <stdexcept>


#include "IntTagCollection.h"

namespace fcc {

IntTagCollection::IntTagCollection() : m_isValid(false), m_collectionID(0), m_entries() ,m_data(new IntTagDataContainer() ) {
  
}

IntTagCollection::~IntTagCollection() {
  clear();
  if (m_data != nullptr) delete m_data;
  
};

const IntTag IntTagCollection::operator[](unsigned int index) const {
  return IntTag(m_entries[index]);
}

const IntTag IntTagCollection::at(unsigned int index) const {
  return IntTag(m_entries.at(index));
}

int  IntTagCollection::size() const {
  return m_entries.size();
}

IntTag IntTagCollection::create(){
  auto obj = new IntTagObj();
  m_entries.emplace_back(obj);

  obj->id = {int(m_entries.size()-1),m_collectionID};
  return IntTag(obj);
}

void IntTagCollection::clear(){
  m_data->clear();

  for (auto& obj : m_entries) { delete obj; }
  m_entries.clear();
}

void IntTagCollection::prepareForWrite(){
  auto size = m_entries.size();
  m_data->reserve(size);
  for (auto& obj : m_entries) {m_data->push_back(obj->data); }
  for (auto& pointer : m_refCollections) {pointer->clear(); } 

  for(int i=0, size = m_data->size(); i != size; ++i){

  }

}

void IntTagCollection::prepareAfterRead(){
  int index = 0;
  for (auto& data : *m_data){
    auto obj = new IntTagObj({index,m_collectionID}, data);
    
    m_entries.emplace_back(obj);
    ++index;
  }
  m_isValid = true;  
}

bool IntTagCollection::setReferences(const podio::ICollectionProvider* collectionProvider){


  return true; //TODO: check success
}

void IntTagCollection::push_back(ConstIntTag object){
  int size = m_entries.size();
  auto obj = object.m_obj;
  if (obj->id.index == podio::ObjectID::untracked) {
      obj->id = {size,m_collectionID};
      m_entries.push_back(obj);
      
  } else {
    throw std::invalid_argument( "Object already in a collection. Cannot add it to a second collection " );
  }
}

void IntTagCollection::setBuffer(void* address){
  if (m_data != nullptr) delete m_data;
  m_data = static_cast<IntTagDataContainer*>(address);
}


const IntTag IntTagCollectionIterator::operator* () const {
  m_object.m_obj = (*m_collection)[m_index];
  return m_object;
}

const IntTag* IntTagCollectionIterator::operator-> () const {
  m_object.m_obj = (*m_collection)[m_index];
  return &m_object;
}

const IntTagCollectionIterator& IntTagCollectionIterator::operator++() const {
  ++m_index;
  return *this;
}

} // namespace fcc
