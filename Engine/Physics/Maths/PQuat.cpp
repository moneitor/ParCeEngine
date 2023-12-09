#include "PQuat.h"

pQuat::pQuat()
: w{1}, x{0}, y{0}, z{0}
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

pQuat::pQuat(const float angle, const pVec3 &vec)
{
    const float halfAngle = 0.5 * angle;
    this->w = std::cosf(halfAngle);

    const float halfSine = std::sinf(halfAngle);

    pVec3 vecNorm = vec.Normalize();
    this->x = vecNorm[0] * halfSine;
    this->y = vecNorm[1] * halfSine;
    this->z = vecNorm[2] * halfSine;

    if (compareDouble(vec.Magnitude(), 0.0f)) 
    { 
        // constructs a default quat in case the given vec is a zero vector or an undefined vec
        this->w = 1.0f;
        this->x = 0.0f;
        this->y = 0.0f;
        this->z = 0.0f;
    }
}

pQuat::pQuat(float value)
:w{value}, x{0.0f}, y{0.0f}, z{0.0f}
{
}

pQuat::pQuat(const pVec3 &vec)
:w{0.0f}, x{vec.GetX()}, y{vec.GetY()}, z{vec.GetZ()}
{
}

pQuat::pQuat(glm::quat quat)
:w{quat.w}, x{quat.x}, y{quat.y}, z{quat.z}
{
}

pQuat::pQuat(float x, float y, float z)
{
    pQuat temp;
    float roll = DEG2RAD(x);
    float pitch = DEG2RAD(y);
    float yaw = DEG2RAD(z);

    float cyaw, cpitch, croll, syaw, spitch, sroll;
    float cyawcpitch, syawspitch, cyawspitch, syawcpitch;

    cyaw = std::cos(0.5f * yaw);
    cpitch = std::cos(0.5f * pitch);
    croll = std::cos(0.5f * roll);
    syaw = std::sin(0.5f * yaw);
    spitch = std::sin(0.5f * pitch);
    sroll = std::sin(0.5f * roll);

    cyawcpitch = cyaw * cpitch;
    syawspitch = syaw * spitch;
    cyawspitch = cyaw * spitch;
    syawcpitch = syaw * cpitch;

    w = cyawcpitch * croll + syawspitch * sroll;
    x = cyawcpitch * sroll - syawspitch * croll;
    y = cyawspitch * croll + syawcpitch * sroll;
    z = syawcpitch * croll - cyawspitch * sroll;
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
    pQuat p(*this);
    pQuat q(other);

    float newW = w * q.w - x * q.x - y * q.y - z * q.z;
    float newX = w * q.x + x * q.w + y * q.z - z * q.y;
    float newY = w * q.y + y * q.w + z * q.x - x * q.z;
    float newZ = w * q.z + z * q.w + x * q.y - y * q.x;
    return pQuat(newW, newX, newY, newZ);
}

pVec3 pQuat::operator*(const pVec3 &v1)
{
    pQuat thisQ = *this;
    
    pVec3 QuatVector = pVec3(thisQ.x, thisQ.y, thisQ.z);
    pVec3 uv = Cross(QuatVector, v1);
	pVec3 uuv = Cross(QuatVector, uv);

    return v1 + ((uv * thisQ.w) + uuv) * (2.0f);
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

    float inverseMag = 1.0f / Magnitude();

    if (inverseMag == 0.0f)
    {
        tempW = 1.0f;
        return pQuat(tempX, tempY, tempZ, tempW);
    }

    tempW = w * inverseMag;
    tempX = x * inverseMag;
    tempY = y * inverseMag;
    tempZ = z * inverseMag;    

    return pQuat(tempW, tempX, tempY, tempZ);

    
}

pMat3 pQuat::ToMatrix() const
{
    pQuat q = *this;
                    
    pMat3 Result;
    float qxx = q.x * q.x;
    float qyy = q.y * q.y;
    float qzz = q.z * q.z;
    float qxz = q.x * q.z;
    float qxy = q.x * q.y;
    float qyz = q.y * q.z;
    float qwx = q.w * q.x;
    float qwy = q.w * q.y;
    float qwz = q.w * q.z;

    Result.e11 = 1.0f - 2.0f * (qyy +  qzz);
    Result.e12 = 2.0f * (qxy + qwz);
    Result.e13 = 2.0f * (qxz - qwy);

    Result.e21 = 2.0f * (qxy - qwz);
    Result.e22 = 1.0f - 2.0f * (qxx +  qzz);
    Result.e23 = 2.0f * (qyz + qwx);

    Result.e31 = 2.0f * (qxz + qwy);
    Result.e32 = 2.0f * (qyz - qwx);
    Result.e33 = 1.0f - 2.0f * (qxx +  qyy);

    return Result;
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

pVec3 pQuat::GetVector() const
{
    return pVec3(x, y, z);
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


pQuat operator*(const pQuat &q1, const pQuat &q2)
{
    pQuat p(q1);
    pQuat q(q2);

    float newW = p.w * q.w - p.x * q.x - p.y * q.y - p.z * q.z;
    float newX = p.w * q.x + p.x * q.w + p.y * q.z - p.z * q.y;
    float newY = p.w * q.y + p.y * q.w + p.z * q.x - p.x * q.z;
    float newZ = p.w * q.z + p.z * q.w + p.x * q.y - p.y * q.x;
    return pQuat(newW, newX, newY, newZ);
}

pVec3 operator*(const pVec3 &v1, const pQuat &q)
{
    return pVec3(q.Invert() * v1);
}

pVec3 operator*(const pQuat &q, const pVec3 &v1)
{    
    pVec3 QuatVector = pVec3(q.x, q.y, q.z);
    pVec3 uv = Cross(QuatVector, v1);
	pVec3 uuv = Cross(QuatVector, uv);

    return v1 + ((uv * q.w) + uuv) * (2.0f);
}

pQuat operator*(float value, const pQuat &q)
{
    return pQuat(q.GetW() * value, q.GetX() * value, q.GetY() * value, q.GetZ() * value);
}

pQuat operator*(const pQuat &q, float value)
{
    return pQuat(q.GetW() * value, q.GetX() * value, q.GetY() * value, q.GetZ() * value);
}

pVec3 RotateVector(const pQuat &q, const pVec3 &vec)
{

    pQuat tempq = q;   
    // pQuat mult = tempq * vec * tempq.Invert();
    // return mult.GetVector();
    return q * vec;
}

pQuat RotateByVector(const pQuat &q, const pVec3 &vec)
{
    pQuat vtoquat = pQuat(vec);
    pQuat tempQ = q;

    return tempQ * vtoquat;
    
}

pQuat RotateByVector(const pQuat &q, const pVec3 &vec, float dt)
{
    pQuat vecToQuat = pQuat(0.0f, vec.GetX() * dt, vec.GetY() * dt, vec.GetZ() * dt);
    pQuat thisQuat = q;
    vecToQuat *= thisQuat;
    thisQuat.w += vecToQuat.w * 0.5;
    thisQuat.x += vecToQuat.x * 0.5;
    thisQuat.y += vecToQuat.y * 0.5;
    thisQuat.z += vecToQuat.z * 0.5;
    return thisQuat;
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
    // pQuat vquat = pQuat(0.0f, v.GetX(), v.GetY(), v.GetZ());

    // pQuat mult = q1 * vquat * pQuat(q1.w, -q1.x, -q1.y, -q1.z);
    // return mult.GetVector();
    pVec3 tempV = v;
    pVec3 QuatVector = pVec3(q1.x, q1.y, q1.z);
    pVec3 uv = pVec3(QuatVector.Cross(v));
    pVec3 uuv = pVec3(QuatVector.Cross(uv));

    return tempV + ((uv * q1.w) + uuv) * 2.0f;
}

pQuat EulerToQuat(float x, float y, float z)
{
    pQuat temp;

    float cx = std::cos(x * 0.5);
    float cy = std::cos(y * 0.5);
    float cz = std::cos(z * 0.5);

    float sx = std::sin(x * 0.5);
    float sy = std::sin(y * 0.5);
    float sz = std::sin(z * 0.5);

    temp.w = cx * cy * cz + sx * sy * sz;
    temp.x = sx * cy * cz - cx * sy * sz;
    temp.y = cx * sy * cz + sx * cy * sz;
    temp.z = cx * cy * sz - sx * sy * cz;

    return temp;
}
