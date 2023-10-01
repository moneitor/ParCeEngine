#include "PMat3.h"

pMat3::pMat3()
    :e11{0}, e12{0}, e13{0}, 
     e21{0}, e22{0}, e23{0}, 
     e31{0}, e32{0}, e33{0},
     elements{0,0,0,0,0,0,0,0,0}
{
}

pMat3::pMat3(const pMat3 &other)
    :e11{other.e11}, e12{other.e12}, e13{other.e13}, 
     e21{other.e21}, e22{other.e22}, e23{other.e23}, 
     e31{other.e31}, e32{other.e32}, e33{other.e33},
     elements{other.e11, other.e12, other.e13, 
              other.e21, other.e22, other.e23, 
              other.e31, other.e32, other.e33}
{
}

pMat3::pMat3(const pVec3 &row0_, const pVec3 &row1_, const pVec3 &row2_)
    :e11{row0_.GetX()}, e12{row0_.GetY()}, e13{row0_.GetZ()}, 
     e21{row1_.GetX()}, e22{row1_.GetY()}, e23{row1_.GetZ()}, 
     e31{row2_.GetX()}, e32{row2_.GetY()}, e33{row2_.GetZ()},
     elements{row0_.GetX(), row0_.GetY(), row0_.GetZ(), 
              row1_.GetX(), row1_.GetY(), row1_.GetZ(),
              row2_.GetX(), row2_.GetY(), row2_.GetZ()}

{
}

pMat3::pMat3(float a11, float a12, float a13, float a21, float a22, float a23, float a31, float a32, float a33)
    :e11{a11}, e12{a12}, e13{a13}, 
     e21{a21}, e22{a22}, e23{a23}, 
     e31{a31}, e32{a32}, e33{a33},
     elements{a11, a12, a13, 
              a21, a22, a23, 
              a31, a32, a33}
{
}

pVec3 pMat3::GetRow0() const
{    
    return pVec3(e11, e12, e13);
}

pVec3 pMat3::GetRow1() const
{
    return pVec3(e21, e22, e23);
}

pVec3 pMat3::GetRow2() const
{
    return pVec3(e31, e32, e33);
}

void pMat3::SetXX(float value)
{
    this->e11 = value;
}

void pMat3::SetXY(float value)
{
    this->e12 = value;
}

void pMat3::SetXZ(float value)
{
    this->e13 = value;
}

void pMat3::SetYX(float value)
{
    this->e21 = value;
}

void pMat3::SetYY(float value)
{
    this->e22 = value;
}

void pMat3::SetYZ(float value)
{
    this->e23 = value;
}

void pMat3::SetZX(float value)
{
    this->e31 = value;
}

void pMat3::SetZY(float value)
{
    this->e32 = value;
}

void pMat3::SetZZ(float value)
{
    this->e33 = value;
}

float pMat3::Determinant() const
{
    return e11*e22*e33 - 
           e11*e32*e23 +
           e21*e32*e13 - 
           e21*e12*e33 +
           e31*e12*e23 -
           e31*e22*e13;
}

pMat3 pMat3::Transpose() const
{
    pMat3 tranposed = pMat3(e11, e21, e31, e12, e22, e32, e13, e23, e33);
    return tranposed;
}

pMat3 pMat3::Invert() const
{
    float determinant = this->Determinant();
    if (determinant == 0) determinant = 1.0;
    return pMat3((e22*e33 - e23*e32) / determinant,
                 -(e12*e33 - e13*e32) / determinant,
                 (e12*e23 - e13*e22) / determinant,
                 -(e21*e33 - e23*e31) / determinant,
                 (e11*e33 - e13*e31) / determinant,
                 -(e11*e23 - e13*e21) / determinant,
                 (e21*e32 - e22*e31) / determinant,
                 -(e11*e32 - e12*e31) / determinant,
                 (e11*e22 -e12*e21) / determinant);      
}

pMat3 &pMat3::operator=(const pMat3 &other)
{
    this->e11 = other.e11;
    this->e12 = other.e12;
    this->e13 = other.e13;

    this->e21 = other.e21;
    this->e22 = other.e22;
    this->e23 = other.e23;

    this->e31 = other.e31;
    this->e32 = other.e32;
    this->e33 = other.e33;

    return *this;
}

float pMat3::operator[](const int value)
{
    if (value == 0) return e11;
    if (value == 1) return e12;
    if (value == 2) return e13;

    if (value == 3) return e21;
    if (value == 4) return e22;
    if (value == 5) return e23;

    if (value == 6) return e31;
    if (value == 7) return e32;
    if (value == 8) return e33;
    else return e11;
}

const pMat3 &pMat3::operator+=(const pMat3 &other)
{
    this->e11 += other.e11;
    this->e12 += other.e12;
    this->e13 += other.e13;

    this->e21 += other.e21;
    this->e22 += other.e22;
    this->e23 += other.e23;

    this->e31 += other.e31;
    this->e32 += other.e32;
    this->e33 += other.e33;
    return *this;
}

inline const pMat3 &pMat3::operator-=(const pMat3 &other)
{
    this->e11 -= other.e11;
    this->e12 -= other.e12;
    this->e13 -= other.e13;

    this->e21 -= other.e21;
    this->e22 -= other.e22;
    this->e23 -= other.e23;

    this->e31 -= other.e31;
    this->e32 -= other.e32;
    this->e33 -= other.e33;
    return *this;
}

const pMat3 &pMat3::operator*=(const float value)
{
    this->e11 *= value;
    this->e12 *= value;
    this->e13 *= value;

    this->e21 *= value;
    this->e22 *= value;
    this->e23 *= value;

    this->e31 *= value;
    this->e32 *= value;
    this->e33 *= value;
    return *this;
}

const pMat3 &pMat3::operator*=(const pMat3 &other)
{
    this->e11 = this->e11*other.e11 + this->e12*other.e21 + this->e13*other.e31;
    this->e12 = this->e11*other.e12 + this->e12*other.e22 + this->e13*other.e32;
    this->e13 = this->e11*other.e13 + this->e12*other.e23 + this->e13*other.e33;

    this->e21 = this->e21*other.e11 + this->e22*other.e21 + this->e23*other.e31;
    this->e22 = this->e21*other.e12 + this->e22*other.e22 + this->e23*other.e32;
    this->e23 = this->e21*other.e13 + this->e22*other.e23 + this->e23*other.e33;

    this->e31 = this->e31*other.e11 + this->e32*other.e21 + this->e33*other.e31;
    this->e32 = this->e31*other.e12 + this->e32*other.e22 + this->e33*other.e32;
    this->e33 = this->e31*other.e13 + this->e32*other.e23 + this->e33*other.e33;
    return *this;
}

inline const pMat3 &pMat3::operator/=(const float value)
{
    this->e11 /= value;
    this->e12 /= value;
    this->e13 /= value;

    this->e21 /= value;
    this->e22 /= value;
    this->e23 /= value;

    this->e31 /= value;
    this->e32 /= value;
    this->e33 /= value;
    return *this;
}

inline const pMat3 pMat3::operator*(const pMat3 &other)
{
    return pMat3(   this->e11*other.e11 + this->e12*other.e21 + this->e13*other.e31,
                    this->e11*other.e12 + this->e12*other.e22 + this->e13*other.e32,
                    this->e11*other.e13 + this->e12*other.e23 + this->e13*other.e33,
                    this->e21*other.e11 + this->e22*other.e21 + this->e23*other.e31,
                    this->e21*other.e12 + this->e22*other.e22 + this->e23*other.e32,
                    this->e21*other.e13 + this->e22*other.e23 + this->e23*other.e33,
                    this->e31*other.e11 + this->e32*other.e21 + this->e33*other.e31,
                    this->e31*other.e12 + this->e32*other.e22 + this->e33*other.e32,
                    this->e31*other.e13 + this->e32*other.e23 + this->e33*other.e33);
}

pVec3 operator*(const pMat3 &mat, const pVec3 &vec)
{
    return pVec3( mat.e11*vec.GetX() + mat.e12*vec.GetY() + mat.e13*vec.GetZ(),
                  mat.e21*vec.GetX() + mat.e22*vec.GetY() + mat.e23*vec.GetZ(),
                  mat.e31*vec.GetX() + mat.e32*vec.GetY() + mat.e33*vec.GetZ());
}

pVec3 operator*(const pVec3 &vec, const pMat3 &mat)
{
    return pVec3( vec.GetX()*mat.e11 + vec.GetY()*mat.e21 + vec.GetZ()*mat.e31,
                  vec.GetX()*mat.e12 + vec.GetY()*mat.e22 + vec.GetZ()*mat.e32,
                  vec.GetX()*mat.e13 + vec.GetY()*mat.e23 + vec.GetZ()*mat.e33);
}
