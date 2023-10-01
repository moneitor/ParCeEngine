#pragma once

#include "Core.h"

#include <array>

class pVec4
{
public:
    pVec4();
    pVec4(std::array<float, 3> values);
    pVec4(const float value);
    pVec4(const float x_, const float y_, const float z_, const float w_);
    pVec4(const pVec4 &other);

    ~pVec4() = default;

    float Magnitude() const;
    float MagnitudeSq() const;
    pVec4 Normalize() const;
    float Dot(const pVec4 &other) const;

    float GetX() const;
    float GetY() const;
    float GetZ() const;
    float GetW() const;

    float operator[](const unsigned int value);
    pVec4 &operator = (const pVec4 &other);
    bool operator == (const pVec4 &other) const;
    bool operator != (const pVec4 &other) const;
    inline pVec4 operator + (const pVec4 &other);
    inline pVec4 operator - (const pVec4 &other);
    inline pVec4 operator * (float scalar);
    inline pVec4 operator * (const pVec4 &other);
    inline pVec4 operator / (float scalar);
    inline pVec4 &operator += (const pVec4 &other);
    inline pVec4 &operator -= (const pVec4 &other);
    inline pVec4 &operator *= (float scalar);
    inline pVec4 &operator /= (float scalar);

    friend float Dot(const pVec4 &v1, const pVec4 &v2);


private:
    float x, y, z, w;
};

float Dot(const pVec4 &v1, const pVec4 &v2);

