#ifndef SimCaloClusterHitAssociation_H
#define SimCaloClusterHitAssociation_H
#include "SimCaloClusterHitAssociationData.h"

#include <vector>
#include "podio/ObjectID.h"

// Association between a simulated calo cluster and a simulated hit. Used to keep track of the hits used to build a given cluster
// author: C. Bernet, B. Hegner

//forward declarations
class SimCaloCluster;
class ConstSimCaloCluster;
class SimCaloHit;
class ConstSimCaloHit;


#include "SimCaloClusterHitAssociationConst.h"
#include "SimCaloClusterHitAssociationObj.h"



class SimCaloClusterHitAssociationCollection;
class SimCaloClusterHitAssociationCollectionIterator;
class ConstSimCaloClusterHitAssociation;

class SimCaloClusterHitAssociation {

  friend SimCaloClusterHitAssociationCollection;
  friend SimCaloClusterHitAssociationCollectionIterator;
  friend ConstSimCaloClusterHitAssociation;

public:

  /// default constructor
  SimCaloClusterHitAssociation();
  
  /// constructor from existing SimCaloClusterHitAssociationObj
  SimCaloClusterHitAssociation(SimCaloClusterHitAssociationObj* obj);
  /// copy constructor
  SimCaloClusterHitAssociation(const SimCaloClusterHitAssociation& other);
  /// copy-assignment operator
  SimCaloClusterHitAssociation& operator=(const SimCaloClusterHitAssociation& other);
  /// support cloning (deep-copy)
  SimCaloClusterHitAssociation clone() const;
  /// destructor
  ~SimCaloClusterHitAssociation();

  /// conversion to const object
  operator ConstSimCaloClusterHitAssociation () const;

public:

  const ConstSimCaloCluster Cluster() const;
  const ConstSimCaloHit Hit() const;

  void Cluster(ConstSimCaloCluster value);
  void Hit(ConstSimCaloHit value);


  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from SimCaloClusterHitAssociationObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const SimCaloClusterHitAssociation& other) const {
       return (m_obj==other.m_obj);
  }

  bool operator==(const ConstSimCaloClusterHitAssociation& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const SimCaloClusterHitAssociation& p1,
//       const SimCaloClusterHitAssociation& p2 );

  const podio::ObjectID getObjectID() const;

private:
  SimCaloClusterHitAssociationObj* m_obj;

};



#endif
