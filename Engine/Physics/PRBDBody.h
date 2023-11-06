#pragma once

#include "Maths/PQuat.h"
#include "Maths/PMat3.h"
#include "Maths/PMat4.h"
#include "./PRBDShape.h"
#include "../Graphics/Entity/AssModel.h"

class pRBDBody
{
public:
    pRBDBody(pRBDShape *shape);
    pRBDBody(pRBDShape *shape, const pVec3 &pos);
    ~pRBDBody();

    pRBDShape *GetShape();

    pVec3 Pos();
    void SetPosition(const pVec3 &pos);
    void SetPosition(float x, float y, float z);

    pVec3 Vel();
    void SetVelocity(const pVec3 &vel);
    void SetVelocity(float x, float y, float z);

    pVec3 Accel();
    void SetAcceleration(const pVec3 &accel);
    void SetAcceleration(float x, float y, float z);

    float Elasticity();
    void SetElasticity(float elasticity);

    float Mass();

    void AddForce(const pVec3 &force);
    void CleanForces();

    void SetActive(bool value);

    void Integrate(float dt);

    void ChunkMeshVertices();

private:
    pRBDShape *rbdShape;

    pVec3 position;
    pVec3 velocity;
    pVec3 acceleration;
    pVec3 netForce;
    pQuat rotation;

    float elasticity;
    float mass;
    float invMass;

    bool active;
};