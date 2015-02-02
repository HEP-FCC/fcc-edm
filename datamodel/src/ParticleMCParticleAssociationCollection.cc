#include "datamodel/ParticleMCParticleAssociationCollection.h"

ParticleMCParticleAssociationCollection::ParticleMCParticleAssociationCollection() : m_collectionID(0), m_data(new ParticleMCParticleAssociationVector() ){
}

const ParticleMCParticleAssociationHandle& ParticleMCParticleAssociationCollection::get(int index) const{
  return m_handles[index];
}

ParticleMCParticleAssociationHandle ParticleMCParticleAssociationCollection::create() {
  m_data->emplace_back(ParticleMCParticleAssociation());
  int index = m_data->size()-1;
  // std::cout<<"creating handle: "<<index<<"/"<<m_collectionID<<std::endl;
  m_handles.emplace_back(ParticleMCParticleAssociationHandle(index,m_collectionID, m_data));

  return m_handles.back();
}

ParticleMCParticleAssociationHandle ParticleMCParticleAssociationCollection::insert(const ParticleMCParticleAssociationHandle& origin) {
  m_data->emplace_back(origin.read());
  int index = m_data->size()-1;
  m_handles.emplace_back(ParticleMCParticleAssociationHandle(index,m_collectionID, m_data));

  return m_handles.back();
}  

void ParticleMCParticleAssociationCollection::clear(){
  m_data->clear();
  m_handles.clear();

}

void ParticleMCParticleAssociationCollection::prepareForWrite(const albers::Registry* registry){
  for(auto& data : *m_data){
     data.Rec.prepareForWrite(registry);
    data.Sim.prepareForWrite(registry);
  }
}

void ParticleMCParticleAssociationCollection::prepareAfterRead(albers::Registry* registry){
  m_handles.clear();
  int index = 0;
  // fix. otherwise, m_collectionID == 0..
  m_collectionID = registry->getIDFromPODAddress( _getBuffer() );
  for (auto& data : *m_data){
    data.Rec.prepareAfterRead(registry);
data.Sim.prepareAfterRead(registry);

    m_handles.emplace_back(ParticleMCParticleAssociationHandle(index,m_collectionID, m_data));
    ++index;
  }
}


void ParticleMCParticleAssociationCollection::setPODsAddress(const void* address){
  m_data = (ParticleMCParticleAssociationVector*)address;
}


const ParticleMCParticleAssociationHandle ParticleMCParticleAssociationCollectionIterator::operator* () const {
  return m_collection->get(m_index);
}

//std::vector<std::pair<std::string,albers::CollectionBase*>>& referenceCollections() {
//}


void ParticleMCParticleAssociationCollection::print() const {
  std::cout<<"collection "<<m_collectionID
           <<", buf "<<m_data
           <<", nhandles "<<m_handles.size()<<std::endl;
}

