#pragma once

#include "../Maths/PVec3.h"
#include "../PRBDObject.h"


class pForce
{
public:
    pForce();
    virtual ~pForce();

    virtual void UpdateForce(pRBDObject *rbd) = 0;

private:
    pVec3 force;

};



class Gravity
    :public pForce
{
public:
    Gravity();
    ~Gravity();
    void UpdateForce(pRBDObject *rbd) override;       
};



class Wind
    :public pForce
{
public:
    Wind(const pVec3 &vec);
    ~Wind();
    void UpdateForce(pRBDObject *rbd) override;     

private:
    pVec3 vec;
};




class Drag
    :public pForce
{
public:
    Drag(float value);
    ~Drag();
    void UpdateForce(pRBDObject *rbd) override;     

private:
    float value;
};