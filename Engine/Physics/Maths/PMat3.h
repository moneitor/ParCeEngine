#pragma once

#include "Core.h"
#include "PVec3.h"
#include "PMat2.h"
#include <vector>



class pMat3
{
public:   
    float *operator[] (int value);    

    pMat3();
    pMat3(const pMat3 &other);
    pMat3(float a11, float a12, float a13,
          float a21, float a22, float a23,
          float a31, float a32, float a33
          );
    pMat3(const pVec3 &row0, const pVec3 &row1, const pVec3 &row2);      

    ~pMat3() = default;

    pVec3 GetRow0() const;
    pVec3 GetRow1() const;
    pVec3 GetRow2() const;

    pMat3 Transpose() const;
    pMat3 Invert() const;

    pMat3 & operator = (const pMat3 &other);  
    const pMat3 operator * (const float value);
    const pMat3 operator * (const pVec3 &vec);
    const pMat3 operator * (const pMat3 &other);
    const pMat3 & operator += (const pMat3 &other);  
    const pMat3 & operator -= (const pMat3 &other);  
    const pMat3 & operator *= (const float value);  
    const pMat3 & operator *= (const pMat3 &other);  
    const pMat3 & operator /= (const float value);  

    void ToEulerAngles(float &yaw, float &pitch, float &roll);

    friend pMat3 operator * (const pMat3 &A, const pMat3 &B);
    friend pVec3 operator * (const pMat3 &mat, const pVec3 &vec);
    friend pVec3 operator * (const pVec3 &vec, const pMat3 &mat);

    friend pMat3 Transpose(const pMat3 &mat);
    friend float Determinant(const pMat3& mat);
    friend pMat2 Cut(const pMat3 &mat, int row, int col);  
    friend pMat3 Minor(const pMat3 &mat);
    friend pMat3 Cofactor(const pMat3 &mat);
    friend pMat3 Adjugate(const pMat3 &mat);
    friend pMat3 Inverse(const pMat3 &mat);

    friend pMat3 XRotation3(float angle);
    friend pMat3 YRotation3(float angle);
    friend pMat3 ZRotation3(float angle);
    friend pMat3 Rotation3(float pitch, float yaw, float roll);
    friend pMat3 RotationAxis3(const pVec3 &axis, float angle);

    union
    {
        struct
        {
            float e11, e12, e13, 
                  e21, e22, e23, 
                  e31, e32, e33;
        };
        float data[9];
    };

      
};

pMat3 operator * (const pMat3 &A, const pMat3 &B);
pVec3 operator * (const pVec3 &vec, const pMat3 &mat);
pVec3 operator * (const pMat3 &mat, const pVec3 &vec);


pMat3 Transpose(const pMat3 &mat);
pMat2 Cut(const pMat3 &mat, int row, int col);   
pMat3 Minor(const pMat3 &mat);
pMat3 Cofactor(const pMat3 &mat);
float Determinant(const pMat3& mat);
pMat3 Adjugate(const pMat3 &mat);
pMat3 Inverse(const pMat3 &mat);


pMat3 XRotation3(float angle);
pMat3 YRotation3(float angle);
pMat3 ZRotation3(float angle);
pMat3 Rotation3(float pitch, float yaw, float roll);
pMat3 RotationAxis3(const pVec3 &axis, float angle);



