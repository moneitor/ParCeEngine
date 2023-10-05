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

private:
    pVec3 position;
    pVec3 velocity;
    pVec3 acceleration;
    float mass;
};