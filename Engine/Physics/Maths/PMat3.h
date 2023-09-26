#pragma once

#include "Core.h"

#include "PVec3.h"

class pMat3
{
public:
    pMat3();
    pMat3(const pMat3 &other);
    pMat3(const pVec3 &row0, const pVec3 &row1, const pVec3 &row2);      
    pMat3(float a11, float a12, float a13,
          float a21, float a22, float a23,
          float a31, float a32, float a33 );

    float Determinant() const;
    inline pMat3 Transpose() const;
    inline pMat3 Invert() const;

    pMat3 & operator = (const pMat3 &other);  
    float operator[](const int value);
    inline const pMat3 & operator += (const pMat3 &other);  
    inline const pMat3 & operator *= (const float value);  
    inline const pMat3 & operator *= (const pMat3 &other);  

private:
    float e11, e12, e13, e21, e22, e23, e31, e32, e33;
    pVec3 row0, row1, row2;
};