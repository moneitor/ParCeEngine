#pragma once

#include "Core.h"

#include <array>

class pVec3
{
public:
    pVec3();
    pVec3(std::array<float, 3> values);
    pVec3(const float value);
    pVec3(const float x_, const float y_, const float z_);
    pVec3(const pVec3 &other);

    ~pVec3() = default;

    float Magnitude() const;
    float MagnitudeSq() const;
    pVec3 Normalize() const;
    float Angle(const pVec3 &other) const;
    float Dot(const pVec3 &other) const;
    pVec3 Cross(const pVec3 &other) const;

    float GetX() const;
    float GetY() const;
    float GetZ() const;

    float operator[](const int value);
    pVec3 &operator = (const pVec3 &other);
    bool operator == (const pVec3 &other) const;
    bool operator != (const pVec3 &other) const;
    pVec3 operator + (const pVec3 &other);
    pVec3 operator - (const pVec3 &other);
    pVec3 operator * (float scalar);
    pVec3 operator * (const pVec3 &other);
    pVec3 operator / (float scalar);
    pVec3 &operator += (const pVec3 &other);
    pVec3 &operator -= (const pVec3 &other);
    pVec3 &operator *= (float scalar);
    pVec3 &operator /= (float scalar);

    friend pVec3 Cross(const pVec3 &v1, const pVec3 &v2);
    friend float Angle(const pVec3 &v1, const pVec3 &v2);
    friend pVec3 Projection(const pVec3 &v1, const pVec3 &v2);
    friend pVec3 Perpendicular(const pVec3 &v1, const pVec3 &v2);
    friend float Dot(const pVec3 &v1, const pVec3 &v2);
    friend pVec3 Reflection(const pVec3 &v1, const pVec3 &v2);

private:
    float x, y, z;
};

float Dot(const pVec3 &v1, const pVec3 &v2);
pVec3 Cross(const pVec3 &v1, const pVec3 &v2);
float Angle(const pVec3 &v1, const pVec3 &v2);
pVec3 Projection(const pVec3 &v1, const pVec3 &v2);
pVec3 Perpendicular(const pVec3 &v1, const pVec3 &v2);
pVec3 Reflection(const pVec3 &v1, const pVec3 &v2);