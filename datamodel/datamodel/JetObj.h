#ifndef JetOBJ_H
#define JetOBJ_H

// std includes
#include <atomic>
#include <iostream>

// data model specific includes
#include "podio/ObjBase.h"
#include "JetData.h"

#include <vector>
#include "Particle.h"


// forward declarations
class Jet;
class ConstJet;


namespace fcc {
class JetObj : public podio::ObjBase {
public:
  /// constructor
  JetObj();
  /// copy constructor (does a deep-copy of relation containers)
  JetObj(const JetObj&);
  /// constructor from ObjectID and JetData
  /// does not initialize the internal relation containers
  JetObj(const podio::ObjectID id, JetData data);
  virtual ~JetObj();

public:
  JetData data;
  std::vector<::fcc::ConstParticle>* m_particles;


};
} // namespace fcc


#endif
