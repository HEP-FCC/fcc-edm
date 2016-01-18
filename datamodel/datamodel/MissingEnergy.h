#ifndef MissingEnergy_H
#define MissingEnergy_H
#include "MissingEnergyData.h"

#include <vector>
#include "podio/ObjectID.h"

//  .
// author: C. Bernet, B. Hegner

//forward declarations


#include "MissingEnergyConst.h"
#include "MissingEnergyObj.h"



class MissingEnergyCollection;
class MissingEnergyCollectionIterator;
class ConstMissingEnergy;

class MissingEnergy {

  friend MissingEnergyCollection;
  friend MissingEnergyCollectionIterator;
  friend ConstMissingEnergy;

public:

  /// default constructor
  MissingEnergy();
    MissingEnergy(float Energy,float Phi);

  /// constructor from existing MissingEnergyObj
  MissingEnergy(MissingEnergyObj* obj);
  /// copy constructor
  MissingEnergy(const MissingEnergy& other);
  /// copy-assignment operator
  MissingEnergy& operator=(const MissingEnergy& other);
  /// support cloning (deep-copy)
  MissingEnergy clone() const;
  /// destructor
  ~MissingEnergy();

  /// conversion to const object
  operator ConstMissingEnergy () const;

public:

  const float& Energy() const;
  const float& Phi() const;

  void Energy(float value);
  void Phi(float value);


  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from MissingEnergyObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const MissingEnergy& other) const {
       return (m_obj==other.m_obj);
  }

  bool operator==(const ConstMissingEnergy& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const MissingEnergy& p1,
//       const MissingEnergy& p2 );

  const podio::ObjectID getObjectID() const;

private:
  MissingEnergyObj* m_obj;

};



#endif
