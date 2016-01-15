#include "CaloHitAssociationObj.h"
#include "CaloHitConst.h"
#include "SimCaloHitConst.h"



CaloHitAssociationObj::CaloHitAssociationObj() :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    ,data()
    ,m_Rec(nullptr)
,m_Sim(nullptr)

    { }

CaloHitAssociationObj::CaloHitAssociationObj(const podio::ObjectID id, CaloHitAssociationData data) :
    ObjBase{id,0},
    data(data)
    { }

CaloHitAssociationObj::CaloHitAssociationObj(const CaloHitAssociationObj& other) :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    ,data(other.data)
    
    { }

CaloHitAssociationObj::~CaloHitAssociationObj() {
  if (id.index == podio::ObjectID::untracked) {
delete m_Rec;
delete m_Sim;

  }
}

