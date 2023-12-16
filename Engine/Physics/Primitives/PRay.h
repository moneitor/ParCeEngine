#pragma once
#include "../Maths/PVec3.h"

class pRay
{
public:
    pRay(const pVec3 &orig, const pVec3 &dir);
    ~pRay();

    pRay FromPoints(const pVec3 &orig, const pVec3 &end);

    pVec3 GetDirection() const;
    pVec3 GetOrigin() const;

private:
    pVec3 orig;
    pVec3 direction;

};