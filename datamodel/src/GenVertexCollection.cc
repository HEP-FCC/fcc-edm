#include "datamodel/GenVertexCollection.h"

GenVertexCollection::GenVertexCollection() : m_collectionID(0), m_data(new GenVertexVector() ){
}

const GenVertexHandle& GenVertexCollection::get(int index) const{
  return m_handles[index];
}

GenVertexHandle GenVertexCollection::create() {
  m_data->emplace_back(GenVertex());
  int index = m_data->size()-1;
  // std::cout<<"creating handle: "<<index<<"/"<<m_collectionID<<std::endl;
  m_handles.emplace_back(GenVertexHandle(index,m_collectionID, m_data));

  return m_handles.back();
}

GenVertexHandle GenVertexCollection::insert(const GenVertexHandle& origin) {
  m_data->emplace_back(origin.read());
  int index = m_data->size()-1;
  m_handles.emplace_back(GenVertexHandle(index,m_collectionID, m_data));

  return m_handles.back();
}  

void GenVertexCollection::clear(){
  m_data->clear();
  m_handles.clear();

}

void GenVertexCollection::prepareForWrite(const albers::Registry* registry){

}

void GenVertexCollection::prepareAfterRead(albers::Registry* registry){
  m_handles.clear();
  int index = 0;
  // fix. otherwise, m_collectionID == 0..
  m_collectionID = registry->getIDFromPODAddress( _getBuffer() );
  for (auto& data : *m_data){
    
    m_handles.emplace_back(GenVertexHandle(index,m_collectionID, m_data));
    ++index;
  }
}


void GenVertexCollection::setPODsAddress(const void* address){
  m_data = (GenVertexVector*)address;
}


const GenVertexHandle GenVertexCollectionIterator::operator* () const {
  return m_collection->get(m_index);
}

//std::vector<std::pair<std::string,albers::CollectionBase*>>& referenceCollections() {
//}


void GenVertexCollection::print() const {
  std::cout<<"collection "<<m_collectionID
           <<", buf "<<m_data
           <<", nhandles "<<m_handles.size()<<std::endl;
}

