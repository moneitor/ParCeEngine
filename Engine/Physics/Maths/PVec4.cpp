#include "PVec4.h"


pVec4::pVec4()
    :x{0}, y{0}, z{0}, w{0}
{
}

pVec4::pVec4(std::array<float, 3> values)
    :x{values[0]}, y{values[1]}, z{values[2]}, w{values[3]}
{
}

pVec4::pVec4(const float value)
    :x{value}, y{value}, z{value}, w{value}
{
}

pVec4::pVec4(const float x_, const float y_, const float z_, const float w_)
    :x{x_}, y{y_}, z{z_}, w{w_}
{
}

pVec4::pVec4(const pVec4 &other)
    :x{other.x}, y{other.y}, z{other.z}, w{other.w}
{
}

float pVec4::Magnitude() const
{
    
    return sqrt(this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w);
}

float pVec4::MagnitudeSq() const
{    
    return (this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w);
}

pVec4 pVec4::Normalize() const
{
    float mag = this->Magnitude();
    return pVec4(this->x/mag, this->y/mag, this->z/mag, this->w/mag);
}

float pVec4::Dot(const pVec4 &other) const
{
    return (this->x * other.x + this->y * other.y + this->z * other.z + this->w * other.w);
}

float pVec4::GetX()
{
    return x;
}

float pVec4::GetY()
{
    return y;
}

float pVec4::GetZ()
{
    return z;
}

float pVec4::GetW()
{
    return w;
}
float pVec4::operator[](const unsigned int value)
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
        case 3:
        {
            return w;
            break;
        } 
        default:
            return x;  
    }
}

pVec4 &pVec4::operator=(const pVec4 &other)
{
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
    this->w = other.w;
    return *this;
}

bool pVec4::operator==(const pVec4 &other) const
{
    return(compareDouble(this->x, other.x) && 
           compareDouble(this->y, other.y) &&
           compareDouble(this->z, other.z) &&
           compareDouble(this->w, other.w));
}

bool pVec4::operator!=(const pVec4 &other) const
{
    return !(*this==other);
}

inline pVec4 pVec4::operator+(const pVec4 &other)
{
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;
    this->w += other.w;
    return *this;
}

inline pVec4 pVec4::operator-(const pVec4 &other)
{
    this->x -= other.x;
    this->y -= other.y;
    this->z -= other.z;
    this->w -= other.w;
    return *this;
}

inline pVec4 pVec4::operator*(float scalar)
{
    this->x *= scalar;
    this->y *= scalar;
    this->z *= scalar;
    this->w *= scalar;
    return *this;
}

inline pVec4 pVec4::operator*(const pVec4 &other)
{
    // Performs element wise Hadamard multiplication
    this->x *= other.x;
    this->y *= other.y;
    this->z *= other.z;
    this->w *= other.w;
    return *this;
}

inline pVec4 pVec4::operator/(float scalar)
{
    this->x /= scalar;
    this->y /= scalar;
    this->z /= scalar;
    this->w /= scalar;
    return *this;
}

inline pVec4 &pVec4::operator+=(const pVec4 &other)
{
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;
    this->w += other.w;
    return *this;
}

inline pVec4 &pVec4::operator-=(const pVec4 &other)
{
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;
    this->w += other.w;
    return *this;
}

inline pVec4 &pVec4::operator*=(float scalar)
{
    this->x *= scalar;
    this->y *= scalar;
    this->z *= scalar;
    this->w *= scalar;
    return *this;
}

inline pVec4 &pVec4::operator/=(float scalar)
{
    this->x /= scalar;
    this->y /= scalar;
    this->z /= scalar;
    this->w /= scalar;
    return *this;
}

float Dot(const pVec4 &v1, const pVec4 &v2)
{
    return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w);
}


