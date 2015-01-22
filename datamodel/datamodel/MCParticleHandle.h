#ifndef MCParticleHANDLE_H
#define MCParticleHANDLE_H
#include "datamodel/MCParticle.h"
#include "datamodel/BareParticle.h"
#include "datamodel/GenVertexHandle.h"
#include "datamodel/GenVertexHandle.h"

#include <vector>

// Reference to the vertex in which the particle disappeared.
// author: C. Bernet, B. Hegner

//forward declaration of MCParticle container
class MCParticleCollection;

namespace albers {
  class Registry;
}

class MCParticleHandle {

  friend class MCParticleCollection;

public:

  MCParticleHandle() :
  		      m_index(-1),
		      m_containerID(0),
		      m_container(0),
		      m_registry(0)
		      {}	

  MCParticleHandle(const MCParticleHandle& other) :
  		      m_index(other.m_index),
		      m_containerID(other.m_containerID),
		      m_container(other.m_container),
		      m_registry(other.m_registry)
		      {}	

//TODO: Proper syntax to use, but ROOT doesn't handle it:  MCParticleHandle() = default;



  // precheck whether the pointee actually exists
  bool isAvailable() const;

  // returns a const (read-only) reference to the object pointed by the Handle.
  const MCParticle& read() const {return m_container->at(m_index);}

  // returns a non-const (writeable) reference to the object pointed by the Handle 
  MCParticle& mod() {return m_container->at(m_index);}
  
  void prepareForWrite(const albers::Registry*);  // use m_container to set m_containerID properly
  
  void prepareAfterRead(albers::Registry*);   // use m_containerID to set m_container properly

  int index() const {return m_index;}

  int containerID() const {return m_containerID;}

  /// equality operator (true if both the index and the container ID are equal)
  bool operator==(const MCParticleHandle& other) const {
       return (m_index==other.m_index) && (other.m_containerID==other.m_containerID);
  }

  /// less comparison operator, so that Handles can be e.g. stored in sets.
  friend bool operator< (const MCParticleHandle& p1,
			 const MCParticleHandle& p2 );

private:
  MCParticleHandle(int index, unsigned containerID,  std::vector<MCParticle>* container);
  int m_index;
  unsigned m_containerID;
  mutable std::vector<MCParticle>* m_container; //! transient
  albers::Registry* m_registry; //! transient
  //  bool _retrieveData();
  // members to support 1-to-N relations
  

};

#endif
