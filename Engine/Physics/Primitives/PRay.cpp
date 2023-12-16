#include "PRay.h"

pRay::pRay(const pVec3 &orig, const pVec3 &dir)
:orig{orig}, direction{dir.Normalize()}
{
}

pRay::~pRay()
{
}

pRay pRay::FromPoints(const pVec3 &orig, const pVec3 &end)
{
    return pRay(orig, (end - orig).Normalize());
}

pVec3 pRay::GetDirection() const
{
    return this->direction;
}

pVec3 pRay::GetOrigin() const
{
    return this->orig;
}
