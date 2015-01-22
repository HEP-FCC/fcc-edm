#ifndef ParticleMCAssociationHANDLE_H
#define ParticleMCAssociationHANDLE_H
#include "datamodel/ParticleMCAssociation.h"
#include "datamodel/ParticleHandle.h"
#include "datamodel/MCParticleHandle.h"

#include <vector>

// Reference to the Monte-Carlo particle
// author: C. Bernet, B. Hegner

//forward declaration of ParticleMCAssociation container
class ParticleMCAssociationCollection;

namespace albers {
  class Registry;
}

class ParticleMCAssociationHandle {

  friend class ParticleMCAssociationCollection;

public:

  ParticleMCAssociationHandle() :
  		      m_index(-1),
		      m_containerID(0),
		      m_container(0),
		      m_registry(0)
		      {}	

  ParticleMCAssociationHandle(const ParticleMCAssociationHandle& other) :
  		      m_index(other.m_index),
		      m_containerID(other.m_containerID),
		      m_container(other.m_container),
		      m_registry(other.m_registry)
		      {}	

//TODO: Proper syntax to use, but ROOT doesn't handle it:  ParticleMCAssociationHandle() = default;



  // precheck whether the pointee actually exists
  bool isAvailable() const;

  // returns a const (read-only) reference to the object pointed by the Handle.
  const ParticleMCAssociation& read() const {return m_container->at(m_index);}

  // returns a non-const (writeable) reference to the object pointed by the Handle 
  ParticleMCAssociation& mod() {return m_container->at(m_index);}
  
  void prepareForWrite(const albers::Registry*);  // use m_container to set m_containerID properly
  
  void prepareAfterRead(albers::Registry*);   // use m_containerID to set m_container properly

  int index() const {return m_index;}

  int containerID() const {return m_containerID;}

  /// equality operator (true if both the index and the container ID are equal)
  bool operator==(const ParticleMCAssociationHandle& other) const {
       return (m_index==other.m_index) && (other.m_containerID==other.m_containerID);
  }

  /// less comparison operator, so that Handles can be e.g. stored in sets.
  friend bool operator< (const ParticleMCAssociationHandle& p1,
			 const ParticleMCAssociationHandle& p2 );

private:
  ParticleMCAssociationHandle(int index, unsigned containerID,  std::vector<ParticleMCAssociation>* container);
  int m_index;
  unsigned m_containerID;
  mutable std::vector<ParticleMCAssociation>* m_container; //! transient
  albers::Registry* m_registry; //! transient
  //  bool _retrieveData();
  // members to support 1-to-N relations
  

};

#endif
