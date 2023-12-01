#pragma once

#include "./PRBDBody.h"

struct pImpactData
{
    pRBDBody *aBody;
    pRBDBody *bBody;
    
    pVec3 start;
    pVec3 end;

    pVec3 collisionPosition;
    pVec3 collisionNormal;

    float collisionDepth;

    pImpactData() = default;
    ~pImpactData() = default;
};