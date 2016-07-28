#ifndef GenJetOBJ_H
#define GenJetOBJ_H

// std includes
#include <atomic>
#include <iostream>

// data model specific includes
#include "podio/ObjBase.h"
#include "GenJetData.h"

#include <vector>
#include "MCParticle.h"


// forward declarations
class GenJet;
class ConstGenJet;


namespace fcc {
class GenJetObj : public podio::ObjBase {
public:
  /// constructor
  GenJetObj();
  /// copy constructor (does a deep-copy of relation containers)
  GenJetObj(const GenJetObj&);
  /// constructor from ObjectID and GenJetData
  /// does not initialize the internal relation containers
  GenJetObj(const podio::ObjectID id, GenJetData data);
  virtual ~GenJetObj();

public:
  GenJetData data;
  std::vector<::fcc::ConstMCParticle>* m_particles;


};
} // namespace fcc


#endif
