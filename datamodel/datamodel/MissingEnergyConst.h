#ifndef ConstMissingEnergy_H
#define ConstMissingEnergy_H
#include "MissingEnergyData.h"

#include <vector>
#include "podio/ObjectID.h"

//  .
// author: C. Bernet, B. Hegner

//forward declarations


#include "MissingEnergyObj.h"



class MissingEnergyObj;
class MissingEnergy;
class MissingEnergyCollection;
class MissingEnergyCollectionIterator;

class ConstMissingEnergy {

  friend MissingEnergy;
  friend MissingEnergyCollection;
  friend MissingEnergyCollectionIterator;

public:

  /// default constructor
  ConstMissingEnergy();
  ConstMissingEnergy(float Energy,float Phi);

  /// constructor from existing MissingEnergyObj
  ConstMissingEnergy(MissingEnergyObj* obj);
  /// copy constructor
  ConstMissingEnergy(const ConstMissingEnergy& other);
  /// copy-assignment operator
  ConstMissingEnergy& operator=(const ConstMissingEnergy& other);
  /// support cloning (deep-copy)
  ConstMissingEnergy clone() const;
  /// destructor
  ~ConstMissingEnergy();


public:

  const float& Energy() const;
  const float& Phi() const;


  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from MissingEnergyObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const ConstMissingEnergy& other) const {
       return (m_obj==other.m_obj);
  }

  bool operator==(const MissingEnergy& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const MissingEnergy& p1,
//       const MissingEnergy& p2 );

  const podio::ObjectID getObjectID() const;

private:
  MissingEnergyObj* m_obj;

};


#endif
