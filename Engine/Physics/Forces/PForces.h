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



class WindForce
    :public pForce
{
public:
    WindForce(const pVec3 &vec);
    ~WindForce();
    void UpdateForce(pRBDObject *rbd) override;     
    

private:
    pVec3 vec;
};




class DragForce
    :public pForce
{
public:
    DragForce(float value);
    ~DragForce();
    void UpdateForce(pRBDObject *rbd) override;       

private:
    float value;
};




class SpringForce
    :public pForce
{
public:
    SpringForce(pRBDObject *rbd, const pVec3 &anchor, float restlength, float k);
    ~SpringForce();
    void UpdateForce(pRBDObject *rbd) override;     

private:
    float value;
};