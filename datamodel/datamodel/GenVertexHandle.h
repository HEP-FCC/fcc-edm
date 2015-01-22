#ifndef GenVertexHANDLE_H
#define GenVertexHANDLE_H
#include "datamodel/GenVertex.h"
#include "datamodel/Point.h"

#include <vector>

// Not sure how it's defined.
// author: C. Bernet, B. Hegner

//forward declaration of GenVertex container
class GenVertexCollection;

namespace albers {
  class Registry;
}

class GenVertexHandle {

  friend class GenVertexCollection;

public:

  GenVertexHandle() :
  		      m_index(-1),
		      m_containerID(0),
		      m_container(0),
		      m_registry(0)
		      {}	

  GenVertexHandle(const GenVertexHandle& other) :
  		      m_index(other.m_index),
		      m_containerID(other.m_containerID),
		      m_container(other.m_container),
		      m_registry(other.m_registry)
		      {}	

//TODO: Proper syntax to use, but ROOT doesn't handle it:  GenVertexHandle() = default;



  // precheck whether the pointee actually exists
  bool isAvailable() const;

  // returns a const (read-only) reference to the object pointed by the Handle.
  const GenVertex& read() const {return m_container->at(m_index);}

  // returns a non-const (writeable) reference to the object pointed by the Handle 
  GenVertex& mod() {return m_container->at(m_index);}
  
  void prepareForWrite(const albers::Registry*);  // use m_container to set m_containerID properly
  
  void prepareAfterRead(albers::Registry*);   // use m_containerID to set m_container properly

  int index() const {return m_index;}

  int containerID() const {return m_containerID;}

  /// equality operator (true if both the index and the container ID are equal)
  bool operator==(const GenVertexHandle& other) const {
       return (m_index==other.m_index) && (other.m_containerID==other.m_containerID);
  }

  /// less comparison operator, so that Handles can be e.g. stored in sets.
  friend bool operator< (const GenVertexHandle& p1,
			 const GenVertexHandle& p2 );

private:
  GenVertexHandle(int index, unsigned containerID,  std::vector<GenVertex>* container);
  int m_index;
  unsigned m_containerID;
  mutable std::vector<GenVertex>* m_container; //! transient
  albers::Registry* m_registry; //! transient
  //  bool _retrieveData();
  // members to support 1-to-N relations
  

};

#endif
