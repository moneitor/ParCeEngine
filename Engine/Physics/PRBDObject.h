#pragma once

#include "Maths/PMat3.h"
#include "Maths/PMat4.h"
#include "../Graphics/Entity/AssModel.h"

class pRBDObject
{
public:
    pRBDObject();
    pRBDObject(const pVec3 &pos);
    pRBDObject(assModel *model);
    pRBDObject(assModel *model, const pVec3 &pos);

    assModel *GetObject();

    pVec3 Pos();
    void SetPosition(const pVec3 &pos);
    void SetPosition(float x, float y, float z);

    pVec3 Vel();
    void SetVelocity(const pVec3 &vel);
    void SetVelocity(float x, float y, float z);

    void SetElasticity(float elasticity);
    float Elasticity();

    void Update();

private:
    assModel *object;

    pVec3 position;
    pVec3 velocity;
    pVec3 acceleration;
    float elasticity;
    float mass;
};