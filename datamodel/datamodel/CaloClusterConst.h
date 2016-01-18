#ifndef ConstCaloCluster_H
#define ConstCaloCluster_H
#include "CaloClusterData.h"
#include "BareCluster.h"

#include <vector>
#include "podio/ObjectID.h"

//  contains basic cluster information
// author: C. Bernet, B. Hegner

//forward declarations


#include "CaloClusterObj.h"



class CaloClusterObj;
class CaloCluster;
class CaloClusterCollection;
class CaloClusterCollectionIterator;

class ConstCaloCluster {

  friend CaloCluster;
  friend CaloClusterCollection;
  friend CaloClusterCollectionIterator;

public:

  /// default constructor
  ConstCaloCluster();
  ConstCaloCluster(BareCluster Core);

  /// constructor from existing CaloClusterObj
  ConstCaloCluster(CaloClusterObj* obj);
  /// copy constructor
  ConstCaloCluster(const ConstCaloCluster& other);
  /// copy-assignment operator
  ConstCaloCluster& operator=(const ConstCaloCluster& other);
  /// support cloning (deep-copy)
  ConstCaloCluster clone() const;
  /// destructor
  ~ConstCaloCluster();


public:

  const BareCluster& Core() const;


  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from CaloClusterObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const ConstCaloCluster& other) const {
       return (m_obj==other.m_obj);
  }

  bool operator==(const CaloCluster& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const CaloCluster& p1,
//       const CaloCluster& p2 );

  const podio::ObjectID getObjectID() const;

private:
  CaloClusterObj* m_obj;

};


#endif
