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

void Gravity::UpdateForce(pRBDBody *rbd)
{
    rbd->AddForce(pVec3(0.0f, -9.8f, 0.0f) * rbd->Mass()) ;
}



///////////// WIND ///////////

WindForce::WindForce(const pVec3 &vec)
    :vec{vec}
{
}

void WindForce::UpdateForce(pRBDBody *rbd)
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

void DragForce::UpdateForce(pRBDBody *rbd)
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

SpringForce::SpringForce(pRBDBody *rbd, const pVec3 &anchor_, float restlength_, float k_, float c_)
:anchor{anchor_},
restlength{restlength_},
k{k_},
c{c_},
rbd0{rbd},
rbd1{nullptr}
{
}

SpringForce::SpringForce(pRBDBody *rbd0_, pRBDBody *rbd1_, float restlength_, float k_, float c_)
:anchor{pVec3(0.0f,0.0f,0.0f)},
restlength{restlength_},
k{k_},
c{c_},
rbd0{rbd0_},
rbd1{rbd1_}
{
}

SpringForce::~SpringForce()
{
    delete(rbd0);
    delete(rbd1);
}

void SpringForce::UpdateForce(pRBDBody *rbd)
{
}

void SpringForce::ApplySpring()
{
    if(rbd1 == nullptr)
    {
        pVec3 d = rbd0->Pos() - anchor;
        float distance = d.Magnitude();
        float displacement = distance - restlength;

        pVec3 direction = d.Normalize();
        float magnitude = -k * displacement;

        pVec3 dampening = rbd0->Vel() * -c;
        pVec3 springForce = direction * magnitude; 

        rbd0->AddForce(springForce + dampening);
    } 
    else 
    {
        pVec3 force0 = CalculateForce(rbd0, rbd1);
        pVec3 force1 = CalculateForce(rbd1, rbd0);

        rbd0->AddForce(force0);
        rbd1->AddForce(force1);
    }
}

pVec3 SpringForce::CalculateForce(pRBDBody *rbd0_, pRBDBody *rbd1_)
{
    pVec3 d = (rbd0_->Pos()) - (rbd1_->Pos());
    float distance = d.Magnitude();
    float displacement = distance - restlength;

    pVec3 direction = d.Normalize();
    float magnitude = -k * displacement;

    pVec3 springForce = direction * magnitude; 

    return(springForce);
}
