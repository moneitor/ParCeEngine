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

    pVec3 GetVector() const;

    pMat3 ToMatrix() const;

    void Normalize() const;
    void Invert() const;
    float Magnitude() const;
    float MagnitudeSq() const;

private:
    float x, y, z, w;
};