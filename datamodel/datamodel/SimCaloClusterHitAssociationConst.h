#ifndef ConstSimCaloClusterHitAssociation_H
#define ConstSimCaloClusterHitAssociation_H
#include "SimCaloClusterHitAssociationData.h"
#include <vector>
#include "podio/ObjectID.h"

// Association between a simulated calo cluster and a simulated hit. Used to keep track of the hits used to build a given cluster
// author: C. Bernet, B. Hegner

//forward declarations
namespace fcc {
class SimCaloCluster;
class ConstSimCaloCluster;
class SimCaloHit;
class ConstSimCaloHit;
}


#include "SimCaloClusterHitAssociationObj.h"

namespace fcc {

class SimCaloClusterHitAssociationObj;
class SimCaloClusterHitAssociation;
class SimCaloClusterHitAssociationCollection;
class SimCaloClusterHitAssociationCollectionIterator;

class ConstSimCaloClusterHitAssociation {

  friend SimCaloClusterHitAssociation;
  friend SimCaloClusterHitAssociationCollection;
  friend SimCaloClusterHitAssociationCollectionIterator;

public:

  /// default constructor
  ConstSimCaloClusterHitAssociation();
  
  /// constructor from existing SimCaloClusterHitAssociationObj
  ConstSimCaloClusterHitAssociation(SimCaloClusterHitAssociationObj* obj);
  /// copy constructor
  ConstSimCaloClusterHitAssociation(const ConstSimCaloClusterHitAssociation& other);
  /// copy-assignment operator
  ConstSimCaloClusterHitAssociation& operator=(const ConstSimCaloClusterHitAssociation& other);
  /// support cloning (deep-copy)
  ConstSimCaloClusterHitAssociation clone() const;
  /// destructor
  ~ConstSimCaloClusterHitAssociation();


public:

  const fcc::ConstSimCaloCluster Cluster() const;
  const fcc::ConstSimCaloHit Hit() const;



  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from SimCaloClusterHitAssociationObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const ConstSimCaloClusterHitAssociation& other) const {
       return (m_obj==other.m_obj);
  }

  bool operator==(const SimCaloClusterHitAssociation& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const SimCaloClusterHitAssociation& p1,
//       const SimCaloClusterHitAssociation& p2 );
  bool operator<(const ConstSimCaloClusterHitAssociation& other) const { return m_obj < other.m_obj  ; }

  const podio::ObjectID getObjectID() const;

private:
  SimCaloClusterHitAssociationObj* m_obj;

};
} // namespace fcc

#endif
