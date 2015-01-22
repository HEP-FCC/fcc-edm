// albers specific includes
#include "albers/Registry.h"
#include "albers/Reader.h"

// datamodel specific includes
#include "datamodel/GenVertex.h"
#include "datamodel/GenVertexCollection.h"



bool  GenVertexHandle::isAvailable() const {
  if (m_container != nullptr) {
    return true;
  }
  return false;
}

void GenVertexHandle::prepareForWrite(const albers::Registry* registry){
  m_containerID = registry->getIDFromPODAddress(m_container);
}

void GenVertexHandle::prepareAfterRead(albers::Registry* registry){
  m_registry = registry;
  m_registry->getPODAddressFromID(m_containerID,m_container);
}


GenVertexHandle::GenVertexHandle(int index, unsigned containerID, std::vector<GenVertex>* container) :
  m_index(index),
  m_containerID(containerID),
  m_container(container)
{}


bool operator< (const GenVertexHandle& p1, const GenVertexHandle& p2 ) {
  if( p1.m_containerID == p2.m_containerID ) {
    return p1.m_index < p2.m_index;
  }
  else {
    return p1.m_containerID < p2.m_containerID;
  }
}
