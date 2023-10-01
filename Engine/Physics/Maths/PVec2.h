#pragma once

#include "Core.h"

#include <array>

class pVec2
{
public:
    pVec2();
    pVec2(std::array<float, 2> values);
    pVec2(const float value);
    pVec2(const float x_, const float y_);
    pVec2(const pVec2 &other);

    ~pVec2() = default;

    float Magnitude() const;
    float MagnitudeSq() const;
    pVec2 Normalize() const;
    float Dot(const pVec2 &other) const;
    float Angle(const pVec2 &other) const;

    float GetX() const;
    float GetY() const;

    float operator[](const unsigned int value);
    pVec2 &operator = (const pVec2 &other);
    bool operator == (const pVec2 &other) const;
    bool operator != (const pVec2 &other) const;
    pVec2 operator + (const pVec2 &other);
    pVec2 operator - (const pVec2 &other);
    pVec2 operator * (float scalar);
    pVec2 operator * (const pVec2 &other);
    pVec2 operator / (float scalar);
    pVec2 operator += (const pVec2 &other);
    pVec2 operator -= (const pVec2 &other);
    pVec2 operator *= (float scalar);
    pVec2 operator /= (float scalar);

private:
    float x, y;

};
