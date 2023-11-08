#pragma once

#include "Core.h"
#include "PVec3.h"
#include "PMat3.h"

class pQuat
{
public:
    pQuat();
    pQuat(const pQuat &other);
    pQuat(float x_, float y_, float z_, float w_);
    pQuat(const pVec3 &vec, const float angle);

    ~pQuat();

    pQuat operator*(const pQuat &other);
    pQuat &operator*=(const pQuat &other);

    float operator[](const int i);

    float Magnitude() const;
    float MagnitudeSq() const;

    pQuat Normalize() const;
    pMat3 ToMatrix() const;

    pQuat Invert() const;

    pVec3 RotateVector(pVec3 const &vec) const;

    friend pQuat operator * (const pQuat &q1, const pQuat &q2);
    friend pVec3 operator * (const pVec3 &v1, const pQuat &q2);


private:
    public:
    union
    {
        struct
        {
            float w, x, y, z;
        };
        float data[4];
    };
};

pQuat operator * (const pQuat &q1, const pQuat &q2);
pVec3 operator * (const pVec3 &v1, const pQuat &q2);