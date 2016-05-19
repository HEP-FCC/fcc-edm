#ifndef CaloCluster_H
#define CaloCluster_H
#include "BareCluster.h"
#include "CaloClusterData.h"
#include <vector>
#include "podio/ObjectID.h"

// A calo cluster, made of CaloHits
// author: C. Bernet, B. Hegner

//forward declarations


#include "CaloClusterConst.h"
#include "CaloClusterObj.h"

namespace fcc {

class CaloClusterCollection;
class CaloClusterCollectionIterator;
class ConstCaloCluster;

class CaloCluster {

  friend CaloClusterCollection;
  friend CaloClusterCollectionIterator;
  friend ConstCaloCluster;

public:

  /// default constructor
  CaloCluster();
  CaloCluster(fcc::BareCluster Core);

  /// constructor from existing CaloClusterObj
  CaloCluster(CaloClusterObj* obj);
  /// copy constructor
  CaloCluster(const CaloCluster& other);
  /// copy-assignment operator
  CaloCluster& operator=(const CaloCluster& other);
  /// support cloning (deep-copy)
  CaloCluster clone() const;
  /// destructor
  ~CaloCluster();

  /// conversion to const object
  operator ConstCaloCluster () const;

public:

  const fcc::BareCluster& Core() const;

  fcc::BareCluster& Core();
  void Core(class fcc::BareCluster value);



  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from CaloClusterObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const CaloCluster& other) const {
    return (m_obj==other.m_obj);
  }

  bool operator==(const ConstCaloCluster& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const CaloCluster& p1,
//       const CaloCluster& p2 );
  bool operator<(const CaloCluster& other) const { return m_obj < other.m_obj  ; }

  const podio::ObjectID getObjectID() const;

private:
  CaloClusterObj* m_obj;

};

} // namespace fcc

#endif
