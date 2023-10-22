#pragma once

#include "Maths/PVec3.h"

class PParticle
{
public:
    PParticle();
    PParticle(const pVec3 &pos);
    PParticle(float px, float py, float pz);
    PParticle(const pVec3 &pos, const pVec3 &vel);
    PParticle(float px, float py, float pz, float vx, float vy, float vz);
    ~PParticle();

    pVec3 GetPosition();
    void SetPosition(const pVec3 &pos);
    void SetPosition(float x, float y, float z);

    pVec3 GetVelocity();
    void SetVelocity(const pVec3 &vel);
    void SetVelocity(float x, float y, float z);

    void Update();

private:
    pVec3 position;
    pVec3 velocity;
    pVec3 acceleration;
    float mass;
};