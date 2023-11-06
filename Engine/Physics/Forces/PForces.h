#pragma once

#include "../Maths/PVec3.h"
#include "../PRBDBody.h"


class pForce
{
public:
    pForce();
    virtual ~pForce();

    virtual void UpdateForce(pRBDBody *rbd) = 0;


private:
    pVec3 force;

};



class Gravity
    :public pForce
{
public:
    Gravity();
    ~Gravity();
    void UpdateForce(pRBDBody *rbd) override;       
  
};



class WindForce
    :public pForce
{
public:
    WindForce(const pVec3 &vec);
    ~WindForce();
    void UpdateForce(pRBDBody *rbd) override;     
    

private:
    pVec3 vec;
};




class DragForce
    :public pForce
{
public:
    DragForce(float value);
    ~DragForce();
    void UpdateForce(pRBDBody *rbd) override;       

private:
    float value;
};




class SpringForce
    :public pForce
{
public:
    SpringForce(pRBDBody *rbd, const pVec3 &anchor, float restlength, float k,  float c);
    SpringForce(pRBDBody *rbd0, pRBDBody *rbd1, float restlength, float k,  float c);
    ~SpringForce();
    void UpdateForce(pRBDBody *rbd) override;     
    void ApplySpring();

    pVec3 CalculateForce(pRBDBody *rbd0_, pRBDBody *rbd1_);

private:
    pVec3 anchor;
    float value;
    float restlength;
    float k, c;
    pRBDBody *rbd0;
    pRBDBody *rbd1;
};