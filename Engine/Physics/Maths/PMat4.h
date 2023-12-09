#pragma once

#include "Core.h"
#include "PVec4.h"
#include "PVec4.h"
#include "PPoint.h"
#include "PMat3.h"
#include <vector>



class pMat4
{
public:   
    float *operator[] (int value);    

    pMat4();
    pMat4(const pMat4 &other);
    pMat4(float a11, float a12, float a13, float a14,
          float a21, float a22, float a23, float a24,
          float a31, float a32, float a33, float a34,
          float a41, float a42, float a43, float a44
          );
    pMat4(const pVec4 &row0, const pVec4 &row1, const pVec4 &row2, const pVec4 &row3);      

    ~pMat4() = default;

    pVec4 GetRow0() const;
    pVec4 GetRow1() const;
    pVec4 GetRow2() const;
    pVec4 GetRow3() const;

    pMat3 Minor(const int i, const int j) const;
    float Determinant() const;
    pMat4 Transpose() const;
    pMat4 Invert() const;

    pMat4 & operator = (const pMat4 &other);  

    const pMat4 operator * (const float value);
    const pMat4 operator * (const pVec4 &vec);
    const pMat4 operator * (const pMat4 &other);

    const pMat4 & operator += (const pMat4 &other);  
    const pMat4 & operator -= (const pMat4 &other);  
    const pMat4 & operator *= (const float value);  
    const pMat4 & operator *= (const pMat4 &other);  
    const pMat4 & operator /= (const float value);  

    friend pMat4 operator * (const pMat4 &A, const pMat4 &B);
    friend pPoint operator * (const pPoint &point, const pMat4 &mat);
    friend pVec3 operator * (const pVec3 &vec, const pMat4 &mat);
    friend pVec3 operator * (const pMat4 &mat, const pVec4 &vec);

    friend pMat4 Transpose(const pMat4 &mat);
    friend pMat3 Cut(const pMat4&mat, int row, int col);   
    friend pMat4 Minor(const pMat4 &mat);
    friend pMat4 Cofactor(const pMat4 &mat);
    friend float Determinant(const pMat4& mat);
    friend pMat4 Adjugate(const pMat4 &mat);
    friend pMat4 Inverse(const pMat4 &mat);

    friend void Translate(pMat4 &mat, float x, float y, float z);
    friend void Translate(pMat4 &mat, const pVec3 &vec);
    friend pMat4 Translate(float x, float y, float z);
    friend pMat4 Translate(const pVec3 &vec);
    friend pVec3 GetTranslation(const pMat4 &mat);

    friend void Scale(pMat4 &mat, float x, float y, float z);
    friend void Scale(pMat4 &mat, const pVec3 &vec);
    friend pMat4 Scale(float x, float y, float z);
    friend pMat4 Scale(const pVec3 &vec);
    friend pVec3 GetScale(const pMat4 &mat);
    friend pMat4 RotationAxis4(const pVec3 &axis, float angle);


protected:
    union
    {
        struct
        {
            float e11, e12, e13, e14,
                  e21, e22, e23, e24,
                  e31, e32, e33, e34,
                  e41, e42, e43, e44;
        };
        float data[16];
    };
};

pMat4 operator * (const pMat4 &A, const pMat4 &B);
pPoint operator * (const pPoint &point, const pMat4 &mat);
pVec3 operator * (const pVec3 &vec, const pMat4 &mat);
pVec3 operator * (const pMat4 &mat, const pVec4 &vec);

pMat4 Transpose(const pMat4 &mat);
pMat3 Cut(const pMat4&mat, int row, int col);   
pMat4 Minor(const pMat4 &mat);
pMat4 Cofactor(const pMat4 &mat);
float Determinant(const pMat4 &mat);
pMat4 Adjugate(const pMat4 &mat);
pMat4 Inverse(const pMat4 &mat);

void Translate(pMat4 &mat, float x, float y, float z);
void Translate(pMat4 &mat, const pVec3 &vec);
pMat4 Translate(float x, float y, float z);
pMat4 Translate(const pVec3 &vec);
pVec3 GetTranslation(const pMat4 &mat);

void Scale(pMat4 &mat, float x, float y, float z);
void Scale(pMat4 &mat, const pVec3 &vec);
pMat4 Scale(float x, float y, float z);
pMat4 Scale(const pVec3 &vec);
pVec3 GetScale(const pMat4 &mat);

pMat4 XRotation4(float angle);
pMat4 YRotation4(float angle);
pMat4 ZRotation4(float angle);
pMat4 Rotation4(float pitch, float yaw, float roll);
pMat4 RotationAxis4(const pVec3 &axis, float angle);

