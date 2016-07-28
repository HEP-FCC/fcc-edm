#ifndef EventInfo_H
#define EventInfo_H
#include "EventInfoData.h"
#include <vector>
#include "podio/ObjectID.h"

//forward declarations


#include "EventInfoConst.h"
#include "EventInfoObj.h"

namespace fcc {

class EventInfoCollection;
class EventInfoCollectionIterator;
class ConstEventInfo;

/** @class EventInfo
 *  Event Info Data
 *  @author: C. Bernet, B. Hegner
 */
class EventInfo {

  friend EventInfoCollection;
  friend EventInfoCollectionIterator;
  friend ConstEventInfo;

public:

  /// default constructor
  EventInfo();
  EventInfo(int number);

  /// constructor from existing EventInfoObj
  EventInfo(EventInfoObj* obj);
  /// copy constructor
  EventInfo(const EventInfo& other);
  /// copy-assignment operator
  EventInfo& operator=(const EventInfo& other);
  /// support cloning (deep-copy)
  EventInfo clone() const;
  /// destructor
  ~EventInfo();

  /// conversion to const object
  operator ConstEventInfo () const;

public:

  /// Access the  Event number
  const int& number() const;

  /// Set the  Event number
  void number(int value);




  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from EventInfoObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const EventInfo& other) const {
    return (m_obj==other.m_obj);
  }

  bool operator==(const ConstEventInfo& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const EventInfo& p1,
//       const EventInfo& p2 );
  bool operator<(const EventInfo& other) const { return m_obj < other.m_obj  ; }

  const podio::ObjectID getObjectID() const;

private:
  EventInfoObj* m_obj;

};

} // namespace fcc

#endif
