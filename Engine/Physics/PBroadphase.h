#pragma once

#include "./PRBDBody.h"
#include "./Maths/PVec3.h"
#include "./Primitives/PBounds.h"

#include <vector>


struct CollisionPair
{
    int a, b;
    bool operator==(const CollisionPair &other) const
    {
        return ( ( (a == other.a) && (b == other.b) ) || ( ( a == other.b)  && ( b == other.a) ) );
    }

    bool operator!=(const CollisionPair &other) const
    {
        return !(*this == other);
    }
};


void BroadPhase(std::vector<pRBDBody*> rbds, int num, std::vector< CollisionPair > &finalPairs, float dt_sec ) ;