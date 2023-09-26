#include "PMat3.h"

pMat3::pMat3()
    :e11{0}, e12{0}, e13{0}, e21{0}, e22{0}, e23{0}, e31{0}, e32{0}, e33{0},
    row0{pVec3(0.0, 0.0, 0.0)}, row1{pVec3(0.0, 0.0, 0.0)}, row2{pVec3(0.0, 0.0, 0.0)}
{
}

pMat3::pMat3(const pMat3 &other)
    :e11{other.e11},
     e12{other.e12},
     e13{other.e13}, 
     e21{other.e21}, 
     e22{other.e22}, 
     e23{other.e23}, 
     e31{other.e31}, 
     e32{other.e32}, 
     e33{other.e33},
     row0{pVec3(other.e11, other.e12, other.e13)}, 
     row1{pVec3(other.e21, other.e22, other.e23)}, 
     row2{pVec3(other.e31, other.e32, other.e33)}
{
}

pMat3::pMat3(const pVec3 &row0_, const pVec3 &row1_, const pVec3 &row2_)
    :e11{row0_.GetX()},
     e12{row0_.GetY()},
     e13{row0_.GetZ()}, 
     e21{row1_.GetX()}, 
     e22{row1_.GetY()}, 
     e23{row1_.GetZ()}, 
     e31{row2_.GetX()}, 
     e32{row2_.GetY()}, 
     e33{row2_.GetZ()},
     row0{row0_}, row1{row1_}, row2{row2_}
{
}

pMat3::pMat3(float a11, float a12, float a13, float a21, float a22, float a23, float a31, float a32, float a33)
    :e11{a11}, e12{a12}, e13{a13}, e21{a21}, e22{a22}, e23{a23}, e31{a31}, e32{a32}, e33{a33},
    row0{pVec3(a11, a12, a13)}, row1{pVec3(a21, a22, a23)}, row2{pVec3(a31, a32, a33)}
{
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
    this->row0 = other.row0;
    this->row1 = other.row1;
    this->row2 = other.row2;
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
    this->row0 += other.row0;
    this->row1 += other.row1;
    this->row2 += other.row2;
    return *this;
}

const pMat3 &pMat3::operator*=(const float value)
{
    this->row0 *= value;
    this->row1 *= value;
    this->row2 *= value;
    return *this;
}

const pMat3 &pMat3::operator*=(const pMat3 &other)
{
    return *this;
}
