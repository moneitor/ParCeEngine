#include "PPoint.h"


pPoint::pPoint()
    :x{0}, y{0}, z{0}, w{0}
{
}

pPoint::pPoint(std::array<float, 3> values)
    :x{values[0]}, y{values[1]}, z{values[2]}, w{values[3]}
{
}

pPoint::pPoint(const float value)
    :x{value}, y{value}, z{value}, w{value}
{
}

pPoint::pPoint(const float x_, const float y_, const float z_, const float w_)
    :x{x_}, y{y_}, z{z_}, w{w_}
{
}

pPoint::pPoint(const pPoint &other)
    :x{other.x}, y{other.y}, z{other.z}, w{other.w}
{
}

pPoint::pPoint(const pPoint &other, float w_)
:x{other.GetX()}, y{other.GetY()}, z{other.GetZ()}, w{w_}
{
}

float pPoint::Magnitude() const
{
    
    return sqrt(this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w);
}

float pPoint::MagnitudeSq() const
{    
    return (this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w);
}

pPoint pPoint::Normalize() const
{
    float mag = this->Magnitude();
    return pPoint(this->x/mag, this->y/mag, this->z/mag, this->w/mag);
}

float pPoint::Dot(const pPoint &other) const
{
    return (this->x * other.x + this->y * other.y + this->z * other.z + this->w * other.w);
}

float pPoint::GetX() const 
{
    return x;
}

float pPoint::GetY() const
{
    return y;
}

float pPoint::GetZ() const
{
    return z;
}

float pPoint::GetW() const
{
    return w;
}
void pPoint::SetX(float value)
{
    this->x = value;
}

void pPoint::SetY(float value)
{
    this->y = value;
}

void pPoint::SetZ(float value)
{
    this->z = value;
}

void pPoint::SetW(float value)
{
    this->w = value;
}

float pPoint::operator[](const unsigned int value)
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

pPoint &pPoint::operator=(const pPoint &other)
{
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
    this->w = other.w;
    return *this;
}

bool pPoint::operator==(const pPoint &other) const
{
    return(compareDouble(this->x, other.x) && 
           compareDouble(this->y, other.y) &&
           compareDouble(this->z, other.z) &&
           compareDouble(this->w, other.w));
}

bool pPoint::operator!=(const pPoint &other) const
{
    return !(*this==other);
}

inline pPoint pPoint::operator+(const pPoint &other)
{
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;
    this->w += other.w;
    return *this;
}

inline pPoint pPoint::operator-(const pPoint &other)
{
    this->x -= other.x;
    this->y -= other.y;
    this->z -= other.z;
    this->w -= other.w;
    return *this;
}

inline pPoint pPoint::operator*(float scalar)
{
    this->x *= scalar;
    this->y *= scalar;
    this->z *= scalar;
    this->w *= scalar;
    return *this;
}

inline pPoint pPoint::operator*(const pPoint &other)
{
    // Performs element wise Hadamard multiplication
    this->x *= other.x;
    this->y *= other.y;
    this->z *= other.z;
    this->w *= other.w;
    return *this;
}

inline pPoint pPoint::operator/(float scalar)
{
    this->x /= scalar;
    this->y /= scalar;
    this->z /= scalar;
    this->w /= scalar;
    return *this;
}

inline pPoint &pPoint::operator+=(const pPoint &other)
{
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;
    this->w += other.w;
    return *this;
}

inline pPoint &pPoint::operator-=(const pPoint &other)
{
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;
    this->w += other.w;
    return *this;
}

inline pPoint &pPoint::operator*=(float scalar)
{
    this->x *= scalar;
    this->y *= scalar;
    this->z *= scalar;
    this->w *= scalar;
    return *this;
}

inline pPoint &pPoint::operator/=(float scalar)
{
    this->x /= scalar;
    this->y /= scalar;
    this->z /= scalar;
    this->w /= scalar;
    return *this;
}

float PointDot(const pPoint &v1, const pPoint &v2)
{
    return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w);
}


