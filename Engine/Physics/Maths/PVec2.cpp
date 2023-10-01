// #include "PVec2.h"

// pVec2::pVec2()
//     :x{0}, y{0}
// {
// }

// pVec2::pVec2(std::array<float, 2> values)
//     :x{values[0]}, y{values[1]}
// {
// }

// pVec2::pVec2(const float value)
//     :x{value}, y{value}
// {
// }

// pVec2::pVec2(const float x_, const float y_)
//     :x{x_}, y{y_}
// {
// }

// pVec2::pVec2(const pVec2 &other)
//     :x{other.x}, y{other.y}
// {
// }

// float pVec2::GetX() const
// {
//     return x;
// }

// float pVec2::GetY() const
// {
//     return y;
// }

// float pVec2::Magnitude() const
// {    
//     return sqrt(this->x * this->x + this->y * this->y);
// }

// float pVec2::MagnitudeSq() const
// {    
//     return (this->x * this->x + this->y * this->y);
// }

// pVec2 pVec2::Normalize() const
// {
//     float mag = this->Magnitude();
//     return pVec2(this->x/mag, this->y/mag);
// }

// float pVec2::Dot(const pVec2 &other) const
// {
//     return (this->x * other.x + this->y * other.y);
// }

// float pVec2::Angle(const pVec2 &other) const
// {
//     float m = sqrt(this->Magnitude() * other.Magnitude());
//     return acos(this->Dot(other) / m);
// }

// float pVec2::operator[](const unsigned int value)
// {
//     assert(value <= 1);

//     switch (value)
//     {
//         case 0:
//         {
//             return x;
//             break;
//         }
//         case 1:
//         {
//             return y;
//             break;
//         }      
//         default:
//             return x;  
//     }
// }

// pVec2 &pVec2::operator=(const pVec2 &other)
// {
//     this->x = other.x;
//     this->y = other.y;
//     return *this;
// }

// bool pVec2::operator==(const pVec2 &other) const
// {
//     return(compareDouble(this->x, other.x) && compareDouble(this->y, other.y));
// }

// bool pVec2::operator!=(const pVec2 &other) const
// {
//     return !(*this==other);
// }

// pVec2 pVec2::operator+(const pVec2 &other)
// {
//     this->x += other.x;
//     this->y += other.y;
//     return *this;
// }

// pVec2 pVec2::operator-(const pVec2 &other)
// {
//     this->x -= other.x;
//     this->y -= other.y;
//     return *this;
// }

// pVec2 pVec2::operator*(float scalar)
// {
//     this->x *= scalar;
//     this->y *= scalar;
//     return *this;
// }

// pVec2 pVec2::operator*(const pVec2 &other)
// {
//     // Performs element wise Hadamard multiplication
//     this->x *= other.x;
//     this->y *= other.y;
//     return *this;
// }

// pVec2 pVec2::operator/(float scalar)
// {
//     this->x /= scalar;
//     this->y /= scalar;
//     return *this;
// }

// pVec2 pVec2::operator+=(const pVec2 &other)
// {
//     this->x += other.x;
//     this->y += other.y;
//     return *this;
// }

// pVec2 pVec2::operator-=(const pVec2 &other)
// {
//     this->x += other.x;
//     this->y += other.y;
//     return *this;
// }

// pVec2 pVec2::operator*=(float scalar)
// {
//     this->x *= scalar;
//     this->y *= scalar;
//     return *this;
// }

// pVec2 pVec2::operator/=(float scalar)
// {
//     this->x /= scalar;
//     this->y /= scalar;
//     return *this;
// }
