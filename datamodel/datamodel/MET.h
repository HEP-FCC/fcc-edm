#ifndef MET_H
#define MET_H
#include "METData.h"
#include <vector>
#include "podio/ObjectID.h"

//forward declarations


#include "METConst.h"
#include "METObj.h"

namespace fcc {

class METCollection;
class METCollectionIterator;
class ConstMET;

/** @class MET
 *  Naive MET type
 *  @author: C. Bernet, B. Hegner
 */
class MET {

  friend METCollection;
  friend METCollectionIterator;
  friend ConstMET;

public:

  /// default constructor
  MET();
  MET(float magnitude,float phi,float scalarSum);

  /// constructor from existing METObj
  MET(METObj* obj);
  /// copy constructor
  MET(const MET& other);
  /// copy-assignment operator
  MET& operator=(const MET& other);
  /// support cloning (deep-copy)
  MET clone() const;
  /// destructor
  ~MET();

  /// conversion to const object
  operator ConstMET () const;

public:

  /// Access the  Magnitude (could be the pT or the ET of the MET vector)
  const float& magnitude() const;
  /// Access the  Azimuthal angle
  const float& phi() const;
  /// Access the  Corresponding sum pT or sum ET
  const float& scalarSum() const;

  /// Set the  Magnitude (could be the pT or the ET of the MET vector)
  void magnitude(float value);

  /// Set the  Azimuthal angle
  void phi(float value);

  /// Set the  Corresponding sum pT or sum ET
  void scalarSum(float value);




  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from METObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const MET& other) const {
    return (m_obj==other.m_obj);
  }

  bool operator==(const ConstMET& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const MET& p1,
//       const MET& p2 );
  bool operator<(const MET& other) const { return m_obj < other.m_obj  ; }

  const podio::ObjectID getObjectID() const;

private:
  METObj* m_obj;

};

} // namespace fcc

#endif
