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
    pQuat &operator*=(const float value);

    pVec3 operator*(const pVec3 &other);
    pMat3 operator*(const pMat3 &other);

    float operator[](const int i);

    float Magnitude() const;
    float MagnitudeSq() const;

    pQuat Normalize() const;
    pMat3 ToMatrix() const;

    void Invert() const;


private:
    public:
    union
    {
        struct
        {
            float x, y, z, w;
        };
        float data[4];
    };
};