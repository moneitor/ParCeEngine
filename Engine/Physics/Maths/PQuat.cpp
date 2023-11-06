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
    const float halfAngle = 0.5 * angle;
    w = std::cos(halfAngle);

    const float halfSine = std::sin(halfAngle);

    pVec3 vecNorm = vec.Normalize();
    x = vecNorm[0] * halfSine;
    y = vecNorm[1] * halfSine;
    z = vecNorm[2] * halfSine;
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

float pQuat::operator[](const int i)
{
    return data[i];
}

float pQuat::Magnitude() const
{
    return std::sqrt(this->MagnitudeSq());
}

float pQuat::MagnitudeSq() const
{
    return ((x*x) + (y*y) + (z*z) + (w*w));
}

pQuat pQuat::Normalize() const
{    
    float tempX = 0.0f, tempY = 0.0f, tempZ = 0.0f, tempW = 0.0f;

    float inverseMag = 1.0f / this->Magnitude();
    if(!compareDouble(0.0f, inverseMag))
    {
        tempX = x * inverseMag;
        tempY = y * inverseMag;
        tempZ = z * inverseMag;
        tempW = w * inverseMag;
    }

    return pQuat(tempX, tempY, tempZ, tempW);
}
