#pragma once

#include "Maths/PMat3.h"
#include "Maths/PMat4.h"
#include "../Graphics/Entity/AssModel.h"

class pRBDObject
{
public:
    pRBDObject();
    pRBDObject(const pVec3 &pos);
    pRBDObject(assModel *model, const pVec3 &pos);

    assModel *GetObject();
    pVec3 GetPosition();

private:
    pVec3 position;
    assModel *object;
};