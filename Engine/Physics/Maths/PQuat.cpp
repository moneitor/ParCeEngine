#include "PQuat.h"

pQuat::pQuat()
: w{0}, x{0}, y{0}, z{0}
{
}

pQuat::pQuat(const pQuat &other)
:w{other.w}, x{other.x}, y{other.y}, z{other.z}
{
}

pQuat::pQuat(float w_, float x_, float y_, float z_)
:w{w_}, x{x_}, y{y_}, z{z_}
{
}

pQuat::pQuat(const pVec3 &vec, const float angle)
:w{angle}, x{vec.GetX()}, y{vec.GetY()}, z{vec.GetZ()}
{
    const float halfAngle = 0.5 * angle;
    w = std::cosf(halfAngle);

    const float halfSine = std::sinf(halfAngle);

    pVec3 vecNorm = vec.Normalize();
    x = vecNorm[0] * halfSine;
    y = vecNorm[1] * halfSine;
    z = vecNorm[2] * halfSine;
}

pQuat::pQuat(float value)
:w{value}, x{0.0f}, y{0.0f}, z{0.0f}
{
}

pQuat::pQuat(glm::quat quat)
:w{quat.w}, x{quat.x}, y{quat.y}, z{quat.z}
{
}

pQuat::~pQuat()
{
}

pQuat pQuat::operator*(float value)
{
    return pQuat(w*value, x*value, y*value, z*value);
}

pQuat pQuat::operator*(const pQuat &other)
{
    double newW = w * other.w - x * other.x - y * other.y - z * other.z;
    double newX = w * other.x + x * other.w + y * other.z - z * other.y;
    double newY = w * other.y - x * other.z + y * other.w + z * other.x;
    double newZ = w * other.z + x * other.y - y * other.x + z * other.w;

    return pQuat(newW, newX, newY, newZ);
}

pQuat pQuat::operator*(const pVec3 &v1)
{
    float vx, vy, vz;
    
    vx = v1.GetX();
    vy = v1.GetY();
    vz = v1.GetZ();

    return pQuat( -(x*vx  +  y*vy  +  z*vz),
                   (w*vx  +  y*vz  -  z*vy),
                   (w*vy  +  z*vx  -  x*vx),
                   (w*vz  +  x*vy  -  y*vx) );
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

pQuat pQuat::operator+(const pQuat &other)
{
    return pQuat(w + other.w, x + other.x, y + other.y, z + other.z);
}

pQuat pQuat::operator-(const pQuat &other)
{
    return pQuat(w - other.w, x + other.x, y - other.y, z - other.z);
}

pQuat pQuat::operator/(float value)
{
    return pQuat(w/value, x/value, y/value, z/value);
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

    if (inverseMag == 0.0f)
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
    pMat3 out = pMat3();
    pVec3 row1, row2, row3;

    row1 = out.GetRow0();
    row2 = out.GetRow1();
    row3 = out.GetRow2();

    row1 = RotateVector(row1);
    row2 = RotateVector(row2);
    row3 = RotateVector(row3);

    out = pMat3(row1[0], row1[1], row1[2],
                row2[0], row2[1], row2[2],
                row3[0], row3[1], row3[2]);
                    
    return out;
}


pVec3 pQuat::ToEuler() const
{
    float roll = std::atan2(2.0f * (w * x + y * z), 1.0f - 2.0f * (x * x + y * y));

    // Pitch (Y-axis rotation)
    float pitch;

    // Avoid singularity at the poles
    float sinp = 2.0f * (w * y - z * x);
    if (std::abs(sinp) >= 1.0f) {
        pitch = std::copysign(M_PI / 2.0f, sinp); // Use +/-90 degrees if close to the poles
    } else {
        pitch = std::asin(sinp);
    }

    // Yaw (Z-axis rotation)
    float yaw = std::atan2(2.0f * (w * z + x * y), 1.0f - 2.0f * (y * y + z * z));

    return pVec3(roll, pitch, yaw);
}

void pQuat::SetW(float value)
{
    this->w = value;
}

void pQuat::SetX(float value)
{
    this->x = value;
}

void pQuat::SetY(float value)
{
    this->y = value;
}

void pQuat::SetZ(float value)
{
    this->z = value;
}

float pQuat::GetW() const
{
    return this->w;
}

float pQuat::GetX() const

{
    return this->x;
}

float pQuat::GetY() const
{
    return this->y;
}

float pQuat::GetZ() const
{
    return this->z;
}

float pQuat::GetAngle() const
{
    return 2.0f * std::acos(w);
}

pVec3 pQuat::GetAxis() const
{
    pVec3 v = pVec3(x,y,z);
    float m = v.Magnitude();

    if (m <= 0.01)
    {
        return pVec3(0.0f, 0.0f, 0.0f);
    }
    else
    {
        return pVec3(v.GetX()/m, v.GetY()/m, v.GetZ()/m);
    }
}

std::string pQuat::ToString() const
{
    std::string vec = "quat(" + std::to_string(this->w);
                vec += ", {" + std::to_string(this->x);
                vec += ", " + std::to_string(this->y);
                vec += ", " + std::to_string(this->z);
                vec += "})";

    return vec;
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

pVec3 pQuat::RotateVector(const pVec3 &vec) const
{
    pQuat temp1 = pQuat(vec, 0.0f);
    pQuat temp2 = *this * temp1 * Invert();
    return pVec3(temp2[0], temp2[1], temp2[2]);
}

pQuat pQuat::RotateByVector(const pVec3 &vec)
{

    // NewQ = Q + ( (dt/2)*w*Q )
    pQuat vecToQuat = pQuat(0.0f, vec.GetX(), vec.GetY(), vec.GetZ());
    pQuat thisQuat = *this;


    return thisQuat * vecToQuat;
}

pQuat pQuat::RotateByVector(const pVec3 &vec, float dt)
{
    pQuat vecToQuat = pQuat(0.0f, vec.GetX() * dt, vec.GetY() * dt, vec.GetZ() * dt);
    pQuat thisQuat = *this;
    vecToQuat *= thisQuat;
    thisQuat.w += vecToQuat.w * 0.5;
    thisQuat.x += vecToQuat.x * 0.5;
    thisQuat.y += vecToQuat.y * 0.5;
    thisQuat.z += vecToQuat.z * 0.5;
    return thisQuat;

}

pQuat operator*(const pQuat &q1, const pQuat &q2)
{
    double newW = q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z;
    double newX = q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y;
    double newY = q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x;
    double newZ = q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w;

    return pQuat(newW, newX, newY, newZ);
}

pQuat operator*(const pVec3 &v1, const pQuat &q)
{
    float vx, vy, vz, qx, qy, qz, qw;
    
    vx = v1.GetX();
    vy = v1.GetY();
    vz = v1.GetZ();

    qw = q.GetW();
    qx = q.GetX();
    qy = q.GetY();
    qz = q.GetZ();

    return pQuat( -(qx*vx  +  qy*vy  +  qz*vz),
                   (qw*vx  +  qz*vy  -  qy*vz),
                   (qw*vy  +  qx*vz  -  qz*vx),
                   (qw*vz  +  qy*vx  -  qx*vy) );

}

pQuat operator*(const pQuat &q, const pVec3 &v1)
{
    float vx, vy, vz, qx, qy, qz, qw;
    
    vx = v1.GetX();
    vy = v1.GetY();
    vz = v1.GetZ();

    qw = q.GetW();
    qx = q.GetX();
    qy = q.GetY();
    qz = q.GetZ();

    return pQuat( -(qx*vx  +  qy*vy  +  qz*vz),
                   (qw*vx  +  qy*vz  -  qz*vy),
                   (qw*vy  +  qz*vx  -  qx*vz),
                   (qw*vz  +  qx*vy  -  qy*vx) );
}

pQuat operator*(float value, const pQuat &q)
{
    return pQuat(q.GetW() * value, q.GetX() * value, q.GetY() * value, q.GetZ() * value);
}

pQuat operator*(const pQuat &q, float value)
{
    return pQuat(q.GetW() * value, q.GetX() * value, q.GetY() * value, q.GetZ() * value);
}

pQuat QRotate(const pQuat &q1, const pQuat &q2)
{
    pQuat temp1, temp2;
    temp1 = q1;
    temp2 = q2;
    return temp1 * temp2 * temp1.Invert();
}

pVec3 QVRotate(const pQuat &q1, const pVec3 &v)
{
    pQuat tempq = q1;
    pVec3 tempv = v;

    pQuat mult = tempq * v * tempq.Invert();
    return pVec3(mult.GetX(), mult.GetY(), mult.GetZ());

}
