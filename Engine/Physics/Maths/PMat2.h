#pragma once

#include "Core.h"
#include "PVec2.h"
#include <vector>



class pMat2
{
public:   
    float *operator[] (int value);    

    pMat2();
    pMat2(const pMat2 &other);
    pMat2(float a11, float a12, float a21, float a22);
    pMat2(const pVec2 &row0, const pVec2 &row1);      

    ~pMat2() = default;

    pVec2 GetRow0() const;
    pVec2 GetRow1() const;

    pMat2 Transpose() const;
    float Determinant() const;    
    inline pMat2 Invert() const;

    pMat2 & operator = (const pMat2 &other);  
    inline const pMat2 operator * (const float value);
    inline const pMat2 operator * (const pVec2 &vec);
    inline const pMat2 operator * (const pMat2 &other);
    inline const pMat2 & operator += (const pMat2 &other);  
    inline const pMat2 & operator -= (const pMat2 &other);  
    inline const pMat2 & operator *= (const float value);  
    inline const pMat2 & operator *= (const pMat2 &other);  
    inline const pMat2 & operator /= (const float value);  

    // FRIENDS
    friend pVec2 operator * (const pMat2 &mat, const pVec2 &vec);
    friend pVec2 operator * (const pVec2 &vec, const pMat2 &mat);
    friend pMat2 Transpose(const pMat2 &mat);
    friend float Determinant(const pMat2& mat);
    friend pMat2 Minor(const pMat2 &mat);
    friend pMat2 Cofactor(const pMat2 &mat);
    friend pMat2 Adjugate(const pMat2 &mat);
    friend pMat2 Inverse(const pMat2 &mat);


public:
    union
    {
        struct
        {
            float e11, e12, 
                  e21, e22;
        };
        float data[4];
    };
};

pMat2 Transpose(const pMat2 &mat);
float Determinant(const pMat2& mat);
pMat2 Minor(const pMat2 &mat);
pMat2 Cofactor(const pMat2 &mat);
pMat2 Adjugate(const pMat2 &mat);
pMat2 Inverse(const pMat2 &mat);