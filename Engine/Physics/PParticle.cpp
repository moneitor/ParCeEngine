#include "PParticle.h"

PParticle::PParticle()
    :position{pVec3(0.0f, 0.0f, 0.0f)}, mass{1.0f}
{
}

PParticle::PParticle(const pVec3 &pos)
    :position{pos}, mass{1.0f}
{
}

PParticle::PParticle(float px, float py, float pz)
    :position{pVec3(px, py, pz)}, mass{1.0f}
{
}

PParticle::PParticle(const pVec3 &pos, const pVec3 &vel)
    :position{pos}, velocity{vel}, mass{1.0f}
{
}

PParticle::PParticle(float px, float py, float pz, float vx, float vy, float vz)
    :position{pVec3(px, py, pz)}, velocity{pVec3(vx, vy, vz)}, mass{1.0f}
{
}

PParticle::~PParticle()
{
}

pVec3 PParticle::GetPosition()
{
    return this->position;
}
