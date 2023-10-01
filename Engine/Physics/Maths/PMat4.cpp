#include "PMat4.h"

pMat4::pMat4()
    :e11{1}, e12{0}, e13{0}, e14{0},
     e21{0}, e22{1}, e23{0}, e24{0},
     e31{0}, e32{0}, e33{1}, e34{0},
     e41{0}, e42{0}, e43{0}, e44{1}
{
}

pMat4::pMat4(const pMat4 &other)
    :e11{other.e11}, e12{other.e12}, e13{other.e13}, e14{other.e14},
     e21{other.e21}, e22{other.e22}, e23{other.e23}, e24{other.e24},
     e31{other.e31}, e32{other.e32}, e33{other.e33}, e34{other.e34},
     e41{other.e31}, e42{other.e32}, e43{other.e33}, e44{other.e44}
{
}

pMat4::pMat4(const pVec4 &row0_, const pVec4 &row1_, const pVec4 &row2_, const pVec4 &row3_)
    :e11{row0_.GetX()}, e12{row0_.GetY()}, e13{row0_.GetZ()}, e14{row0_.GetW()},
     e21{row1_.GetX()}, e22{row1_.GetY()}, e23{row1_.GetZ()}, e24{row0_.GetW()},
     e31{row2_.GetX()}, e32{row2_.GetY()}, e33{row2_.GetZ()}, e34{row0_.GetW()},
     e41{row2_.GetX()}, e42{row2_.GetY()}, e43{row2_.GetZ()}, e44{row0_.GetW()}
{
}

pMat4::pMat4(float a11_, float a12_, float a13_, float a14_, 
             float a21_, float a22_, float a23_, float a24_, 
             float a31_, float a32_, float a33_, float a34_, 
             float a41_, float a42_, float a43_, float a44_)
    :e11{a11_}, e12{a12_}, e13{a13_}, e14{a14_}, 
     e21{a21_}, e22{a22_}, e23{a23_}, e24{a24_}, 
     e31{a31_}, e32{a32_}, e33{a33_}, e34{a34_}, 
     e41{a41_}, e42{a42_}, e43{a43_}, e44{a44_}
{
}

pVec4 pMat4::GetRow0() const
{
    return pVec4(e11, e12, e13, e14);
}

pVec4 pMat4::GetRow1() const
{
    return pVec4(e21, e22, e23, e24);
}

pVec4 pMat4::GetRow2() const
{
    return pVec4(e31, e32, e33, e34);
}

pVec4 pMat4::GetRow3() const
{
    return pVec4(e41, e42, e43, e44);
}

pMat3 pMat4::Minor(const int i, const int j) const
{
    return pMat3();
}

float pMat4::Determinant() const
{
    return 0.0f;
}

pMat4 pMat4::Transpose() const
{
    pMat4 transposed;
    TransposeGeneric(this->data, transposed.data, 4, 4);
    return transposed;
}

inline pMat4 pMat4::Invert() const
{
    return pMat4();
}

pMat4 &pMat4::operator=(const pMat4 &other)
{
    this->e11 = other.e11;
    this->e12 = other.e12;
    this->e13 = other.e13;
    this->e14 = other.e14;

    this->e21 = other.e21;
    this->e22 = other.e22;
    this->e23 = other.e23;
    this->e24 = other.e24;

    this->e31 = other.e31;
    this->e32 = other.e32;
    this->e33 = other.e33;
    this->e34 = other.e34;

    this->e41 = other.e41;
    this->e42 = other.e42;
    this->e43 = other.e43;
    this->e44 = other.e44;

    return *this;
}

inline const pMat4 pMat4::operator*(const float value)
{
    pMat4 result;
    for (int i=0; i < 16; i++)
    {
        result.data[i] = this->data[i] * value; 
    }
    return result;
}

inline const pMat4 pMat4::operator*(const pVec4 &vec)
{
    return pMat4();
}

inline const pMat4 pMat4::operator*(const pMat4 &other)
{
    pMat4 result;
    MatrixMultiplyGeneric(result.data, this->data, 4, 4, other.data, 4, 4);
    return result;
}

float *pMat4::operator[](int value)
{
    return &(data[value * 4]);
}

pMat4 Transpose(const pMat4 &mat)
{
    pMat4 transposed;
    TransposeGeneric(mat.data, transposed.data, 4, 4);
    return transposed;
}

pMat3 Cut(const pMat4 &mat, int row, int col)
{
	pMat3 result;
	int index = 0;

	for (int i = 0; i < 4; ++i) 
    {
		for (int j = 0; j < 4; ++j) 
        {
			if (i == row || j == col) 
            {
				continue;
			}
			result.data[index++] = mat.data[4 * i + j];
		}
	}

	return result;
}

pMat4 Minor(const pMat4 &mat)
{
    pMat4 result;

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            result[i][j] = Determinant(Cut(mat, i, j));
        }
    }
    return result;
}

pMat4 Cofactor(const pMat4 &mat)
{
    pMat4 out;
    CofactorGeneric(out.data, Minor(mat).data, 4, 4);
    return out;
}

float Determinant(const pMat4 &mat)
{
    float out = 0.0f;
    pMat4 cofactor = Cofactor(mat);
    for (int j = 0; j < 4; ++j)
    {
        int index = 4 * (0 + j);
        out += mat.data[index] * cofactor[0][j];
    }
    return out;

    // return mat.e11 * mat.e22 * mat.e33 * mat.e44 + mat.e11 * mat.e23 * mat.e34 * mat.e42 + mat.e11 * mat.e24 * mat.e32 * mat.e43
	// 	+ mat.e12 * mat.e21 * mat.e34 * mat.e43 + mat.e12 * mat.e23 * mat.e31 * mat.e44 + mat.e12 * mat.e24 * mat.e33 * mat.e41
	// 	+ mat.e13 * mat.e21 * mat.e32 * mat.e44 + mat.e13 * mat.e22 * mat.e34 * mat.e41 + mat.e13 * mat.e24 * mat.e31 * mat.e42
	// 	+ mat.e14 * mat.e21 * mat.e33 * mat.e42 + mat.e14 * mat.e22 * mat.e31 * mat.e43 + mat.e14 * mat.e23 * mat.e32 * mat.e41
	// 	- mat.e11 * mat.e22 * mat.e34 * mat.e43 - mat.e11 * mat.e23 * mat.e32 * mat.e44 - mat.e11 * mat.e24 * mat.e33 * mat.e42
	// 	- mat.e12 * mat.e21 * mat.e33 * mat.e44 - mat.e12 * mat.e23 * mat.e34 * mat.e41 - mat.e12 * mat.e24 * mat.e31 * mat.e43
	// 	- mat.e13 * mat.e21 * mat.e34 * mat.e42 - mat.e13 * mat.e22 * mat.e31 * mat.e44 - mat.e13 * mat.e24 * mat.e32 * mat.e41
	// 	- mat.e14 * mat.e21 * mat.e32 * mat.e43 - mat.e14 * mat.e22 * mat.e33 * mat.e41 - mat.e14 * mat.e23 * mat.e31 * mat.e42;
}

pMat4 Adjugate(const pMat4 &mat)
{
    return Transpose(Cofactor(mat));
}

pMat4 Inverse(const pMat4 &mat)
{
    // float determinant = Determinant(mat);
    // if(compareDouble(determinant, 0.0f)) return pMat4();
    // return Adjugate(mat) * (1.0f / determinant);

	float determinant
		= mat.e11 * mat.e22 * mat.e33 * mat.e44 + mat.e11 * mat.e23 * mat.e34 * mat.e42 + mat.e11 * mat.e24 * mat.e32 * mat.e43
		+ mat.e12 * mat.e21 * mat.e34 * mat.e43 + mat.e12 * mat.e23 * mat.e31 * mat.e44 + mat.e12 * mat.e24 * mat.e33 * mat.e41
		+ mat.e13 * mat.e21 * mat.e32 * mat.e44 + mat.e13 * mat.e22 * mat.e34 * mat.e41 + mat.e13 * mat.e24 * mat.e31 * mat.e42
		+ mat.e14 * mat.e21 * mat.e33 * mat.e42 + mat.e14 * mat.e22 * mat.e31 * mat.e43 + mat.e14 * mat.e23 * mat.e32 * mat.e41
		- mat.e11 * mat.e22 * mat.e34 * mat.e43 - mat.e11 * mat.e23 * mat.e32 * mat.e44 - mat.e11 * mat.e24 * mat.e33 * mat.e42
		- mat.e12 * mat.e21 * mat.e33 * mat.e44 - mat.e12 * mat.e23 * mat.e34 * mat.e41 - mat.e12 * mat.e24 * mat.e31 * mat.e43
		- mat.e13 * mat.e21 * mat.e34 * mat.e42 - mat.e13 * mat.e22 * mat.e31 * mat.e44 - mat.e13 * mat.e24 * mat.e32 * mat.e41
		- mat.e14 * mat.e21 * mat.e32 * mat.e43 - mat.e14 * mat.e22 * mat.e33 * mat.e41 - mat.e14 * mat.e23 * mat.e31 * mat.e42;

	if (compareDouble(determinant, 0.0f))
    { 
		return pMat4(); 
	}

	float i_det = 1.0f / determinant;

	pMat4 result;
	result.e11 = (mat.e22 * mat.e33 * mat.e44 + mat.e23 * mat.e34 * mat.e42 + mat.e24 * mat.e32 * mat.e43 - mat.e22 * mat.e34 * mat.e43 - mat.e23 * mat.e32 * mat.e44 - mat.e24 * mat.e33 * mat.e42) * i_det;
	result.e12 = (mat.e12 * mat.e34 * mat.e43 + mat.e13 * mat.e32 * mat.e44 + mat.e14 * mat.e33 * mat.e42 - mat.e12 * mat.e33 * mat.e44 - mat.e13 * mat.e34 * mat.e42 - mat.e14 * mat.e32 * mat.e43) * i_det;
	result.e13 = (mat.e12 * mat.e23 * mat.e44 + mat.e13 * mat.e24 * mat.e42 + mat.e14 * mat.e22 * mat.e43 - mat.e12 * mat.e24 * mat.e43 - mat.e13 * mat.e22 * mat.e44 - mat.e14 * mat.e23 * mat.e42) * i_det;
	result.e14 = (mat.e12 * mat.e24 * mat.e33 + mat.e13 * mat.e22 * mat.e34 + mat.e14 * mat.e23 * mat.e32 - mat.e12 * mat.e23 * mat.e34 - mat.e13 * mat.e24 * mat.e32 - mat.e14 * mat.e22 * mat.e33) * i_det;
	result.e21 = (mat.e21 * mat.e34 * mat.e43 + mat.e23 * mat.e31 * mat.e44 + mat.e24 * mat.e33 * mat.e41 - mat.e21 * mat.e33 * mat.e44 - mat.e23 * mat.e34 * mat.e41 - mat.e24 * mat.e31 * mat.e43) * i_det;
	result.e22 = (mat.e11 * mat.e33 * mat.e44 + mat.e13 * mat.e34 * mat.e41 + mat.e14 * mat.e31 * mat.e43 - mat.e11 * mat.e34 * mat.e43 - mat.e13 * mat.e31 * mat.e44 - mat.e14 * mat.e33 * mat.e41) * i_det;
	result.e23 = (mat.e11 * mat.e24 * mat.e43 + mat.e13 * mat.e21 * mat.e44 + mat.e14 * mat.e23 * mat.e41 - mat.e11 * mat.e23 * mat.e44 - mat.e13 * mat.e24 * mat.e41 - mat.e14 * mat.e21 * mat.e43) * i_det;
	result.e24 = (mat.e11 * mat.e23 * mat.e34 + mat.e13 * mat.e24 * mat.e31 + mat.e14 * mat.e21 * mat.e33 - mat.e11 * mat.e24 * mat.e33 - mat.e13 * mat.e21 * mat.e34 - mat.e14 * mat.e23 * mat.e31) * i_det;
	result.e31 = (mat.e21 * mat.e32 * mat.e44 + mat.e22 * mat.e34 * mat.e41 + mat.e24 * mat.e31 * mat.e42 - mat.e21 * mat.e34 * mat.e42 - mat.e22 * mat.e31 * mat.e44 - mat.e24 * mat.e32 * mat.e41) * i_det;
	result.e32 = (mat.e11 * mat.e34 * mat.e42 + mat.e12 * mat.e31 * mat.e44 + mat.e14 * mat.e32 * mat.e41 - mat.e11 * mat.e32 * mat.e44 - mat.e12 * mat.e34 * mat.e41 - mat.e14 * mat.e31 * mat.e42) * i_det;
	result.e33 = (mat.e11 * mat.e22 * mat.e44 + mat.e12 * mat.e24 * mat.e41 + mat.e14 * mat.e21 * mat.e42 - mat.e11 * mat.e24 * mat.e42 - mat.e12 * mat.e21 * mat.e44 - mat.e14 * mat.e22 * mat.e41) * i_det;
	result.e34 = (mat.e11 * mat.e24 * mat.e32 + mat.e12 * mat.e21 * mat.e34 + mat.e14 * mat.e22 * mat.e31 - mat.e11 * mat.e22 * mat.e34 - mat.e12 * mat.e24 * mat.e31 - mat.e14 * mat.e21 * mat.e32) * i_det;
	result.e41 = (mat.e21 * mat.e33 * mat.e42 + mat.e22 * mat.e31 * mat.e43 + mat.e23 * mat.e32 * mat.e41 - mat.e21 * mat.e32 * mat.e43 - mat.e22 * mat.e33 * mat.e41 - mat.e23 * mat.e31 * mat.e42) * i_det;
	result.e42 = (mat.e11 * mat.e32 * mat.e43 + mat.e12 * mat.e33 * mat.e41 + mat.e13 * mat.e31 * mat.e42 - mat.e11 * mat.e33 * mat.e42 - mat.e12 * mat.e31 * mat.e43 - mat.e13 * mat.e32 * mat.e41) * i_det;
	result.e43 = (mat.e11 * mat.e23 * mat.e42 + mat.e12 * mat.e21 * mat.e43 + mat.e13 * mat.e22 * mat.e41 - mat.e11 * mat.e22 * mat.e43 - mat.e12 * mat.e23 * mat.e41 - mat.e13 * mat.e21 * mat.e42) * i_det;
	result.e44 = (mat.e11 * mat.e22 * mat.e33 + mat.e12 * mat.e23 * mat.e31 + mat.e13 * mat.e21 * mat.e32 - mat.e11 * mat.e23 * mat.e32 - mat.e12 * mat.e21 * mat.e33 - mat.e13 * mat.e22 * mat.e31) * i_det;

	/*if (result * m != mat4()) {
		std::cout << "ERROR! Expecting matrix x inverse to equal identity!\n";
	}*/

	return result;
}
