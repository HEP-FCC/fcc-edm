// standard includes
#include <stdexcept>


#include "METCollection.h"

namespace fcc {

METCollection::METCollection() : m_isValid(false), m_collectionID(0), m_entries() ,m_data(new METDataContainer() ) {
  
}

METCollection::~METCollection() {
  clear();
  if (m_data != nullptr) delete m_data;
  
}

const MET METCollection::operator[](unsigned int index) const {
  return MET(m_entries[index]);
}

const MET METCollection::at(unsigned int index) const {
  return MET(m_entries.at(index));
}

int  METCollection::size() const {
  return m_entries.size();
}

MET METCollection::create(){
  auto obj = new METObj();
  m_entries.emplace_back(obj);

  obj->id = {int(m_entries.size()-1),m_collectionID};
  return MET(obj);
}

void METCollection::clear(){
  m_data->clear();

  for (auto& obj : m_entries) { delete obj; }
  m_entries.clear();
}

void METCollection::prepareForWrite(){
  auto size = m_entries.size();
  m_data->reserve(size);
  for (auto& obj : m_entries) {m_data->push_back(obj->data); }
  for (auto& pointer : m_refCollections) {pointer->clear(); } 

  for(int i=0, size = m_data->size(); i != size; ++i){

  }

}

void METCollection::prepareAfterRead(){
  int index = 0;
  for (auto& data : *m_data){
    auto obj = new METObj({index,m_collectionID}, data);
    
    m_entries.emplace_back(obj);
    ++index;
  }
  m_isValid = true;  
}

bool METCollection::setReferences(const podio::ICollectionProvider* collectionProvider){


  return true; //TODO: check success
}

void METCollection::push_back(ConstMET object){
  int size = m_entries.size();
  auto obj = object.m_obj;
  if (obj->id.index == podio::ObjectID::untracked) {
      obj->id = {size,m_collectionID};
      m_entries.push_back(obj);
      
  } else {
    throw std::invalid_argument( "Object already in a collection. Cannot add it to a second collection " );
  }
}

void METCollection::setBuffer(void* address){
  if (m_data != nullptr) delete m_data;
  m_data = static_cast<METDataContainer*>(address);
}


const MET METCollectionIterator::operator* () const {
  m_object.m_obj = (*m_collection)[m_index];
  return m_object;
}

const MET* METCollectionIterator::operator-> () const {
  m_object.m_obj = (*m_collection)[m_index];
  return &m_object;
}

const METCollectionIterator& METCollectionIterator::operator++() const {
  ++m_index;
  return *this;
}

} // namespace fcc
