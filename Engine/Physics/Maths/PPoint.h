#pragma once

#include "Core.h"
#include "PVec3.h"

#include <array>

class pPoint
{
public:
    pPoint();
    pPoint(std::array<float, 3> values);
    pPoint(const float value);
    pPoint(const float x_, const float y_, const float z_, const float w_);
    pPoint(const pPoint &other);
    pPoint(const pPoint &other, float w_);

    ~pPoint() = default;

    float Magnitude() const;
    float MagnitudeSq() const;
    pPoint Normalize() const;
    float Dot(const pPoint &other) const;

    float GetX() const;
    float GetY() const;
    float GetZ() const;
    float GetW() const;

    void SetX(float value);
    void SetY(float value);
    void SetZ(float value);
    void SetW(float value);

    float operator[](const unsigned int value);
    pPoint &operator = (const pPoint &other);
    bool operator == (const pPoint &other) const;
    bool operator != (const pPoint &other) const;
    inline pPoint operator + (const pPoint &other);
    inline pPoint operator - (const pPoint &other);
    inline pPoint operator * (float scalar);
    inline pPoint operator * (const pPoint &other);
    inline pPoint operator / (float scalar);
    inline pPoint &operator += (const pPoint &other);
    inline pPoint &operator -= (const pPoint &other);
    inline pPoint &operator *= (float scalar);
    inline pPoint &operator /= (float scalar);

    friend float PointDot(const pPoint &v1, const pPoint &v2);


private:
    float x, y, z, w;
};

float PointDot(const pPoint &v1, const pPoint &v2);

