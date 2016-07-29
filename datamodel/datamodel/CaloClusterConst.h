#ifndef ConstCaloCluster_H
#define ConstCaloCluster_H
#include "BareCluster.h"
#include "CaloClusterData.h"
#include <vector>
#include "CaloHit.h"
#include <vector>
#include "podio/ObjectID.h"

//forward declarations


#include "CaloClusterObj.h"

namespace fcc {

class CaloClusterObj;
class CaloCluster;
class CaloClusterCollection;
class CaloClusterCollectionIterator;

/** @class ConstCaloCluster
 *  A calo cluster, made of CaloHits
 *  @author: C. Bernet, B. Hegner
 */

class ConstCaloCluster {

  friend CaloCluster;
  friend CaloClusterCollection;
  friend CaloClusterCollectionIterator;

public:

  /// default constructor
  ConstCaloCluster();
  ConstCaloCluster(fcc::BareCluster core);

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

  /// Access the  contains basic cluster information
  const fcc::BareCluster& core() const;
  /// Access the member of  contains basic cluster information
  const unsigned& bits() const;
  /// Access the member of  contains basic cluster information
  const float& energy() const;
  /// Access the member of  contains basic cluster information
  const ::fcc::Point& position() const;
  /// Access the member of  contains basic cluster information
  const float& time() const;

  unsigned int hits_size() const;
  fcc::ConstCaloHit hits(unsigned int) const;
  std::vector<fcc::ConstCaloHit>::const_iterator hits_begin() const;
  std::vector<fcc::ConstCaloHit>::const_iterator hits_end() const;


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
  bool operator<(const ConstCaloCluster& other) const { return m_obj < other.m_obj  ; }

  const podio::ObjectID getObjectID() const;

private:
  CaloClusterObj* m_obj;

};
} // namespace fcc

#endif
