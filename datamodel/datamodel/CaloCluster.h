#ifndef CaloCluster_H
#define CaloCluster_H
#include "BareCluster.h"
#include "CaloClusterData.h"
#include <vector>
#include "CaloHit.h"
#include <vector>
#include "podio/ObjectID.h"

//forward declarations


#include "CaloClusterConst.h"
#include "CaloClusterObj.h"

namespace fcc {

class CaloClusterCollection;
class CaloClusterCollectionIterator;
class ConstCaloCluster;

/** @class CaloCluster
 *  A calo cluster, made of CaloHits
 *  @author: C. Bernet, B. Hegner
 */
class CaloCluster {

  friend CaloClusterCollection;
  friend CaloClusterCollectionIterator;
  friend ConstCaloCluster;

public:

  /// default constructor
  CaloCluster();
  CaloCluster(fcc::BareCluster core);

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

  /// Get reference to the  contains basic cluster information
  fcc::BareCluster& core();
  /// Set the  contains basic cluster information
  void core(class fcc::BareCluster value);
  /// Set the  member of  contains basic cluster information
  void bits(unsigned value);

  /// Set the  member of  contains basic cluster information
  void energy(float value);

  /// Get reference to the member of  contains basic cluster information
  ::fcc::Point& position();
  /// Set the  member of  contains basic cluster information
  void position(class ::fcc::Point value);
  /// Set the  member of  contains basic cluster information
  void time(float value);


  void addhits(fcc::ConstCaloHit);
  unsigned int hits_size() const;
  fcc::ConstCaloHit hits(unsigned int) const;
  std::vector<fcc::ConstCaloHit>::const_iterator hits_begin() const;
  std::vector<fcc::ConstCaloHit>::const_iterator hits_end() const;



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
