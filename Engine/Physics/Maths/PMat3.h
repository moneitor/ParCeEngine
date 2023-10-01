#pragma once

#include "Core.h"

#include "PVec3.h"

/*
M = |e11, e12, e13|
    |e21, e22, e23|
    |e31, e32, e33|

row0 = (e11, e12, e13)
row1 = (e21, e22, e23)
row2 = (e31, e32, e33)
*/

class pMat3
{
public:
    pMat3();
    pMat3(const pMat3 &other);
    pMat3(const pVec3 &row0, const pVec3 &row1, const pVec3 &row2);      
    pMat3(float a11, float a12, float a13,
          float a21, float a22, float a23,
          float a31, float a32, float a33 );

    ~pMat3() = default;

    pVec3 GetRow0() const;
    pVec3 GetRow1() const;
    pVec3 GetRow2() const;

    void SetXX(float value);
    void SetXY(float value);
    void SetXZ(float value);
    void SetYX(float value);
    void SetYY(float value);
    void SetYZ(float value);
    void SetZX(float value);
    void SetZY(float value);
    void SetZZ(float value);

    float Determinant() const;
    inline pMat3 Transpose() const;
    inline pMat3 Invert() const;

    pMat3 & operator = (const pMat3 &other);  
    float operator[](const int value);
    inline const pMat3 & operator += (const pMat3 &other);  
    inline const pMat3 & operator -= (const pMat3 &other);  
    inline const pMat3 & operator *= (const float value);  
    inline const pMat3 & operator *= (const pMat3 &other);  
    inline const pMat3 & operator /= (const float value);  
    inline const pMat3 operator * (const pMat3 &other);
    inline const pMat3 operator * (const pVec3 &vec);

    friend pVec3 operator * (const pMat3 &mat, const pVec3 &vec);
    friend pVec3 operator * (const pVec3 &vec, const pMat3 &mat);

private:
    float e11, e12, e13, 
          e21, e22, e23, 
          e31, e32, e33;

    float elements[9];
};

inline pVec3 operator * (const pMat3 &mat, const pVec3 &vec);
inline pVec3 operator * (const pVec3 &vec, const pMat3 &mat);