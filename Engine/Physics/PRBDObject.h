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

    pVec3 Accel();
    void SetAcceleration(const pVec3 &accel);
    void SetAcceleration(float x, float y, float z);

    void SetElasticity(float elasticity);
    float Elasticity();

    void AddForce(const pVec3 &force);
    void CleanForces();


    void Integrate(float dt);

private:
    assModel *object;

    pVec3 position;
    pVec3 vel;
    pVec3 acceleration;
    pVec3 netForce;

    float elasticity;
    float mass;
};