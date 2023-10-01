#include "PMat2.h"

pMat2::pMat2()
    :e11{1}, e12{0}, 
     e21{0}, e22{1}
{
}

pMat2::pMat2(const pMat2 &other)
    :e11{other.e11}, e12{other.e12},
     e21{other.e21}, e22{other.e22}
{
}

pMat2::pMat2(const pVec2 &row0_, const pVec2 &row1_)
    :e11{row0_.GetX()}, e12{row0_.GetY()},
     e21{row1_.GetX()}, e22{row1_.GetY()}
{
}

pMat2::pMat2(float a11_, float a12_, float a21_, float a22_)
    :e11{a11_}, e12{a12_},
     e21{a21_}, e22{a22_}
{
}

pVec2 pMat2::GetRow0() const
{
    return pVec2(e11, e12);
}

pVec2 pMat2::GetRow1() const
{
    return pVec2(e21, e22);
}


float pMat2::Determinant() const
{
    return e11 * e22 - e12 * e21;
}

pMat2 pMat2::Transpose() const
{
    pMat2 transposed;
    TransposeGeneric(this->data, transposed.data, 2, 2);
    return transposed;
}

inline pMat2 pMat2::Invert() const
{
    return pMat2();
}

pMat2 &pMat2::operator=(const pMat2 &other)
{
    this->e11 = other.e11;
    this->e12 = other.e12;

    this->e21 = other.e21;
    this->e22 = other.e22;

    return *this;
}

inline const pMat2 pMat2::operator*(const float value)
{
    pMat2 result;
    for (int i=0; i < 4; i++)
    {
        result.data[i] = this->data[i] * value; 
    }
    return result;
}

inline const pMat2 pMat2::operator*(const pVec2 &vec)
{
    return pMat2();
}

inline const pMat2 pMat2::operator*(const pMat2 &other)
{
    pMat2 result;
    MatrixMultiplyGeneric(result.data, this->data, 2, 2, other.data, 2, 2);
    return result;
}

float *pMat2::operator[](int value)
{
    return &(data[value * 2]);
}

pMat2 Transpose(const pMat2 &mat)
{
    pMat2 transposed;
    TransposeGeneric(mat.data, transposed.data, 2, 2);
    return transposed;
}

float Determinant(const pMat2 &mat)
{
    return mat.e11 * mat.e22 - mat.e12 * mat.e21;
}

pMat2 Minor(const pMat2 &mat)
{
    return pMat2(mat.e22, mat.e21, 
                 mat.e12, mat.e11);
}

pMat2 Cofactor(const pMat2 &mat)
{
    pMat2 out;
    CofactorGeneric(out.data, Minor(mat).data, 2, 2);
    return out;
}

pMat2 Adjugate(const pMat2 &mat)
{
    return Transpose(Cofactor(mat));
}

pMat2 Inverse(const pMat2 &mat)
{
    // float determinant = Determinant(mat);
    // if(compareDouble(determinant, 0.0f)) return pMat2();
    // return Adjugate(mat) * (1.0f / determinant);

    float determinant = mat.e11 * mat.e22 - mat.e12 * mat.e21;

    if (compareDouble(determinant, 0.0f)) return pMat2();

    pMat2 result;
    float i_det = 1.0f / determinant;

    result.e11 =  mat.e22 * i_det;
    result.e12 = -mat.e12 * i_det;
    result.e21 = -mat.e21 * i_det;
    result.e22 =  mat.e11 * i_det;

    return result;
}
