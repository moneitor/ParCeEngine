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



///////////// WIND ///////////

WindForce::WindForce(const pVec3 &vec)
    :vec{vec}
{
}

void WindForce::UpdateForce(pRBDObject *rbd)
{
    rbd->AddForce(vec);
}



WindForce::~WindForce()
{
}



////////////// DRAG   //////////////////

DragForce::DragForce(float value_)
:value{value_}
{
}

DragForce::~DragForce()
{
}

void DragForce::UpdateForce(pRBDObject *rbd)
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



/////////// SPRING ////////////////

SpringForce::SpringForce(pRBDObject *rbd, const pVec3 &anchor, float restlength, float k)
{
    pVec3 d = rbd->Pos() - anchor;
    float distance = d.Magnitude();
    float displacement = distance - restlength;

    pVec3 direction = d.Normalize();
    float magnitude = -k * displacement;

    pVec3 springForce = direction * magnitude;

    rbd->AddForce(springForce);
}

SpringForce::~SpringForce()
{
}

void SpringForce::UpdateForce(pRBDObject *rbd)
{
}

