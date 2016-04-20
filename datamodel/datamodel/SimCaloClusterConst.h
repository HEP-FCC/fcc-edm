#ifndef ConstSimCaloCluster_H
#define ConstSimCaloCluster_H
#include "BareCluster.h"
#include "SimCaloClusterData.h"
#include <vector>
#include "podio/ObjectID.h"

// A simulated calo cluster, made of SimCaloHits
// author: C. Bernet, B. Hegner

//forward declarations


#include "SimCaloClusterObj.h"

namespace fcc {

class SimCaloClusterObj;
class SimCaloCluster;
class SimCaloClusterCollection;
class SimCaloClusterCollectionIterator;

class ConstSimCaloCluster {

  friend SimCaloCluster;
  friend SimCaloClusterCollection;
  friend SimCaloClusterCollectionIterator;

public:

  /// default constructor
  ConstSimCaloCluster();
  ConstSimCaloCluster(fcc::BareCluster Core);

  /// constructor from existing SimCaloClusterObj
  ConstSimCaloCluster(SimCaloClusterObj* obj);
  /// copy constructor
  ConstSimCaloCluster(const ConstSimCaloCluster& other);
  /// copy-assignment operator
  ConstSimCaloCluster& operator=(const ConstSimCaloCluster& other);
  /// support cloning (deep-copy)
  ConstSimCaloCluster clone() const;
  /// destructor
  ~ConstSimCaloCluster();


public:

  const fcc::BareCluster& Core() const;



  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from SimCaloClusterObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const ConstSimCaloCluster& other) const {
       return (m_obj==other.m_obj);
  }

  bool operator==(const SimCaloCluster& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const SimCaloCluster& p1,
//       const SimCaloCluster& p2 );

  const podio::ObjectID getObjectID() const;

private:
  SimCaloClusterObj* m_obj;

};
} // namespace fcc

#endif
