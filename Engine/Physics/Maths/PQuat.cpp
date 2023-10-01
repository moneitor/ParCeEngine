#include "PQuat.h"

pQuat::pQuat()
:x{0}, y{0}, z{0}, w{0}
{
}

pQuat::pQuat(const pQuat &other)
:x{other.x}, y{other.y}, z{other.z}, w{other.w}
{
}

pQuat::pQuat(float x_, float y_, float z_, float w_)
:x{x_}, y{y_}, z{z_}, w{w_}
{
}

pQuat::pQuat(const pVec3 &vec, const float angle)
:x{vec.GetX()}, y{vec.GetY()}, z{vec.GetZ()}, w{angle}
{
}

pQuat::~pQuat()
{
}

pQuat pQuat::operator*(const pQuat &other)
{
    pQuat temp;
    temp.y = (x * other.w) + (w * other.x) + (y * other.z) - (z * other.y);
    temp.z = (y * other.w) + (w * other.y) + (z * other.x) - (x * other.z);
    temp.z = (z * other.w) + (w * other.z) + (x * other.y) - (y * other.x); 
    temp.w = (w * other.w) - (x * other.x) - (y * other.y) - (z * other.z);

    return temp;
}

pQuat &pQuat::operator*=(const pQuat &other)
{
    pQuat temp = *this * other;
    this->x = temp.x;
    this->y = temp.y;
    this->z = temp.z;
    this->w = temp.w;

    return *this;
}

pQuat &pQuat::operator*=(const float value)
{
    return *this;
}
