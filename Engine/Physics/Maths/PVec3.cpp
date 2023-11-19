#include "PVec3.h"

pVec3::pVec3()
    :x{0}, y{0}, z{0}
{
}

pVec3::pVec3(std::array<float, 3> values)
    :x{values[0]}, y{values[1]}, z{values[2]}
{
}

pVec3::pVec3(const float value)
    :x{value}, y{value}, z{value}
{
}

pVec3::pVec3(const float x_, const float y_, const float z_)
    :x{x_}, y{y_}, z{z_}
{
}

pVec3::pVec3(const pVec3 &other)
    :x{other.x}, y{other.y}, z{other.z}
{
}

pVec3::pVec3(const glm::vec3 &other)
    :x{other.x}, y{other.y}, z{other.z}
{
}

float pVec3::Magnitude() const
{
    
    return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}

float pVec3::MagnitudeSq() const
{    
    return (this->x * this->x + this->y * this->y + this->z * this->z);
}

pVec3 pVec3::Normalize() const
{
    float mag = this->Magnitude();
    return pVec3(this->x/mag, this->y/mag, this->z/mag);
}

float pVec3::Angle(const pVec3 &other) const
{
    float m = sqrt(this->Magnitude() * other.Magnitude());
    return acos(this->Dot(other) / m);
}

float pVec3::Dot(const pVec3 &other) const
{
    return (this->x * other.x + this->y * other.y + this->z * other.z);
}

pVec3 pVec3::Cross(const pVec3 &other) const
{
    return pVec3(this->y * other.z - this->z * other.y ,
                 this->x * other.z - this->z * other.x ,
                 this->x * other.y - this->y * other.x);
}

float pVec3::GetX() const
{
    return x;
}

float pVec3::GetY() const
{
    return y;
}

float pVec3::GetZ() const
{
    return z;
}

void pVec3::SetZ(float value)
{
    this->z = value;
}

std::string pVec3::ToString() const
{
    std::string vec = "X: " + std::to_string(this->x);
    vec += ", Y: " + std::to_string(this->y);
    vec += ", Z: " + std::to_string(this->z);

    return vec;
}

void pVec3::SetY(float value)
{
    this->y = value;
}

void pVec3::SetX(float value)
{
    this->x = value;
}

float pVec3::operator[](const int value)
{
    assert(value <= 2);

    switch (value)
    {
        case 0:
        {
            return x;
            break;
        }
        case 1:
        {
            return y;
            break;
        }     
        case 2:
        {
            return z;
            break;
        }  
        default:
            return x;  
    }
}

pVec3 &pVec3::operator=(const pVec3 &other)
{
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
    return *this;
}

bool pVec3::operator==(const pVec3 &other) const
{
    return(compareDouble(this->x, other.x) && compareDouble(this->y, other.y)  && compareDouble(this->z, other.z));
}

bool pVec3::operator!=(const pVec3 &other) const
{
    return !(*this==other);
}

pVec3 pVec3::operator+(const pVec3 &other)
{
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;
    return *this;
}

pVec3 pVec3::operator-(const pVec3 &other)
{
    this->x -= other.x;
    this->y -= other.y;
    this->z -= other.z;
    return *this;
}

pVec3 pVec3::operator*(float scalar)
{

    // x *= scalar;
    // y *= scalar;
    // z *= scalar;
    // return *this;

    pVec3 temp = *this;
    temp.x *= scalar;
    temp.y *= scalar;
    temp.z *= scalar;
    return temp;
}

pVec3 pVec3::operator*(const pVec3 &other)
{
    // Performs element wise Hadamard multiplication
    pVec3 temp = *this;
    temp.x *= other.x;
    temp.y *= other.y;
    temp.z *= other.z;
    return temp;
}

pVec3 pVec3::operator/(float scalar)
{
    this->x /= scalar;
    this->y /= scalar;
    this->z /= scalar;
    return *this;
}

pVec3 &pVec3::operator+=(const pVec3 &other)
{
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;
    return *this;
}

pVec3 &pVec3::operator-=(const pVec3 &other)
{
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;
    return *this;
}

pVec3 &pVec3::operator*=(float scalar)
{
    this->x *= scalar;
    this->y *= scalar;
    this->z *= scalar;
    return *this;
}

pVec3 &pVec3::operator/=(float scalar)
{
    this->x /= scalar;
    this->y /= scalar;
    this->z /= scalar;
    return *this;
}

float Dot(const pVec3 &v1, const pVec3 &v2)
{
    return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

pVec3 Cross(const pVec3 &v1, const pVec3 &v2)
{
    return pVec3(v1.y * v2.z - v1.z * v2.y ,
                 v1.x * v2.z - v1.z * v2.x ,
                 v1.x * v2.y - v1.y * v2.x);
}

float Angle(const pVec3 &v1, const pVec3 &v2)
{
    float numerator = v1.Dot(v2);
    float denominator = v1.Magnitude() * v2.Magnitude();
    return (numerator/denominator) * 57.295754; // the last float is to convert from radians to degrees
    // multiply by 0.0174533
}

pVec3 Projection(const pVec3 &v1, const pVec3 &v2)
{
    // Returns the component of v1 that is parallel to v2
    pVec3 tempVec = v2;
    float dot = Dot(v1, v2);
    float magsq = v2.MagnitudeSq();
    float result = dot/magsq;

    return tempVec * result;
}

pVec3 Perpendicular(const pVec3 &v1, const pVec3 &v2)
{
    pVec3 tempVec = v1;
    return tempVec - Projection(v1, v2);
}

pVec3 Reflection(const pVec3 &v1, const pVec3 &normal)
{
    pVec3 tempNormal = normal;
    pVec3 tempV1 = v1;
    float d = Dot(v1, normal);
    return tempV1 - tempNormal * (2 * d);
}
