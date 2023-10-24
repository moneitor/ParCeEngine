#include "PForces.h"



pForce::pForce()
{
}

pForce::~pForce()
{
}

Gravity::Gravity()
{
}

Gravity::~Gravity()
{
}

void Gravity::UpdateForce(pRBDObject *rbd)
{
    rbd->AddForce(pVec3(0.0f, -9.8f, 0.0f));
}



Wind::Wind(const pVec3 &vec)
    :vec{vec}
{
}

void Wind::UpdateForce(pRBDObject *rbd)
{
    rbd->AddForce(vec);
}


Wind::~Wind()
{
}



Drag::Drag(float value_)
:value{value_}
{
}

Drag::~Drag()
{
}

void Drag::UpdateForce(pRBDObject *rbd)
{
    pVec3 dragForce = pVec3(0.0f, 0.0f, 0.0f);
    if(rbd->Vel().MagnitudeSq() > 0.0f)
    {
        pVec3 dragDirection = rbd->Vel().Normalize() * -1;
        float dragMagnitude = rbd->Vel().MagnitudeSq() * value;
        dragForce = dragDirection * dragMagnitude;

        rbd->AddForce(dragForce);
    }    
}
