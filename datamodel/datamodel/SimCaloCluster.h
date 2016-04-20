#ifndef SimCaloCluster_H
#define SimCaloCluster_H
#include "BareCluster.h"
#include "SimCaloClusterData.h"
#include <vector>
#include "podio/ObjectID.h"

// A simulated calo cluster, made of SimCaloHits
// author: C. Bernet, B. Hegner

//forward declarations


#include "SimCaloClusterConst.h"
#include "SimCaloClusterObj.h"

namespace fcc {

class SimCaloClusterCollection;
class SimCaloClusterCollectionIterator;
class ConstSimCaloCluster;

class SimCaloCluster {

  friend SimCaloClusterCollection;
  friend SimCaloClusterCollectionIterator;
  friend ConstSimCaloCluster;

public:

  /// default constructor
  SimCaloCluster();
  SimCaloCluster(fcc::BareCluster Core);

  /// constructor from existing SimCaloClusterObj
  SimCaloCluster(SimCaloClusterObj* obj);
  /// copy constructor
  SimCaloCluster(const SimCaloCluster& other);
  /// copy-assignment operator
  SimCaloCluster& operator=(const SimCaloCluster& other);
  /// support cloning (deep-copy)
  SimCaloCluster clone() const;
  /// destructor
  ~SimCaloCluster();

  /// conversion to const object
  operator ConstSimCaloCluster () const;

public:

  const fcc::BareCluster& Core() const;

  fcc::BareCluster& Core();
  void Core(class fcc::BareCluster value);



  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from SimCaloClusterObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const SimCaloCluster& other) const {
    return (m_obj==other.m_obj);
  }

  bool operator==(const ConstSimCaloCluster& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const SimCaloCluster& p1,
//       const SimCaloCluster& p2 );

  const podio::ObjectID getObjectID() const;

private:
  SimCaloClusterObj* m_obj;

};

} // namespace fcc

#endif
