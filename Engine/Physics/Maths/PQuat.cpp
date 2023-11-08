#include "PQuat.h"

pQuat::pQuat()
: w{0}, x{0}, y{0}, z{0}
{
}

pQuat::pQuat(const pQuat &other)
:w{other.w}, x{other.x}, y{other.y}, z{other.z}
{
}

pQuat::pQuat(float x_, float y_, float z_, float w_)
:w{w_}, x{x_}, y{y_}, z{z_}
{
}

pQuat::pQuat(const pVec3 &vec, const float angle)
:w{angle}, x{vec.GetX()}, y{vec.GetY()}, z{vec.GetZ()}
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
    temp.w = (w * other.w) - (x * other.x) - (y * other.y) - (z * other.z);
    temp.y = (x * other.w) + (w * other.x) + (y * other.z) - (z * other.y);
    temp.z = (y * other.w) + (w * other.y) + (z * other.x) - (x * other.z);
    temp.z = (z * other.w) + (w * other.z) + (x * other.y) - (y * other.x); 

    return temp;
}

pQuat &pQuat::operator*=(const pQuat &other)
{
    pQuat temp = *this * other;
    this->w = temp.w;
    this->x = temp.x;
    this->y = temp.y;
    this->z = temp.z;

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
    return ((w*w) + (x*x) + (y*y) + (z*z));
}

pQuat pQuat::Normalize() const
{    
    float tempX = 0.0f, tempY = 0.0f, tempZ = 0.0f, tempW = 0.0f;

    float inverseMag = 1.0f / w*w + x*x + y*y + z*z;

    if (compareDouble(inverseMag, 0.0f))
    {
        tempW = 1.0f;
        return pQuat(tempX, tempY, tempZ, tempW);
    }

    tempW = w * inverseMag;
    tempX = x * inverseMag;
    tempY = y * inverseMag;
    tempZ = z * inverseMag;    

    return pQuat(tempX, tempY, tempZ, tempW);
}

pMat3 pQuat::ToMatrix() const
{
    float e11 = 1 - (2*y*y + 2*z*z);
    float e12 = 2*x*y + 2*z*w;
    float e13 = 2*x*z - 2*y*w;

    float e21 = 2*x*y - 2*z*w;
    float e22 = 1 - (2*x*x + 2*z*z);
    float e23 = 2*y*z + 2*x*w;

    float e31 = 2*x*z + 2*y*w;
    float e32 = 2*y*z -2*x*w;
    float e33 = 1 - (2*x*x + 2*y*y);

    pMat3 out = pMat3(e11, e12, e13,
                      e21, e22, e23,
                      e31, e32, e33);
                    
    return out;
}

pQuat pQuat::Invert() const
{
    float invMagSquared = 1.0f/MagnitudeSq();
    pQuat temp;
    temp.w = w * invMagSquared;
    temp.x = -x * invMagSquared;
    temp.y = -y * invMagSquared;
    temp.z = -z * invMagSquared;

    return temp;
}

pVec3 pQuat::RotateVector(pVec3 const &vec) const
{
    pQuat temp1 = pQuat(vec, 0.0f);
    pQuat temp2 = *this * temp1 * Invert();
    return pVec3(temp2[0], temp2[1], temp2[2]);
}

pQuat operator*(const pQuat &q1, const pQuat &q2)
{
    pQuat temp;
    temp.w = (q1.w * q2.w) - (q1.x * q2.x) - (q1.y * q2.y) - (q1.z * q2.z);
    temp.y = (q1.x * q2.w) + (q1.w * q2.x) + (q1.y * q2.z) - (q1.z * q2.y);
    temp.z = (q1.y * q2.w) + (q1.w * q2.y) + (q1.z * q2.x) - (q1.x * q2.z);
    temp.z = (q1.z * q2.w) + (q1.w * q2.z) + (q1.x * q2.y) - (q1.y * q2.x); 

    return temp;
}

pVec3 operator*(const pVec3 &v1, const pQuat &q2)
{
    pQuat temp1 = pQuat(v1, 0.0f);
    pQuat temp2 = q2 * temp1 * q2.Invert();
    return pVec3(temp2[0], temp2[1], temp2[2]);
}
